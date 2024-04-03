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
#include "log.h"
#include "external_signals.h"
#include "em_rmu.h"
#include "gatt_db.h"
#include "btl_interface.h"
#include "sl_sleeptimer.h"

static sl_sleeptimer_timer_handle_t handle_to_close;

sl_sleeptimer_timer_callback_t f;

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

// Simple implementation, only handle single connection
static uint8_t connection = SL_BT_INVALID_CONNECTION_HANDLE;
static uint8_t bonding = SL_BT_INVALID_CONNECTION_HANDLE;
// Flags used to control OTA
static bool boot_to_dfu_on_close = false;
static bool ota_approved = false;

void callback_to_close(sl_sleeptimer_timer_handle_t *handle, void *data) {
  (void)handle;
  (void)data;
  sl_bt_external_signal(TIMEOUT_TO_CLOSE);
}
/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void)
{
  uint32_t reason = RMU_ResetCauseGet();
  app_log("RMU_ResetCauseGet() returns 0x%lx\n", reason);
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
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
  bd_addr address;
  uint8_t address_type, security_mode, key_size;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // Configure security
      // Since using Just Works, we will ignore requests to bond
      // and only initiate bonding to connected device when button is pressed
      sc = sl_bt_sm_configure(SL_BT_SM_CONFIGURATION_BONDING_REQUIRED \
                             | SL_BT_SM_CONFIGURATION_SC_ONLY         \
                             | SL_BT_SM_CONFIGURATION_BONDING_REQUEST_REQUIRED,
                             sl_bt_sm_io_capability_noinputnooutput);
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
      // Start advertising and enable connections.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
#define ED evt->data.evt_connection_opened
      app_log("evt_connection_opened, connection:%d, bonding:%d\r\n",ED.connection,ED.bonding);
      connection = ED.connection;
      bonding = ED.bonding;
      ota_approved = false;
      boot_to_dfu_on_close = false;
      break;
#undef ED
      break;

      // this event will be generated in response to sl_bt_external_signals(bitmap)
      // if the above is called multiple times before this event can be delivered,
      // the signals field will contain logical OR of bitmaps set
    case sl_bt_evt_system_external_signal_id:
#define ED evt->data.evt_system_external_signal
      if(ED.extsignals & BUTTON_PRESS) {
          if(SL_BT_INVALID_BONDING_HANDLE == bonding) {
              // If the connected device has invalid bonding handle, initiate
              // bonding as normal
            app_log("sm_increase_security(connection:%d)\r\n",connection);
            sc = sl_bt_sm_increase_security(connection);
            app_assert_status(sc);
          } else {
              // but if there is a valid bonding handle, we have existing bonding
              // data for this device.  This indicates we have previously bonded
              // with this device.  Button press is interpreted as permission to
              // initiate OTA
            app_log("Special case previously bonded device ... allow OTA\r\n");
            ota_approved = true;
          }
      }
      if(ED.extsignals & TIMEOUT_TO_CLOSE) {
          // ignore error ... connection may have already closed
          sc = sl_bt_connection_close(connection);
          if (0 == sc) {
              app_log("Closing connection\r\n");
          }
      }
      break;
#undef ED

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
#define ED evt->data.evt_connection_closed
      app_log("evt_connection_closed(%d)\r\n",ED.connection);
      if(boot_to_dfu_on_close) {
          // remote device requesting OTA has closed connection
          // Assume closed by "forgetting"/deleting bonding
          // delete bonding on this end as well
          app_log("OTA was requested: sl_bt_sm_delete_bonding(bonding:%d)\r\n",bonding);
          sc = sl_bt_sm_delete_bonding(bonding);
          app_assert_status(sc);
          bootloader_rebootAndInstall();
      }
      bonding = SL_BT_INVALID_BONDING_HANDLE;
      connection = SL_BT_INVALID_CONNECTION_HANDLE;
#undef ED
      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Restart advertising after client has disconnected.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);
      break;

    case sl_bt_evt_gatt_server_user_write_request_id:
#define ED evt->data.evt_gatt_server_user_write_request
      app_log("evt_gatt_server_user_write_request(0x%x)\r\n",ED.characteristic);
      if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
          app_log("OTA requested\r\n");
          uint8_t att_error = 0x03; // write not permitted
          if(ota_approved) {
              app_log("OTA request approved, will close connection, delete bonding data and reset to AppLoader\r\n");
              att_error = SL_STATUS_OK;
              boot_to_dfu_on_close = true;
              sl_sleeptimer_start_timer_ms(&handle_to_close, 50, callback_to_close, NULL, 0, 0);
          } else {
              app_log("...denied\r\n");
          }
          sc = sl_bt_gatt_server_send_user_write_response(ED.connection, ED.characteristic, att_error);
      }
      break;
#undef ED

      case sl_bt_evt_sm_bonded_id:
#define ED evt->data.evt_sm_bonded
        app_log("evt_sm_bonded\r\n");
        bonding = ED.bonding;
        sc = sl_bt_sm_get_bonding_details(bonding, &address, &address_type, &security_mode, &key_size);
        app_assert_status(sc);
        break;
#undef ED

      case sl_bt_evt_sm_confirm_bonding_id: // Deny all bonding requests
#define ED evt->data.evt_sm_confirm_bonding
        app_log("evt_sm_confirm_bonding ... refused\r\n");
        sl_bt_sm_bonding_confirm(ED.connection, false);
        break;
#undef ED

        // this event should never happen
      case sl_bt_evt_sm_bonding_failed_id:
        app_log("evt_sm_bonding_failed\r\n");
        break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
