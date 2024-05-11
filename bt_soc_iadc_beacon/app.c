/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "app.h"
#include "em_gpio.h"
#include "em_emu.h"

void init_sampling(float frequency);
size_t get_samples(uint16_t *dest, size_t maxlen);

// advertising interval in ms and Sleep Timer ticks
#define ADV_INTERVAL_MS (5000)
#define ADV_INTERVAL_SLEEP_TICKS ((ADV_INTERVAL_MS << 15)/1000)

//
#define SAMPLE_FREQUENCY (10*1000/ADV_INTERVAL_MS)

// transfered sample buffer size
#define MAX_SAMPLES (64)

// If defined, TEST_ADC enables toggling PC00 after each get_samples call
// This can be helpful verifying validity of data
// #define TEST_ADC

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;
static bool ble_ready;
static uint16_t samples[MAX_SAMPLES];

struct advertisement {
  uint8_t len, type;
  uint16_t id;
  struct {
    uint16_t count;
    uint32_t sum;
    uint16_t max, min;
  } data;
} SL_ATTRIBUTE_PACKED adv_payload = { .len = sizeof(struct advertisement)-1, .type = 0xff, .id = 0xffff, };

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void)
{
  // EM01 optimization use low frequency (< 40 MHz) voltage scaling
  EMU_EM01Init_TypeDef em01Init;
  em01Init.vScaleEM01LowPowerVoltageEnable = emuVScaleEM01_LowPower;
  EMU_EM01Init(&em01Init);

  // EM2 optimization
  // Safe enabling of minimal RAM retention requires reducing LENGTH of RAM to 0x6000 in linker script
#ifdef _SILICON_LABS_32B_SERIES_2_CONFIG_2
  SYSCFG->DMEM0RETNCTRL = 2; // power down RAM block 1 (8k), RAM block 0 (24k) retained
#endif
#ifdef _SILICON_LABS_32B_SERIES_2_CONFIG_7
  SYSCFG->DMEM0RETNCTRL = 6; // power down RAM blocks 1 (8k) and 2 (32k), RAM block 0 (24k) retained
#endif
  // This will disable clocking of debug in EM2
  EMU->CTRL_CLR = 1u << _EMU_CTRL_EM2DBGEN_SHIFT;

  // startup sampling
  init_sampling(SAMPLE_FREQUENCY);

  // disable actions in app_process_action until after system-boot event
  ble_ready = false;

  // Enable toggling PC00 after reading data from sample FIFO
#ifdef TEST_ADC
  GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 0);
#endif
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  static uint32_t tick_last_set = 0;
  sl_status_t sc;
  size_t count;
  if(!ble_ready) {
      return;
  }
  /* app_process_action may be called multiple times before dropping to sleep.
   * No advantage to updating advertisement more frequently than it can be sent. */
  uint32_t now = sl_sleeptimer_get_tick_count();
  if ((now - tick_last_set) < ADV_INTERVAL_SLEEP_TICKS) {
      return;
  }
  tick_last_set = now;
  adv_payload.data.count = adv_payload.data.sum = adv_payload.data.max = 0;
  adv_payload.data.min = -1;
  do {
      count = get_samples(samples, MAX_SAMPLES);
#ifdef TEST_ADC
  GPIO_PinOutToggle(gpioPortC, 0);
#endif
      adv_payload.data.count += count;
      for(size_t i = 0; i < count; i++) {
          adv_payload.data.sum += samples[i];
          if (samples[i] > adv_payload.data.max) {
              adv_payload.data.max = samples[i];
          }
          if (samples[i] < adv_payload.data.min) {
              adv_payload.data.min = samples[i];
          }
      }
  } while(MAX_SAMPLES == count);
  sc = sl_bt_legacy_advertiser_set_data(advertising_set_handle, 0, sizeof(adv_payload), (uint8_t*)&adv_payload);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      ble_ready = true;
      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      // set initial advertising data
      app_process_action();

      // Set advertising interval to 100ms.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        (ADV_INTERVAL_MS << 4)/10, // min. adv. interval (milliseconds * 1.6)
        (ADV_INTERVAL_MS << 4)/10, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      app_assert_status(sc);
      // Start advertising and enable connections.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_legacy_advertiser_non_connectable);
      app_assert_status(sc);
      break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
