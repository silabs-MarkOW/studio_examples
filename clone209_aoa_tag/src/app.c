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
#include "advertiser.h"
#include "sl_sleeptimer.h"
#include <stdio.h>

// Bits used to convert interrupt into event
#define UPDATE_RANDOM_ADDRESS (1)
#define UPDATE_PERIODIC_PAYLOAD (2)

// this is called from interrupt context
// Stack calls must not be made from interrupt context
// see UG434
// https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf#page=19
void callback_10minutes(sl_sleeptimer_timer_handle_t *handle, void *data) {
  (void)handle;
  (void)data;
  // pass bit to stack, stack will generate system_external_signals event
  // with logical OR of pending bits
  sl_bt_external_signal(UPDATE_RANDOM_ADDRESS);
}

void callback_30seconds(sl_sleeptimer_timer_handle_t *handle, void *data) {
  (void)handle;
  (void)data;
  sl_bt_external_signal(UPDATE_PERIODIC_PAYLOAD);
}

sl_sleeptimer_timer_handle_t handle_10minutes, handle_30seconds;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void)
{
  // start periodic 10 minute timer
  sl_sleeptimer_start_periodic_timer_ms(&handle_10minutes,
                                        10*60*1000,
                                        callback_10minutes,
                                        NULL, 0, 0);
  sl_sleeptimer_start_periodic_timer_ms(&handle_30seconds,
                                        30*1000,
                                        callback_30seconds,
                                        NULL, 0, 0);
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      initialize_advertisers();
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      start_legacy_advertisement();
      break;

      // this event will be generated due to call in sleeptimer callbacks
    case sl_bt_evt_system_external_signal_id:
#define ED evt->data.evt_system_external_signal
      if(ED.extsignals & UPDATE_RANDOM_ADDRESS) {
          update_extended_private_address();
      }
      if(ED.extsignals & UPDATE_PERIODIC_PAYLOAD) {
          char buffer[64];
          size_t len;
          len = snprintf(buffer, 64, "Uptime %ld seconds",
                         sl_sleeptimer_get_tick_count() / sl_sleeptimer_get_timer_frequency());
          update_periodic_advertisement(len, (uint8_t*)buffer);
      }
      break;
#undef ED

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
