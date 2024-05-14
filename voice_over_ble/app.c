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
#include <stdbool.h>
#include "em_common.h"
#include "app_log.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "app.h"
#include "voice.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "sl_component_catalog.h"
#include "circular_buff.h"

#include "em_timer.h"
#include "em_prs.h"
#include "em_cmu.h"
#include "rac.h"
#include "em_gpio.h"
#include "sl_emlib_gpio_init_copy_from_fifo_config.h"

void callback(uint8_t intno) {
  (void)intno;
  if(GPIO_PinInGet(gpioPortC, 8)) {
      GPIO_PinOutSet(gpioPortA, 8);
  } else {
      GPIO_PinOutClear(gpioPortA, 8);
  }
}

void init_timer(void) {
  TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;
  TIMER_InitCC_TypeDef initCC = TIMER_INITCC_DEFAULT;
  CMU_ClockEnable(cmuClock_WTIMER0, true);
  CMU_ClockEnable(cmuClock_HFPER, true);
  TIMER_Init(WTIMER0, &init);
  initCC.mode = timerCCModeCapture;
  initCC.prsInput = true;
  initCC.prsSel = timerPRSSELCh0;
  TIMER_InitCC(WTIMER0, 0,  &initCC);
  PRS_ConnectSignal(0, prsTypeAsync, prsSignalUSART1_RXDATA);
  TIMER_Enable(WTIMER0, true);
//  PRS_ConnectSignal(1, prsTypeAsync, PRS_CH_CTRL_SIGSEL_GPIOPIN6);
  GPIOINT_CallbackRegister(9, callback);
  GPIO_ExtIntConfig(gpioPortC, 9, 9, true, true, true);
  GPIO_PinModeSet(gpioPortA, 8, gpioModePushPull, 0);
  GPIO_IntEnable(1 << 9);
  PRS_ConnectSignal(1, prsTypeAsync, prsSignalGPIO_PIN9);
  PRS->ROUTELOC1 = PRS_ROUTELOC0_CH1LOC_LOC5;
  PRS->ROUTEPEN = 1<<1;
}

#ifdef SL_CATALOG_SIMPLE_COM_PRESENT
#include "sl_simple_com.h"
#endif // SL_CATALOG_SIMPLE_COM_PRESENT
#ifdef SL_CATALOG_CLI_PRESENT
#include "sl_cli.h"
#endif // SL_CATALOG_CLI_PRESENT

#define SAFETY_MARGIN (3072)

#define INVALID_HANDLE       0xff

#define TRANSFER_STOP        ('0')
#define TRANSFER_START       ('1')

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = INVALID_HANDLE;

extern circular_buffer_t circular_buffer;  // declared in voice.c

// Connection handle, available for other modules
uint8_t ble_connection = INVALID_HANDLE;

// Button events
static bool button_pressed = false;
static bool button_released = false;
static uint32_t packets_sent = 0;
static uint32_t bytes_sent = 0;

static size_t mtu, payload_bytes;
static bool process_mtu;

#define S(X) const char *state_ ## X = #X
S(start);
S(idle);
S(running);
S(clean_up);
const char *state = "None";

void _set_state(const char *next) {
  app_log("set_state: %s --> %s\r\n",state,next);
  state = next;
}

#define set_state(X) _set_state(state_ ## X)
#define is_state(X) (state_ ## X == state)

/***************************************************************************//**
 * Notify client about the actual transfer status.
 ******************************************************************************/
static void app_notify_client(uint8_t transfer_status);

#define FLAGS_TO_SEND (1)
#define FLAGS_SENDING (2)
#define FLAGS_SENT    (4)

struct packet  {
  struct packet *next;
  uint16_t flags;
  uint16_t index;
  uint16_t payload[];
}
__attribute__((__packed__))
*head, *tail;
size_t n_packets;

const char *allocate_packets(void) {
  void *safety = malloc(SAFETY_MARGIN);
  if(!safety) {
      return "out of memory";
  }
  payload_bytes = (mtu - 2 - offsetof(struct packet,index)) & ~1;
  while(1) {
      struct packet *p;
      p = malloc(sizeof(struct packet)+ payload_bytes);
      if(!p) {
          break;
      }
      if(!tail) {
          tail = p;
      }
      p->next = head;
      head = p;
      p->index = 0xffff;
      p->flags = 0;
      n_packets++;
  }
  free(safety);
  tail->next = head;  // loop back to head
  tail = head;  // set to empty state
  return NULL;
}

void process_data(void) {
  static uint16_t index = 0;
  if(is_state(clean_up)) {
      set_state(idle);
  }
  //app_log("fl:%d,%d\r\n",tail->flags,head-tail);
  while((tail != head) && (tail->flags & FLAGS_TO_SEND)) {
      sl_status_t sc;
      tail->flags |= FLAGS_SENDING;
      sc = sl_bt_gatt_server_send_notification(ble_connection,
                                               gattdb_audio_data,
                                               2+payload_bytes,
                                               (uint8_t*)&tail->index);
      if(0 == sc) {
          tail->flags |= FLAGS_SENT;
          tail->flags &= ~(FLAGS_SENDING | FLAGS_TO_SEND);
          tail = tail->next;
          packets_sent++;
          bytes_sent += payload_bytes;
      } else if(0x25 == sc) {
          tail->flags &= ~(FLAGS_SENDING | FLAGS_TO_SEND);
          tail = tail->next;
      } else {
          tail->flags &= ~FLAGS_SENDING;
          app_log("sc: 0x%lx\r\n",sc);
          break;
      }
  }
  GPIO_PinOutSet(SL_EMLIB_GPIO_INIT_COPY_FROM_FIFO_PORT, SL_EMLIB_GPIO_INIT_COPY_FROM_FIFO_PIN);
  size_t av;
  while((av = cb_readable(&circular_buffer)) >= payload_bytes) {
      cb_err_code_t err = cb_pop_buff(&circular_buffer, head->payload, payload_bytes);
      if(cb_err_ok == err) {
          head->flags = FLAGS_TO_SEND;
          head->index = index++;
          head = head->next;
          if(head == tail) {
              tail = tail->next; // force loss
              app_log("head collided with tail\r\n");
          }
          //app_log("av:%d,%d\r\n",av,head-tail);
      }
  }
  GPIO_PinOutClear(SL_EMLIB_GPIO_INIT_COPY_FROM_FIFO_PORT, SL_EMLIB_GPIO_INIT_COPY_FROM_FIFO_PIN);
}

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void)
{
//  init_timer();
  show_rac_init();
  set_state(start);
  voice_init();
  app_log_info("soc_voice initialised\n");
#define P(X) app_log(#X ": 0x%08x\r\n",X)
  P(gattdb_audio_data);
  P(gattdb_sample_rate);
  P(gattdb_filter_enable);
  P(gattdb_encoding_enable);
  P(gattdb_transfer_status);
  P(gattdb_audio_channels);
  P(gattdb_stream_enable);
#undef P
  mtu = 23;
  process_mtu = true;
  head = tail = NULL;
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
  if(process_mtu) {
      const char *errmsg;
      size_t counter = 0;
      if(tail) {
          head = tail->next;
          free(tail);
          counter++;
      }
      while(head && (head != tail)) {
          void *p = head;
          head = head->next;
          free(p);
          counter++;
      }
      app_log("Freed %d packets\r\n",counter);
      head = tail = NULL;
      n_packets = 0;
      CORE_CRITICAL_SECTION(errmsg = allocate_packets();)
      if(errmsg){
          app_log("Error: %s\r\n",errmsg);
          sl_bt_system_reset(0);
      }
      process_mtu = false;
      app_log("%d packets allocated (mtu: %d)\r\n", n_packets,mtu);
      app_log("payload_bytes: %d\r\n",payload_bytes);
  }
  voice_process_action();
  process_data();
  if (button_pressed) {
    button_pressed = false;
    // Turn LED on
    sl_led_turn_on(&sl_led_led0);
    // Start recording
    voice_start();
    // Notify client about transfer status change
    app_notify_client(TRANSFER_START);
  }
  if (button_released) {
    button_released = false;
    // Turn LED off
    sl_led_turn_off(&sl_led_led0);
    // Stop recording
    voice_stop();
    // Notify client about transfer status change
    app_notify_client(TRANSFER_STOP);
  }
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
  uint16_t max_mtu_out;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // Print boot message.
      app_log_info("Bluetooth stack booted: v%d.%d.%d-b%d\n",
                   evt->data.evt_system_boot.major,
                   evt->data.evt_system_boot.minor,
                   evt->data.evt_system_boot.patch,
                   evt->data.evt_system_boot.build);

      // Set maximal MTU for GATT Server.
      sc = sl_bt_gatt_server_set_max_mtu(250, &max_mtu_out);
      app_assert_status(sc);

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Set advertising interval to 100ms.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        160, // min. adv. interval (milliseconds * 1.6)
        160, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      app_assert_status(sc);
      // Start general advertising and enable connections.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_legacy_advertiser_connectable);
      app_assert_status(sc);

      app_log_info("Start advertising\n");
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      app_log_info("Connection opened\n");
      ble_connection = evt->data.evt_connection_opened.connection;
      packets_sent = 0;
      bytes_sent = 0;
      mtu = 23;
      break;

    case sl_bt_evt_gatt_mtu_exchanged_id:
#define ED evt->data.evt_gatt_mtu_exchanged
      app_log("mtu: %d\r\n",ED.mtu);
      mtu = ED.mtu;
      process_mtu = true;
      break;
#undef ED

    case sl_bt_evt_connection_phy_status_id:
#define ED evt->data.evt_connection_phy_status
      app_log("evt_connection_phy_status.phy: %d\r\n",ED.phy);
      break;
#undef ED

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      app_log_info("Connection closed\n");
      app_log("%ld packets sent\r\n",packets_sent);
      app_log("%ld bytes sent\r\n",bytes_sent);
      ble_connection = INVALID_HANDLE;
      if(is_state(running)) {
          voice_stop();
          set_state(idle);
      }
      mtu = 23;
      process_mtu = true;
      set_state(idle);
      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Restart advertising after client has disconnected.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_legacy_advertiser_connectable);
      app_assert_status(sc);
      app_log_info("Start advertising\n");
      break;

    // -------------------------------
    // Handle Voice configuration characteristics.
    case sl_bt_evt_gatt_server_user_write_request_id:
      app_log("evt_gatt_server_user_write_request: 0x%x\r\n", evt->data.evt_gatt_server_user_write_request.characteristic);
      switch (evt->data.evt_gatt_server_user_write_request.characteristic) {
        case gattdb_sample_rate:
          voice_set_sample_rate((sample_rate_t)evt->data.evt_gatt_server_user_write_request.value.data[0]);
          break;

        case gattdb_filter_enable:
          voice_set_filter_enable((bool)evt->data.evt_gatt_server_user_write_request.value.data[0]);
          break;

        case gattdb_encoding_enable:
          voice_set_encoding_enable((bool)evt->data.evt_gatt_server_user_write_request.value.data[0]);
          break;

        case gattdb_audio_channels:
          voice_set_channels(evt->data.evt_gatt_server_user_write_request.value.data[0]);
          break;

        case gattdb_stream_enable:
          app_log("stream_enable write\r\n");
          if(evt->data.evt_gatt_server_user_write_request.value.data[0]) {
              voice_start();
              set_state(running);
          } else {
              voice_stop();
              set_state(idle);
          }
          break;

        default:
          // Other characteristics are not handled here.
          return;
      }
      // Send write response.
      sc = sl_bt_gatt_server_send_user_write_response(
        evt->data.evt_gatt_server_user_write_request.connection,
        evt->data.evt_gatt_server_user_write_request.characteristic,
        0);    // no error
      app_assert_status(sc);
      break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

static void app_notify_client(uint8_t transfer_status)
{
  if (INVALID_HANDLE != ble_connection) {
    (void)sl_bt_gatt_server_send_notification(
      ble_connection,
      gattdb_transfer_status,
      sizeof(transfer_status),
      &transfer_status);
  }
}

#if(0)
bool voice_transmit(uint8_t *buffer, uint32_t size)
{
  sl_status_t sc = 0;
  if (INVALID_HANDLE != ble_connection) {
    // Write data to characteristic
    sc = sl_bt_gatt_server_send_notification(
      ble_connection,
      gattdb_audio_data,
      size,
      buffer);
    if(0 == sc) packets_sent++;
  }
#ifdef SL_CATALOG_SIMPLE_COM_PRESENT
  sl_simple_com_transmit(size, buffer);
#endif // SL_CATALOG_SIMPLE_COM_PRESENT
  return 0 == sc;
}
#endif

/***************************************************************************//**
 * Button event handler callback.
 * Overrides dummy weak implementation.
 ******************************************************************************/
void sl_button_on_change(const sl_button_t *handle)
{
  // button pressed
  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
    if (&sl_button_btn0 == handle) {
      button_pressed = true;
    }
  }
  // button released
  else if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_RELEASED) {
    if (&sl_button_btn0 == handle) {
      button_released = true;
    }
  }
}

#ifdef SL_CATALOG_CLI_PRESENT
/***************************************************************************//**
 * Command line interface handlers.
 ******************************************************************************/
void cli_sample_rate(sl_cli_command_arg_t *arguments)
{
  sample_rate_t sample_rate = (sample_rate_t)sl_cli_get_argument_uint8(arguments, 0);
  voice_set_sample_rate(sample_rate);
}

void cli_channels(sl_cli_command_arg_t *arguments)
{
  uint8_t channels = sl_cli_get_argument_uint8(arguments, 0);
  voice_set_channels(channels);
}

void cli_filter(sl_cli_command_arg_t *arguments)
{
  bool status = (bool)sl_cli_get_argument_uint8(arguments, 0);
  voice_set_filter_enable(status);
}

void cli_encoding(sl_cli_command_arg_t *arguments)
{
  bool status = (bool)sl_cli_get_argument_uint8(arguments, 0);
  voice_set_encoding_enable(status);
}
#endif // SL_CATALOG_CLI_PRESENT
