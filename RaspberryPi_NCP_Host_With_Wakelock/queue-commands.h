#include <sl_status.h>
#ifndef __QUEUE_COMMANDS_H__
#define __QUEUE_COMMANDS_H__

enum CMD_TYPE { DFU_FLASH_SET_ADDRESS, DFU_FLASH_UPLOAD, DFU_FLASH_UPLOAD_FINISH, SYSTEM_HELLO, SYSTEM_START_BLUETOOTH, SYSTEM_STOP_BLUETOOTH, SYSTEM_FORCEFULLY_STOP_BLUETOOTH, SYSTEM_GET_VERSION, SYSTEM_RESET, SYSTEM_HALT, SYSTEM_LINKLAYER_CONFIGURE, SYSTEM_SET_TX_POWER, SYSTEM_GET_TX_POWER_SETTING, SYSTEM_SET_IDENTITY_ADDRESS, SYSTEM_GET_IDENTITY_ADDRESS, SYSTEM_GET_RANDOM_DATA, SYSTEM_DATA_BUFFER_WRITE, SYSTEM_DATA_BUFFER_CLEAR, SYSTEM_GET_COUNTERS, SYSTEM_SET_LAZY_SOFT_TIMER, GAP_SET_PRIVACY_MODE, GAP_SET_DATA_CHANNEL_CLASSIFICATION, GAP_ENABLE_WHITELISTING, GAP_SET_IDENTITY_ADDRESS, ADVERTISER_CREATE_SET, ADVERTISER_CONFIGURE, ADVERTISER_SET_TIMING, ADVERTISER_SET_CHANNEL_MAP, ADVERTISER_SET_TX_POWER, ADVERTISER_SET_REPORT_SCAN_REQUEST, ADVERTISER_SET_RANDOM_ADDRESS, ADVERTISER_CLEAR_RANDOM_ADDRESS, ADVERTISER_STOP, ADVERTISER_DELETE_SET, ADVERTISER_SET_PHY, ADVERTISER_SET_CONFIGURATION, ADVERTISER_CLEAR_CONFIGURATION, ADVERTISER_SET_DATA, ADVERTISER_SET_LONG_DATA, ADVERTISER_START, ADVERTISER_START_PERIODIC_ADVERTISING, ADVERTISER_STOP_PERIODIC_ADVERTISING, SCANNER_SET_PARAMETERS, SCANNER_SET_PARAMETERS_AND_FILTER, SCANNER_STOP, SCANNER_SET_TIMING, SCANNER_SET_MODE, SCANNER_START, CONNECTION_SET_DEFAULT_PARAMETERS, CONNECTION_SET_DEFAULT_PREFERRED_PHY, CONNECTION_SET_DEFAULT_DATA_LENGTH, CONNECTION_OPEN, CONNECTION_SET_PARAMETERS, CONNECTION_SET_PREFERRED_PHY, CONNECTION_DISABLE_SLAVE_LATENCY, CONNECTION_GET_MEDIAN_RSSI, CONNECTION_READ_CHANNEL_MAP, CONNECTION_SET_POWER_REPORTING, CONNECTION_SET_REMOTE_POWER_REPORTING, CONNECTION_GET_TX_POWER, CONNECTION_GET_REMOTE_TX_POWER, CONNECTION_SET_TX_POWER, CONNECTION_READ_REMOTE_USED_FEATURES, CONNECTION_GET_SECURITY_STATUS, CONNECTION_SET_DATA_LENGTH, CONNECTION_READ_STATISTICS, CONNECTION_GET_SCHEDULING_DETAILS, CONNECTION_CLOSE, CONNECTION_FORCEFULLY_CLOSE, CONNECTION_GET_RSSI, GATT_SET_MAX_MTU, GATT_DISCOVER_PRIMARY_SERVICES, GATT_DISCOVER_PRIMARY_SERVICES_BY_UUID, GATT_FIND_INCLUDED_SERVICES, GATT_DISCOVER_CHARACTERISTICS, GATT_DISCOVER_CHARACTERISTICS_BY_UUID, GATT_DISCOVER_DESCRIPTORS, GATT_DISCOVER_CHARACTERISTIC_DESCRIPTORS, GATT_SET_CHARACTERISTIC_NOTIFICATION, GATT_SEND_CHARACTERISTIC_CONFIRMATION, GATT_READ_CHARACTERISTIC_VALUE, GATT_READ_CHARACTERISTIC_VALUE_FROM_OFFSET, GATT_READ_MULTIPLE_CHARACTERISTIC_VALUES, GATT_READ_CHARACTERISTIC_VALUE_BY_UUID, GATT_WRITE_CHARACTERISTIC_VALUE, GATT_WRITE_CHARACTERISTIC_VALUE_WITHOUT_RESPONSE, GATT_PREPARE_CHARACTERISTIC_VALUE_WRITE, GATT_PREPARE_CHARACTERISTIC_VALUE_RELIABLE_WRITE, GATT_EXECUTE_CHARACTERISTIC_VALUE_WRITE, GATT_READ_DESCRIPTOR_VALUE, GATT_WRITE_DESCRIPTOR_VALUE, GATT_SERVER_SET_MAX_MTU, GATT_SERVER_GET_MTU, GATT_SERVER_FIND_ATTRIBUTE, GATT_SERVER_READ_ATTRIBUTE_VALUE, GATT_SERVER_READ_ATTRIBUTE_TYPE, GATT_SERVER_WRITE_ATTRIBUTE_VALUE, GATT_SERVER_SEND_USER_READ_RESPONSE, GATT_SERVER_SEND_USER_WRITE_RESPONSE, GATT_SERVER_SEND_NOTIFICATION, GATT_SERVER_SEND_INDICATION, GATT_SERVER_NOTIFY_ALL, GATT_SERVER_READ_CLIENT_CONFIGURATION, GATT_SERVER_SEND_USER_PREPARE_WRITE_RESPONSE, GATT_SERVER_SET_CAPABILITIES, GATT_SERVER_ENABLE_CAPABILITIES, GATT_SERVER_DISABLE_CAPABILITIES, GATT_SERVER_GET_ENABLED_CAPABILITIES, GATT_SERVER_READ_CLIENT_SUPPORTED_FEATURES, NVM_SAVE, NVM_LOAD, NVM_ERASE, NVM_ERASE_ALL, TEST_DTM_TX_V4, TEST_DTM_TX_CW, TEST_DTM_RX, TEST_DTM_END, SM_CONFIGURE, SM_SET_MINIMUM_KEY_SIZE, SM_SET_DEBUG_MODE, SM_ADD_TO_WHITELIST, SM_STORE_BONDING_CONFIGURATION, SM_SET_BONDABLE_MODE, SM_SET_PASSKEY, SM_INCREASE_SECURITY, SM_ENTER_PASSKEY, SM_PASSKEY_CONFIRM, SM_BONDING_CONFIRM, SM_DELETE_BONDING, SM_DELETE_BONDINGS, SM_GET_BONDING_HANDLES, SM_GET_BONDING_DETAILS, SM_FIND_BONDING_BY_ADDRESS, SM_RESOLVE_RPA, SM_SET_BONDING_KEY, SM_SET_LEGACY_OOB, SM_SET_OOB, SM_SET_REMOTE_OOB, SM_SET_BONDING_DATA, OTA_SET_DEVICE_NAME, OTA_SET_ADVERTISING_DATA, OTA_SET_CONFIGURATION, OTA_SET_RF_PATH, COEX_SET_OPTIONS, COEX_SET_PARAMETERS, COEX_SET_DIRECTIONAL_PRIORITY_PULSE, COEX_GET_PARAMETERS, COEX_GET_COUNTERS, SYNC_SET_PARAMETERS, SYNC_OPEN, SYNC_SET_REPORTING_MODE, SYNC_UPDATE_SYNC_PARAMETERS, SYNC_CLOSE, L2CAP_OPEN_LE_CHANNEL, L2CAP_SEND_LE_CHANNEL_OPEN_RESPONSE, L2CAP_CHANNEL_SEND_DATA, L2CAP_CHANNEL_SEND_CREDIT, L2CAP_CLOSE_CHANNEL, CTE_TRANSMITTER_SET_DTM_PARAMETERS, CTE_TRANSMITTER_CLEAR_DTM_PARAMETERS, CTE_TRANSMITTER_ENABLE_CONNECTION_CTE, CTE_TRANSMITTER_DISABLE_CONNECTION_CTE, CTE_TRANSMITTER_ENABLE_CONNECTIONLESS_CTE, CTE_TRANSMITTER_DISABLE_CONNECTIONLESS_CTE, CTE_TRANSMITTER_ENABLE_SILABS_CTE, CTE_TRANSMITTER_DISABLE_SILABS_CTE, CTE_RECEIVER_SET_DTM_PARAMETERS, CTE_RECEIVER_CLEAR_DTM_PARAMETERS, CTE_RECEIVER_SET_SYNC_CTE_TYPE, CTE_RECEIVER_SET_DEFAULT_SYNC_RECEIVE_PARAMETERS, CTE_RECEIVER_SET_SYNC_RECEIVE_PARAMETERS, CTE_RECEIVER_CONFIGURE, CTE_RECEIVER_ENABLE_CONNECTION_CTE, CTE_RECEIVER_DISABLE_CONNECTION_CTE, CTE_RECEIVER_ENABLE_CONNECTIONLESS_CTE, CTE_RECEIVER_DISABLE_CONNECTIONLESS_CTE, CTE_RECEIVER_ENABLE_SILABS_CTE, CTE_RECEIVER_DISABLE_SILABS_CTE, GATTDB_NEW_SESSION, GATTDB_ADD_SERVICE, GATTDB_REMOVE_SERVICE, GATTDB_ADD_INCLUDED_SERVICE, GATTDB_REMOVE_INCLUDED_SERVICE, GATTDB_ADD_UUID16_CHARACTERISTIC, GATTDB_ADD_UUID128_CHARACTERISTIC, GATTDB_REMOVE_CHARACTERISTIC, GATTDB_ADD_UUID16_DESCRIPTOR, GATTDB_ADD_UUID128_DESCRIPTOR, GATTDB_REMOVE_DESCRIPTOR, GATTDB_START_SERVICE, GATTDB_STOP_SERVICE, GATTDB_START_CHARACTERISTIC, GATTDB_STOP_CHARACTERISTIC, GATTDB_COMMIT, GATTDB_ABORT, CONNECTION_ANALYZER_START, CONNECTION_ANALYZER_STOP, SYNC_SCANNER_SET_SYNC_PARAMETERS, SYNC_SCANNER_OPEN, PAST_RECEIVER_SET_DEFAULT_SYNC_RECEIVE_PARAMETERS, PAST_RECEIVER_SET_SYNC_RECEIVE_PARAMETERS, ADVERTISER_PAST_TRANSFER, PAWR_SYNC_SET_SYNC_SUBEVENTS, PAWR_SYNC_SET_RESPONSE_DATA, PAWR_ADVERTISER_START, PAWR_ADVERTISER_SET_SUBEVENT_DATA, PAWR_ADVERTISER_CREATE_CONNECTION, PAWR_ADVERTISER_STOP, LEGACY_ADVERTISER_SET_DATA, LEGACY_ADVERTISER_GENERATE_DATA, LEGACY_ADVERTISER_START, LEGACY_ADVERTISER_START_DIRECTED, EXTENDED_ADVERTISER_SET_PHY, EXTENDED_ADVERTISER_SET_DATA, EXTENDED_ADVERTISER_SET_LONG_DATA, EXTENDED_ADVERTISER_GENERATE_DATA, EXTENDED_ADVERTISER_START, EXTENDED_ADVERTISER_START_DIRECTED, PERIODIC_ADVERTISER_SET_DATA, PERIODIC_ADVERTISER_SET_LONG_DATA, PERIODIC_ADVERTISER_START, PERIODIC_ADVERTISER_STOP, CS_SECURITY_ENABLE, CS_SET_DEFAULT_SETTINGS, CS_CREATE_CONFIG, CS_REMOVE_CONFIG, CS_SET_CHANNEL_CLASSIFICATION, CS_SET_PROCEDURE_PARAMETERS, CS_PROCEDURE_ENABLE, CS_SET_ANTENNA_CONFIGURATION, CS_READ_LOCAL_SUPPORTED_CAPABILITIES, CS_TEST_START, SYNC_PAST_TRANSFER, EXTERNAL_BONDINGDB_SET_DATA, RESOLVING_LIST_ADD_DEVICE_BY_BONDING, RESOLVING_LIST_ADD_DEVICE_BY_ADDRESS, RESOLVING_LIST_REMOVE_DEVICE_BY_BONDING, RESOLVING_LIST_REMOVE_DEVICE_BY_ADDRESS, RESOLVING_LIST_REMOVE_ALL_DEVICES, ACCEPT_LIST_ADD_DEVICE_BY_BONDING, ACCEPT_LIST_ADD_DEVICE_BY_ADDRESS, ACCEPT_LIST_REMOVE_DEVICE_BY_BONDING, ACCEPT_LIST_REMOVE_DEVICE_BY_ADDRESS, ACCEPT_LIST_REMOVE_ALL_DEVICES, RESOURCE_GET_STATUS, RESOURCE_SET_REPORT_THRESHOLD, RESOURCE_ENABLE_CONNECTION_TX_REPORT, RESOURCE_GET_CONNECTION_TX_STATUS, RESOURCE_DISABLE_CONNECTION_TX_REPORT, USER_MESSAGE_TO_TARGET, USER_MANAGE_EVENT_FILTER, USER_RESET_TO_DFU };
struct dfu_flash_set_address_s {
  uint32_t address;
};
struct dfu_flash_upload_s {
  size_t data_len;
  uint8_t *data;
};
struct dfu_flash_upload_finish_s {
};
struct system_hello_s {
};
struct system_start_bluetooth_s {
};
struct system_stop_bluetooth_s {
};
struct system_forcefully_stop_bluetooth_s {
};
struct system_get_version_s {
  uint16_t major;
  uint16_t minor;
  uint16_t patch;
  uint16_t build;
  uint32_t bootloader;
  uint32_t hash;
};
struct system_reset_s {
  uint8_t dfu;
};
struct system_halt_s {
  uint8_t halt;
};
struct system_linklayer_configure_s {
  uint8_t key;
  size_t data_len;
  uint8_t *data;
};
struct system_set_tx_power_s {
  int16_t min_power;
  int16_t max_power;
  int16_t set_min;
  int16_t set_max;
};
struct system_get_tx_power_setting_s {
  int16_t support_min;
  int16_t support_max;
  int16_t set_min;
  int16_t set_max;
  int16_t rf_path_gain;
};
struct system_set_identity_address_s {
  bd_addr address;
  uint8_t type;
};
struct system_get_identity_address_s {
  bd_addr address;
  uint8_t type;
};
struct system_get_random_data_s {
  uint8_t length;
  size_t data_max_len;
  size_t *data_len;
  uint8_t *data;
};
struct system_data_buffer_write_s {
  size_t data_len;
  uint8_t *data;
};
struct system_data_buffer_clear_s {
};
struct system_get_counters_s {
  uint8_t reset;
  uint16_t tx_packets;
  uint16_t rx_packets;
  uint16_t crc_errors;
  uint16_t failures;
};
struct system_set_lazy_soft_timer_s {
  uint32_t time;
  uint32_t slack;
  uint8_t handle;
  uint8_t single_shot;
};
struct gap_set_privacy_mode_s {
  uint8_t privacy;
  uint8_t interval;
};
struct gap_set_data_channel_classification_s {
  size_t channel_map_len;
  uint8_t *channel_map;
};
struct gap_enable_whitelisting_s {
  uint8_t enable;
};
struct gap_set_identity_address_s {
  bd_addr address;
  uint8_t addr_type;
};
struct advertiser_create_set_s {
  uint8_t handle;
};
struct advertiser_configure_s {
  uint8_t advertising_set;
  uint32_t flags;
};
struct advertiser_set_timing_s {
  uint8_t advertising_set;
  uint32_t interval_min;
  uint32_t interval_max;
  uint16_t duration;
  uint8_t maxevents;
};
struct advertiser_set_channel_map_s {
  uint8_t advertising_set;
  uint8_t channel_map;
};
struct advertiser_set_tx_power_s {
  uint8_t advertising_set;
  int16_t power;
  int16_t set_power;
};
struct advertiser_set_report_scan_request_s {
  uint8_t advertising_set;
  uint8_t report_scan_req;
};
struct advertiser_set_random_address_s {
  uint8_t advertising_set;
  uint8_t addr_type;
  bd_addr address;
  bd_addr address_out;
};
struct advertiser_clear_random_address_s {
  uint8_t advertising_set;
};
struct advertiser_stop_s {
  uint8_t advertising_set;
};
struct advertiser_delete_set_s {
  uint8_t advertising_set;
};
struct advertiser_set_phy_s {
  uint8_t advertising_set;
  uint8_t primary_phy;
  uint8_t secondary_phy;
};
struct advertiser_set_configuration_s {
  uint8_t advertising_set;
  uint32_t configurations;
};
struct advertiser_clear_configuration_s {
  uint8_t advertising_set;
  uint32_t configurations;
};
struct advertiser_set_data_s {
  uint8_t advertising_set;
  uint8_t packet_type;
  size_t adv_data_len;
  uint8_t *adv_data;
};
struct advertiser_set_long_data_s {
  uint8_t advertising_set;
  uint8_t packet_type;
};
struct advertiser_start_s {
  uint8_t advertising_set;
  uint8_t discover;
  uint8_t connect;
};
struct advertiser_start_periodic_advertising_s {
  uint8_t advertising_set;
  uint16_t interval_min;
  uint16_t interval_max;
  uint32_t flags;
};
struct advertiser_stop_periodic_advertising_s {
  uint8_t advertising_set;
};
struct scanner_set_parameters_s {
  uint8_t mode;
  uint16_t interval;
  uint16_t window;
};
struct scanner_set_parameters_and_filter_s {
  uint8_t mode;
  uint16_t interval;
  uint16_t window;
  uint32_t flags;
  uint8_t filter_policy;
};
struct scanner_stop_s {
};
struct scanner_set_timing_s {
  uint8_t phys;
  uint16_t scan_interval;
  uint16_t scan_window;
};
struct scanner_set_mode_s {
  uint8_t phys;
  uint8_t scan_mode;
};
struct scanner_start_s {
  uint8_t scanning_phy;
  uint8_t discover_mode;
};
struct connection_set_default_parameters_s {
  uint16_t min_interval;
  uint16_t max_interval;
  uint16_t latency;
  uint16_t timeout;
  uint16_t min_ce_length;
  uint16_t max_ce_length;
};
struct connection_set_default_preferred_phy_s {
  uint8_t preferred_phy;
  uint8_t accepted_phy;
};
struct connection_set_default_data_length_s {
  uint16_t tx_data_len;
};
struct connection_open_s {
  bd_addr address;
  uint8_t address_type;
  uint8_t initiating_phy;
  uint8_t connection;
};
struct connection_set_parameters_s {
  uint8_t connection;
  uint16_t min_interval;
  uint16_t max_interval;
  uint16_t latency;
  uint16_t timeout;
  uint16_t min_ce_length;
  uint16_t max_ce_length;
};
struct connection_set_preferred_phy_s {
  uint8_t connection;
  uint8_t preferred_phy;
  uint8_t accepted_phy;
};
struct connection_disable_slave_latency_s {
  uint8_t connection;
  uint8_t disable;
};
struct connection_get_median_rssi_s {
  uint8_t connection;
  int8_t rssi;
};
struct connection_read_channel_map_s {
  uint8_t connection;
  size_t channel_map_max_len;
  size_t *channel_map_len;
  uint8_t *channel_map;
};
struct connection_set_power_reporting_s {
  uint8_t connection;
  uint8_t mode;
};
struct connection_set_remote_power_reporting_s {
  uint8_t connection;
  uint8_t mode;
};
struct connection_get_tx_power_s {
  uint8_t connection;
  uint8_t phy;
  int8_t current_level;
  int8_t max_level;
};
struct connection_get_remote_tx_power_s {
  uint8_t connection;
  uint8_t phy;
};
struct connection_set_tx_power_s {
  uint8_t connection;
  int16_t tx_power;
  int16_t tx_power_out;
};
struct connection_read_remote_used_features_s {
  uint8_t connection;
};
struct connection_get_security_status_s {
  uint8_t connection;
  uint8_t security_mode;
  uint8_t key_size;
  uint8_t bonding_handle;
};
struct connection_set_data_length_s {
  uint8_t connection;
  uint16_t tx_data_len;
  uint16_t tx_time_us;
};
struct connection_read_statistics_s {
  uint8_t connection;
  uint8_t reset;
};
struct connection_get_scheduling_details_s {
  uint8_t connection;
  uint32_t access_address;
  uint8_t role;
  uint32_t crc_init;
  uint16_t interval;
  uint16_t supervision_timeout;
  uint8_t central_clock_accuracy;
  uint8_t central_phy;
  uint8_t peripheral_phy;
  uint8_t channel_selection_algorithm;
  uint8_t hop;
  sl_bt_connection_channel_map_t *channel_map;
  uint8_t channel;
  uint16_t event_counter;
  uint32_t start_time_us;
};
struct connection_close_s {
  uint8_t connection;
};
struct connection_forcefully_close_s {
  uint8_t connection;
};
struct connection_get_rssi_s {
  uint8_t connection;
};
struct gatt_set_max_mtu_s {
  uint16_t max_mtu;
  uint16_t max_mtu_out;
};
struct gatt_discover_primary_services_s {
  uint8_t connection;
};
struct gatt_discover_primary_services_by_uuid_s {
  uint8_t connection;
  size_t uuid_len;
  uint8_t *uuid;
};
struct gatt_find_included_services_s {
  uint8_t connection;
  uint32_t service;
};
struct gatt_discover_characteristics_s {
  uint8_t connection;
  uint32_t service;
};
struct gatt_discover_characteristics_by_uuid_s {
  uint8_t connection;
  uint32_t service;
  size_t uuid_len;
  uint8_t *uuid;
};
struct gatt_discover_descriptors_s {
  uint8_t connection;
  uint16_t characteristic;
};
struct gatt_discover_characteristic_descriptors_s {
  uint8_t connection;
  uint16_t start;
  uint16_t end;
};
struct gatt_set_characteristic_notification_s {
  uint8_t connection;
  uint16_t characteristic;
  uint8_t flags;
};
struct gatt_send_characteristic_confirmation_s {
  uint8_t connection;
};
struct gatt_read_characteristic_value_s {
  uint8_t connection;
  uint16_t characteristic;
};
struct gatt_read_characteristic_value_from_offset_s {
  uint8_t connection;
  uint16_t characteristic;
  uint16_t offset;
  uint16_t maxlen;
};
struct gatt_read_multiple_characteristic_values_s {
  uint8_t connection;
  size_t characteristic_list_len;
  uint8_t *characteristic_list;
};
struct gatt_read_characteristic_value_by_uuid_s {
  uint8_t connection;
  uint32_t service;
  size_t uuid_len;
  uint8_t *uuid;
};
struct gatt_write_characteristic_value_s {
  uint8_t connection;
  uint16_t characteristic;
  size_t value_len;
  uint8_t *value;
};
struct gatt_write_characteristic_value_without_response_s {
  uint8_t connection;
  uint16_t characteristic;
  size_t value_len;
  uint8_t *value;
  uint16_t sent_len;
};
struct gatt_prepare_characteristic_value_write_s {
  uint8_t connection;
  uint16_t characteristic;
  uint16_t offset;
  size_t value_len;
  uint8_t *value;
  uint16_t sent_len;
};
struct gatt_prepare_characteristic_value_reliable_write_s {
  uint8_t connection;
  uint16_t characteristic;
  uint16_t offset;
  size_t value_len;
  uint8_t *value;
  uint16_t sent_len;
};
struct gatt_execute_characteristic_value_write_s {
  uint8_t connection;
  uint8_t flags;
};
struct gatt_read_descriptor_value_s {
  uint8_t connection;
  uint16_t descriptor;
};
struct gatt_write_descriptor_value_s {
  uint8_t connection;
  uint16_t descriptor;
  size_t value_len;
  uint8_t *value;
};
struct gatt_server_set_max_mtu_s {
  uint16_t max_mtu;
  uint16_t max_mtu_out;
};
struct gatt_server_get_mtu_s {
  uint8_t connection;
  uint16_t mtu;
};
struct gatt_server_find_attribute_s {
  uint16_t start;
  size_t type_len;
  uint8_t *type;
  uint16_t attribute;
};
struct gatt_server_read_attribute_value_s {
  uint16_t attribute;
  uint16_t offset;
  size_t value_max_len;
  size_t *value_len;
  uint8_t *value;
};
struct gatt_server_read_attribute_type_s {
  uint16_t attribute;
  size_t type_max_len;
  size_t *type_len;
  uint8_t *type;
};
struct gatt_server_write_attribute_value_s {
  uint16_t attribute;
  uint16_t offset;
  size_t value_len;
  uint8_t *value;
};
struct gatt_server_send_user_read_response_s {
  uint8_t connection;
  uint16_t characteristic;
  uint8_t att_errorcode;
  size_t value_len;
  uint8_t *value;
  uint16_t sent_len;
};
struct gatt_server_send_user_write_response_s {
  uint8_t connection;
  uint16_t characteristic;
  uint8_t att_errorcode;
};
struct gatt_server_send_notification_s {
  uint8_t connection;
  uint16_t characteristic;
  size_t value_len;
  uint8_t *value;
};
struct gatt_server_send_indication_s {
  uint8_t connection;
  uint16_t characteristic;
  size_t value_len;
  uint8_t *value;
};
struct gatt_server_notify_all_s {
  uint16_t characteristic;
  size_t value_len;
  uint8_t *value;
};
struct gatt_server_read_client_configuration_s {
  uint8_t connection;
  uint16_t characteristic;
  uint16_t client_config_flags;
};
struct gatt_server_send_user_prepare_write_response_s {
  uint8_t connection;
  uint16_t characteristic;
  uint8_t att_errorcode;
  uint16_t offset;
  size_t value_len;
  uint8_t *value;
};
struct gatt_server_set_capabilities_s {
  uint32_t caps;
  uint32_t reserved;
};
struct gatt_server_enable_capabilities_s {
  uint32_t caps;
};
struct gatt_server_disable_capabilities_s {
  uint32_t caps;
};
struct gatt_server_get_enabled_capabilities_s {
  uint32_t caps;
};
struct gatt_server_read_client_supported_features_s {
  uint8_t connection;
  uint8_t client_features;
};
struct nvm_save_s {
  uint16_t key;
  size_t value_len;
  uint8_t *value;
};
struct nvm_load_s {
  uint16_t key;
  size_t value_max_len;
  size_t *value_len;
  uint8_t *value;
};
struct nvm_erase_s {
  uint16_t key;
};
struct nvm_erase_all_s {
};
struct test_dtm_tx_v4_s {
  uint8_t packet_type;
  uint8_t length;
  uint8_t channel;
  uint8_t phy;
  int8_t power_level;
};
struct test_dtm_tx_cw_s {
  uint8_t packet_type;
  uint8_t channel;
  uint8_t phy;
  int16_t power_level;
};
struct test_dtm_rx_s {
  uint8_t channel;
  uint8_t phy;
};
struct test_dtm_end_s {
};
struct sm_configure_s {
  uint8_t flags;
  uint8_t io_capabilities;
};
struct sm_set_minimum_key_size_s {
  uint8_t minimum_key_size;
};
struct sm_set_debug_mode_s {
};
struct sm_add_to_whitelist_s {
  bd_addr address;
  uint8_t address_type;
};
struct sm_store_bonding_configuration_s {
  uint8_t max_bonding_count;
  uint8_t policy_flags;
};
struct sm_set_bondable_mode_s {
  uint8_t bondable;
};
struct sm_set_passkey_s {
  int32_t passkey;
};
struct sm_increase_security_s {
  uint8_t connection;
};
struct sm_enter_passkey_s {
  uint8_t connection;
  int32_t passkey;
};
struct sm_passkey_confirm_s {
  uint8_t connection;
  uint8_t confirm;
};
struct sm_bonding_confirm_s {
  uint8_t connection;
  uint8_t confirm;
};
struct sm_delete_bonding_s {
  uint8_t bonding;
};
struct sm_delete_bondings_s {
};
struct sm_get_bonding_handles_s {
  uint32_t reserved;
  uint32_t num_bondings;
  size_t bondings_max_len;
  size_t *bondings_len;
  uint8_t *bondings;
};
struct sm_get_bonding_details_s {
  uint32_t bonding;
  bd_addr address;
  uint8_t address_type;
  uint8_t security_mode;
  uint8_t key_size;
};
struct sm_find_bonding_by_address_s {
  bd_addr address;
  uint32_t bonding;
  uint8_t security_mode;
  uint8_t key_size;
};
struct sm_resolve_rpa_s {
  bd_addr rpa;
  bd_addr address;
  uint8_t address_type;
  uint32_t bonding;
};
struct sm_set_bonding_key_s {
  uint32_t bonding;
  uint8_t key_type;
  aes_key_128 key;
};
struct sm_set_legacy_oob_s {
  uint8_t enable;
  aes_key_128 oob_data;
};
struct sm_set_oob_s {
  uint8_t enable;
  aes_key_128 random;
  aes_key_128 confirm;
};
struct sm_set_remote_oob_s {
  uint8_t enable;
  aes_key_128 random;
  aes_key_128 confirm;
};
struct sm_set_bonding_data_s {
  uint8_t connection;
  uint8_t type;
  size_t data_len;
  uint8_t *data;
};
struct ota_set_device_name_s {
  size_t name_len;
  uint8_t *name;
};
struct ota_set_advertising_data_s {
  uint8_t packet_type;
  size_t adv_data_len;
  uint8_t *adv_data;
};
struct ota_set_configuration_s {
  uint32_t flags;
};
struct ota_set_rf_path_s {
  uint8_t enable;
  uint8_t antenna;
};
struct coex_set_options_s {
  uint32_t mask;
  uint32_t options;
};
struct coex_set_parameters_s {
  uint8_t priority;
  uint8_t request;
  uint8_t pwm_period;
  uint8_t pwm_dutycycle;
};
struct coex_set_directional_priority_pulse_s {
  uint8_t pulse;
};
struct coex_get_parameters_s {
  uint8_t priority;
  uint8_t request;
  uint8_t pwm_period;
  uint8_t pwm_dutycycle;
};
struct coex_get_counters_s {
  uint8_t reset;
  size_t counters_max_len;
  size_t *counters_len;
  uint8_t *counters;
};
struct sync_set_parameters_s {
  uint16_t skip;
  uint16_t timeout;
  uint32_t flags;
};
struct sync_open_s {
  bd_addr address;
  uint8_t address_type;
  uint8_t adv_sid;
  uint16_t sync;
};
struct sync_set_reporting_mode_s {
  uint16_t sync;
  uint8_t reporting_mode;
};
struct sync_update_sync_parameters_s {
  uint16_t sync;
  uint16_t skip;
  uint16_t timeout;
};
struct sync_close_s {
  uint16_t sync;
};
struct l2cap_open_le_channel_s {
  uint8_t connection;
  uint16_t spsm;
  uint16_t max_sdu;
  uint16_t max_pdu;
  uint16_t credit;
  uint16_t cid;
};
struct l2cap_send_le_channel_open_response_s {
  uint8_t connection;
  uint16_t cid;
  uint16_t max_sdu;
  uint16_t max_pdu;
  uint16_t credit;
  uint16_t errorcode;
};
struct l2cap_channel_send_data_s {
  uint8_t connection;
  uint16_t cid;
  size_t data_len;
  uint8_t *data;
};
struct l2cap_channel_send_credit_s {
  uint8_t connection;
  uint16_t cid;
  uint16_t credit;
};
struct l2cap_close_channel_s {
  uint8_t connection;
  uint16_t cid;
};
struct cte_transmitter_set_dtm_parameters_s {
  uint8_t cte_length;
  uint8_t cte_type;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_transmitter_clear_dtm_parameters_s {
};
struct cte_transmitter_enable_connection_cte_s {
  uint8_t connection;
  uint8_t cte_types;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_transmitter_disable_connection_cte_s {
  uint8_t connection;
};
struct cte_transmitter_enable_connectionless_cte_s {
  uint8_t handle;
  uint8_t cte_length;
  uint8_t cte_type;
  uint8_t cte_count;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_transmitter_disable_connectionless_cte_s {
  uint8_t handle;
};
struct cte_transmitter_enable_silabs_cte_s {
  uint8_t handle;
  uint8_t cte_length;
  uint8_t cte_type;
  uint8_t cte_count;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_transmitter_disable_silabs_cte_s {
  uint8_t handle;
};
struct cte_receiver_set_dtm_parameters_s {
  uint8_t cte_length;
  uint8_t cte_type;
  uint8_t slot_durations;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_receiver_clear_dtm_parameters_s {
};
struct cte_receiver_set_sync_cte_type_s {
  uint8_t sync_cte_type;
};
struct cte_receiver_set_default_sync_receive_parameters_s {
  uint8_t mode;
  uint16_t skip;
  uint16_t timeout;
  uint8_t sync_cte_type;
  uint8_t reporting_mode;
};
struct cte_receiver_set_sync_receive_parameters_s {
  uint8_t connection;
  uint8_t mode;
  uint16_t skip;
  uint16_t timeout;
  uint8_t sync_cte_type;
  uint8_t reporting_mode;
};
struct cte_receiver_configure_s {
  uint8_t flags;
};
struct cte_receiver_enable_connection_cte_s {
  uint8_t connection;
  uint16_t interval;
  uint8_t cte_length;
  uint8_t cte_type;
  uint8_t slot_durations;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_receiver_disable_connection_cte_s {
  uint8_t connection;
};
struct cte_receiver_enable_connectionless_cte_s {
  uint16_t sync;
  uint8_t slot_durations;
  uint8_t cte_count;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_receiver_disable_connectionless_cte_s {
  uint16_t sync;
};
struct cte_receiver_enable_silabs_cte_s {
  uint8_t slot_durations;
  uint8_t cte_count;
  size_t switching_pattern_len;
  uint8_t *switching_pattern;
};
struct cte_receiver_disable_silabs_cte_s {
};
struct gattdb_new_session_s {
  uint16_t session;
};
struct gattdb_add_service_s {
  uint16_t session;
  uint8_t type;
  uint8_t property;
  size_t uuid_len;
  uint8_t *uuid;
  uint16_t service;
};
struct gattdb_remove_service_s {
  uint16_t session;
  uint16_t service;
};
struct gattdb_add_included_service_s {
  uint16_t session;
  uint16_t service;
  uint16_t included_service;
  uint16_t attribute;
};
struct gattdb_remove_included_service_s {
  uint16_t session;
  uint16_t attribute;
};
struct gattdb_add_uuid16_characteristic_s {
  uint16_t session;
  uint16_t service;
  uint16_t property;
  uint16_t security;
  uint8_t flag;
  sl_bt_uuid_16_t uuid;
  uint8_t value_type;
  uint16_t maxlen;
  size_t value_len;
  uint8_t *value;
  uint16_t characteristic;
};
struct gattdb_add_uuid128_characteristic_s {
  uint16_t session;
  uint16_t service;
  uint16_t property;
  uint16_t security;
  uint8_t flag;
  uuid_128 uuid;
  uint8_t value_type;
  uint16_t maxlen;
  size_t value_len;
  uint8_t *value;
  uint16_t characteristic;
};
struct gattdb_remove_characteristic_s {
  uint16_t session;
  uint16_t characteristic;
};
struct gattdb_add_uuid16_descriptor_s {
  uint16_t session;
  uint16_t characteristic;
  uint16_t property;
  uint16_t security;
  sl_bt_uuid_16_t uuid;
  uint8_t value_type;
  uint16_t maxlen;
  size_t value_len;
  uint8_t *value;
  uint16_t descriptor;
};
struct gattdb_add_uuid128_descriptor_s {
  uint16_t session;
  uint16_t characteristic;
  uint16_t property;
  uint16_t security;
  uuid_128 uuid;
  uint8_t value_type;
  uint16_t maxlen;
  size_t value_len;
  uint8_t *value;
  uint16_t descriptor;
};
struct gattdb_remove_descriptor_s {
  uint16_t session;
  uint16_t descriptor;
};
struct gattdb_start_service_s {
  uint16_t session;
  uint16_t service;
};
struct gattdb_stop_service_s {
  uint16_t session;
  uint16_t service;
};
struct gattdb_start_characteristic_s {
  uint16_t session;
  uint16_t characteristic;
};
struct gattdb_stop_characteristic_s {
  uint16_t session;
  uint16_t characteristic;
};
struct gattdb_commit_s {
  uint16_t session;
};
struct gattdb_abort_s {
  uint16_t session;
};
struct connection_analyzer_start_s {
  uint32_t access_address;
  uint32_t crc_init;
  uint16_t interval;
  uint16_t supervision_timeout;
  uint8_t central_clock_accuracy;
  uint8_t central_phy;
  uint8_t peripheral_phy;
  uint8_t channel_selection_algorithm;
  uint8_t hop;
  sl_bt_connection_channel_map_t *channel_map;
  uint8_t channel;
  uint16_t event_counter;
  int32_t start_time_us;
  uint32_t flags;
  uint8_t analyzer;
};
struct connection_analyzer_stop_s {
  uint8_t analyzer;
};
struct sync_scanner_set_sync_parameters_s {
  uint16_t skip;
  uint16_t timeout;
  uint8_t reporting_mode;
};
struct sync_scanner_open_s {
  bd_addr address;
  uint8_t address_type;
  uint8_t adv_sid;
  uint16_t sync;
};
struct past_receiver_set_default_sync_receive_parameters_s {
  uint8_t mode;
  uint16_t skip;
  uint16_t timeout;
  uint8_t reporting_mode;
};
struct past_receiver_set_sync_receive_parameters_s {
  uint8_t connection;
  uint8_t mode;
  uint16_t skip;
  uint16_t timeout;
  uint8_t reporting_mode;
};
struct advertiser_past_transfer_s {
  uint8_t connection;
  uint16_t service_data;
  uint8_t advertising_set;
};
struct pawr_sync_set_sync_subevents_s {
  uint16_t sync;
  size_t subevents_len;
  uint8_t *subevents;
};
struct pawr_sync_set_response_data_s {
  uint16_t sync;
  uint16_t request_event;
  uint8_t request_subevent;
  uint8_t response_subevent;
  uint8_t response_slot;
  size_t response_data_len;
  uint8_t *response_data;
};
struct pawr_advertiser_start_s {
  uint8_t advertising_set;
  uint16_t interval_min;
  uint16_t interval_max;
  uint32_t flags;
  uint8_t num_subevents;
  uint8_t subevent_interval;
  uint8_t response_slot_delay;
  uint8_t response_slot_spacing;
  uint8_t response_slots;
};
struct pawr_advertiser_set_subevent_data_s {
  uint8_t advertising_set;
  uint8_t subevent;
  uint8_t response_slot_start;
  uint8_t response_slot_count;
  size_t adv_data_len;
  uint8_t *adv_data;
};
struct pawr_advertiser_create_connection_s {
  uint8_t advertising_set;
  uint8_t subevent;
  bd_addr address;
  uint8_t address_type;
  uint8_t connection;
};
struct pawr_advertiser_stop_s {
  uint8_t advertising_set;
};
struct legacy_advertiser_set_data_s {
  uint8_t advertising_set;
  uint8_t type;
  size_t data_len;
  uint8_t *data;
};
struct legacy_advertiser_generate_data_s {
  uint8_t advertising_set;
  uint8_t discover;
};
struct legacy_advertiser_start_s {
  uint8_t advertising_set;
  uint8_t connect;
};
struct legacy_advertiser_start_directed_s {
  uint8_t advertising_set;
  uint8_t connect;
  bd_addr peer_addr;
  uint8_t peer_addr_type;
};
struct extended_advertiser_set_phy_s {
  uint8_t advertising_set;
  uint8_t primary_phy;
  uint8_t secondary_phy;
};
struct extended_advertiser_set_data_s {
  uint8_t advertising_set;
  size_t data_len;
  uint8_t *data;
};
struct extended_advertiser_set_long_data_s {
  uint8_t advertising_set;
};
struct extended_advertiser_generate_data_s {
  uint8_t advertising_set;
  uint8_t discover;
};
struct extended_advertiser_start_s {
  uint8_t advertising_set;
  uint8_t connect;
  uint32_t flags;
};
struct extended_advertiser_start_directed_s {
  uint8_t advertising_set;
  uint8_t connect;
  uint32_t flags;
  bd_addr peer_addr;
  uint8_t peer_addr_type;
};
struct periodic_advertiser_set_data_s {
  uint8_t advertising_set;
  size_t data_len;
  uint8_t *data;
};
struct periodic_advertiser_set_long_data_s {
  uint8_t advertising_set;
};
struct periodic_advertiser_start_s {
  uint8_t advertising_set;
  uint16_t interval_min;
  uint16_t interval_max;
  uint32_t flags;
};
struct periodic_advertiser_stop_s {
  uint8_t advertising_set;
};
struct cs_security_enable_s {
  uint8_t connection;
};
struct cs_set_default_settings_s {
  uint8_t connection;
  uint8_t initiator_status;
  uint8_t reflector_status;
  uint8_t antenna_identifier;
  int8_t max_tx_power;
};
struct cs_create_config_s {
  uint8_t connection;
  uint8_t config_id;
  uint8_t create_context;
  uint8_t main_mode_type;
  uint8_t sub_mode_type;
  uint8_t min_main_mode_steps;
  uint8_t max_main_mode_steps;
  uint8_t main_mode_repetition;
  uint8_t mode_calibration_steps;
  uint8_t role;
  uint8_t rtt_type;
  uint8_t cs_sync_phy;
  sl_bt_cs_channel_map_t *channel_map;
  uint8_t channel_map_repetition;
  uint8_t channel_selection_type;
  uint8_t ch3c_shape;
  uint8_t ch3c_jump;
  uint8_t companion_signal_state;
};
struct cs_remove_config_s {
  uint8_t connection;
  uint8_t config_id;
};
struct cs_set_channel_classification_s {
  sl_bt_cs_channel_map_t *channel_map;
};
struct cs_set_procedure_parameters_s {
  uint8_t connection;
  uint8_t config_id;
  uint16_t max_procedure_len;
  uint16_t min_procedure_interval;
  uint16_t max_procedure_interval;
  uint16_t max_procedure_count;
  uint32_t min_subevent_len;
  uint32_t max_subevent_len;
  uint8_t tone_antenna_config_selection;
  uint8_t phy;
  int8_t tx_pwr_delta;
  uint8_t preferred_peer_antenna;
};
struct cs_procedure_enable_s {
  uint8_t connection;
  uint8_t enable;
  uint8_t config_id;
};
struct cs_set_antenna_configuration_s {
  size_t antenna_element_offset_len;
  uint8_t *antenna_element_offset;
};
struct cs_read_local_supported_capabilities_s {
  uint8_t num_config;
  uint16_t max_consecutive_procedures;
  uint8_t num_antennas;
  uint8_t max_antenna_paths;
  uint8_t roles;
  uint8_t optional_modes;
  uint8_t rtt_capability;
  uint8_t rtt_aa_only;
  uint8_t rtt_sounding;
  uint8_t rtt_random_payload;
  uint8_t optional_cs_sync_phys;
  uint16_t optional_subfeatures;
  uint16_t optional_t_ip1_times;
  uint16_t optional_t_ip2_times;
  uint16_t optional_t_fcs_times;
  uint16_t optional_t_pm_times;
  uint8_t t_sw_times;
};
struct cs_test_start_s {
  uint8_t main_mode_type;
  uint8_t sub_mode_type;
  uint8_t main_mode_repetition;
  uint8_t mode_calibration_steps;
  uint8_t role;
  uint8_t rtt_type;
  uint8_t cs_sync_phy;
  uint8_t antenna_selection;
  sl_bt_cs_subevent_length_t *subevent_len;
  uint16_t subevent_interval;
  int8_t tx_power;
  uint8_t t_ip1_time;
  uint8_t t_ip2_time;
  uint8_t t_fcs_time;
  uint8_t t_pm_time;
  uint8_t t_sw_time;
  uint8_t tone_antenna_config;
  uint8_t companion_signal_state;
  uint16_t drbg_nonce;
  uint16_t override_config;
  size_t override_parameters_len;
  uint8_t *override_parameters;
};
struct sync_past_transfer_s {
  uint8_t connection;
  uint16_t service_data;
  uint16_t sync;
};
struct external_bondingdb_set_data_s {
  uint8_t connection;
  uint8_t type;
  size_t data_len;
  uint8_t *data;
};
struct resolving_list_add_device_by_bonding_s {
  uint32_t bonding;
  uint8_t privacy_mode;
};
struct resolving_list_add_device_by_address_s {
  bd_addr address;
  uint8_t address_type;
  aes_key_128 key;
  uint8_t privacy_mode;
};
struct resolving_list_remove_device_by_bonding_s {
  uint32_t bonding;
};
struct resolving_list_remove_device_by_address_s {
  bd_addr address;
  uint8_t address_type;
};
struct resolving_list_remove_all_devices_s {
};
struct accept_list_add_device_by_bonding_s {
  uint32_t bonding;
};
struct accept_list_add_device_by_address_s {
  bd_addr address;
  uint8_t address_type;
};
struct accept_list_remove_device_by_bonding_s {
  uint32_t bonding;
};
struct accept_list_remove_device_by_address_s {
  bd_addr address;
  uint8_t address_type;
};
struct accept_list_remove_all_devices_s {
};
struct resource_get_status_s {
  uint32_t total_bytes;
  uint32_t free_bytes;
};
struct resource_set_report_threshold_s {
  uint32_t low;
  uint32_t high;
};
struct resource_enable_connection_tx_report_s {
  uint16_t packet_count;
};
struct resource_get_connection_tx_status_s {
  uint8_t connection;
  uint16_t flags;
  uint16_t packet_count;
  uint32_t data_len;
};
struct resource_disable_connection_tx_report_s {
};
struct user_message_to_target_s {
  size_t data_len;
  uint8_t *data;
  size_t response_max_len;
  size_t *response_len;
  uint8_t *response;
};
struct user_manage_event_filter_s {
  size_t data_len;
  uint8_t *data;
};
struct user_reset_to_dfu_s {
};
struct command_s {
  struct command_s *next, *previous;
  enum CMD_TYPE type;
  union {
    struct dfu_flash_set_address_s dfu_flash_set_address;
    struct dfu_flash_upload_s dfu_flash_upload;
    struct dfu_flash_upload_finish_s dfu_flash_upload_finish;
    struct system_hello_s system_hello;
    struct system_start_bluetooth_s system_start_bluetooth;
    struct system_stop_bluetooth_s system_stop_bluetooth;
    struct system_forcefully_stop_bluetooth_s system_forcefully_stop_bluetooth;
    struct system_get_version_s system_get_version;
    struct system_reset_s system_reset;
    struct system_halt_s system_halt;
    struct system_linklayer_configure_s system_linklayer_configure;
    struct system_set_tx_power_s system_set_tx_power;
    struct system_get_tx_power_setting_s system_get_tx_power_setting;
    struct system_set_identity_address_s system_set_identity_address;
    struct system_get_identity_address_s system_get_identity_address;
    struct system_get_random_data_s system_get_random_data;
    struct system_data_buffer_write_s system_data_buffer_write;
    struct system_data_buffer_clear_s system_data_buffer_clear;
    struct system_get_counters_s system_get_counters;
    struct system_set_lazy_soft_timer_s system_set_lazy_soft_timer;
    struct gap_set_privacy_mode_s gap_set_privacy_mode;
    struct gap_set_data_channel_classification_s gap_set_data_channel_classification;
    struct gap_enable_whitelisting_s gap_enable_whitelisting;
    struct gap_set_identity_address_s gap_set_identity_address;
    struct advertiser_create_set_s advertiser_create_set;
    struct advertiser_configure_s advertiser_configure;
    struct advertiser_set_timing_s advertiser_set_timing;
    struct advertiser_set_channel_map_s advertiser_set_channel_map;
    struct advertiser_set_tx_power_s advertiser_set_tx_power;
    struct advertiser_set_report_scan_request_s advertiser_set_report_scan_request;
    struct advertiser_set_random_address_s advertiser_set_random_address;
    struct advertiser_clear_random_address_s advertiser_clear_random_address;
    struct advertiser_stop_s advertiser_stop;
    struct advertiser_delete_set_s advertiser_delete_set;
    struct advertiser_set_phy_s advertiser_set_phy;
    struct advertiser_set_configuration_s advertiser_set_configuration;
    struct advertiser_clear_configuration_s advertiser_clear_configuration;
    struct advertiser_set_data_s advertiser_set_data;
    struct advertiser_set_long_data_s advertiser_set_long_data;
    struct advertiser_start_s advertiser_start;
    struct advertiser_start_periodic_advertising_s advertiser_start_periodic_advertising;
    struct advertiser_stop_periodic_advertising_s advertiser_stop_periodic_advertising;
    struct scanner_set_parameters_s scanner_set_parameters;
    struct scanner_set_parameters_and_filter_s scanner_set_parameters_and_filter;
    struct scanner_stop_s scanner_stop;
    struct scanner_set_timing_s scanner_set_timing;
    struct scanner_set_mode_s scanner_set_mode;
    struct scanner_start_s scanner_start;
    struct connection_set_default_parameters_s connection_set_default_parameters;
    struct connection_set_default_preferred_phy_s connection_set_default_preferred_phy;
    struct connection_set_default_data_length_s connection_set_default_data_length;
    struct connection_open_s connection_open;
    struct connection_set_parameters_s connection_set_parameters;
    struct connection_set_preferred_phy_s connection_set_preferred_phy;
    struct connection_disable_slave_latency_s connection_disable_slave_latency;
    struct connection_get_median_rssi_s connection_get_median_rssi;
    struct connection_read_channel_map_s connection_read_channel_map;
    struct connection_set_power_reporting_s connection_set_power_reporting;
    struct connection_set_remote_power_reporting_s connection_set_remote_power_reporting;
    struct connection_get_tx_power_s connection_get_tx_power;
    struct connection_get_remote_tx_power_s connection_get_remote_tx_power;
    struct connection_set_tx_power_s connection_set_tx_power;
    struct connection_read_remote_used_features_s connection_read_remote_used_features;
    struct connection_get_security_status_s connection_get_security_status;
    struct connection_set_data_length_s connection_set_data_length;
    struct connection_read_statistics_s connection_read_statistics;
    struct connection_get_scheduling_details_s connection_get_scheduling_details;
    struct connection_close_s connection_close;
    struct connection_forcefully_close_s connection_forcefully_close;
    struct connection_get_rssi_s connection_get_rssi;
    struct gatt_set_max_mtu_s gatt_set_max_mtu;
    struct gatt_discover_primary_services_s gatt_discover_primary_services;
    struct gatt_discover_primary_services_by_uuid_s gatt_discover_primary_services_by_uuid;
    struct gatt_find_included_services_s gatt_find_included_services;
    struct gatt_discover_characteristics_s gatt_discover_characteristics;
    struct gatt_discover_characteristics_by_uuid_s gatt_discover_characteristics_by_uuid;
    struct gatt_discover_descriptors_s gatt_discover_descriptors;
    struct gatt_discover_characteristic_descriptors_s gatt_discover_characteristic_descriptors;
    struct gatt_set_characteristic_notification_s gatt_set_characteristic_notification;
    struct gatt_send_characteristic_confirmation_s gatt_send_characteristic_confirmation;
    struct gatt_read_characteristic_value_s gatt_read_characteristic_value;
    struct gatt_read_characteristic_value_from_offset_s gatt_read_characteristic_value_from_offset;
    struct gatt_read_multiple_characteristic_values_s gatt_read_multiple_characteristic_values;
    struct gatt_read_characteristic_value_by_uuid_s gatt_read_characteristic_value_by_uuid;
    struct gatt_write_characteristic_value_s gatt_write_characteristic_value;
    struct gatt_write_characteristic_value_without_response_s gatt_write_characteristic_value_without_response;
    struct gatt_prepare_characteristic_value_write_s gatt_prepare_characteristic_value_write;
    struct gatt_prepare_characteristic_value_reliable_write_s gatt_prepare_characteristic_value_reliable_write;
    struct gatt_execute_characteristic_value_write_s gatt_execute_characteristic_value_write;
    struct gatt_read_descriptor_value_s gatt_read_descriptor_value;
    struct gatt_write_descriptor_value_s gatt_write_descriptor_value;
    struct gatt_server_set_max_mtu_s gatt_server_set_max_mtu;
    struct gatt_server_get_mtu_s gatt_server_get_mtu;
    struct gatt_server_find_attribute_s gatt_server_find_attribute;
    struct gatt_server_read_attribute_value_s gatt_server_read_attribute_value;
    struct gatt_server_read_attribute_type_s gatt_server_read_attribute_type;
    struct gatt_server_write_attribute_value_s gatt_server_write_attribute_value;
    struct gatt_server_send_user_read_response_s gatt_server_send_user_read_response;
    struct gatt_server_send_user_write_response_s gatt_server_send_user_write_response;
    struct gatt_server_send_notification_s gatt_server_send_notification;
    struct gatt_server_send_indication_s gatt_server_send_indication;
    struct gatt_server_notify_all_s gatt_server_notify_all;
    struct gatt_server_read_client_configuration_s gatt_server_read_client_configuration;
    struct gatt_server_send_user_prepare_write_response_s gatt_server_send_user_prepare_write_response;
    struct gatt_server_set_capabilities_s gatt_server_set_capabilities;
    struct gatt_server_enable_capabilities_s gatt_server_enable_capabilities;
    struct gatt_server_disable_capabilities_s gatt_server_disable_capabilities;
    struct gatt_server_get_enabled_capabilities_s gatt_server_get_enabled_capabilities;
    struct gatt_server_read_client_supported_features_s gatt_server_read_client_supported_features;
    struct nvm_save_s nvm_save;
    struct nvm_load_s nvm_load;
    struct nvm_erase_s nvm_erase;
    struct nvm_erase_all_s nvm_erase_all;
    struct test_dtm_tx_v4_s test_dtm_tx_v4;
    struct test_dtm_tx_cw_s test_dtm_tx_cw;
    struct test_dtm_rx_s test_dtm_rx;
    struct test_dtm_end_s test_dtm_end;
    struct sm_configure_s sm_configure;
    struct sm_set_minimum_key_size_s sm_set_minimum_key_size;
    struct sm_set_debug_mode_s sm_set_debug_mode;
    struct sm_add_to_whitelist_s sm_add_to_whitelist;
    struct sm_store_bonding_configuration_s sm_store_bonding_configuration;
    struct sm_set_bondable_mode_s sm_set_bondable_mode;
    struct sm_set_passkey_s sm_set_passkey;
    struct sm_increase_security_s sm_increase_security;
    struct sm_enter_passkey_s sm_enter_passkey;
    struct sm_passkey_confirm_s sm_passkey_confirm;
    struct sm_bonding_confirm_s sm_bonding_confirm;
    struct sm_delete_bonding_s sm_delete_bonding;
    struct sm_delete_bondings_s sm_delete_bondings;
    struct sm_get_bonding_handles_s sm_get_bonding_handles;
    struct sm_get_bonding_details_s sm_get_bonding_details;
    struct sm_find_bonding_by_address_s sm_find_bonding_by_address;
    struct sm_resolve_rpa_s sm_resolve_rpa;
    struct sm_set_bonding_key_s sm_set_bonding_key;
    struct sm_set_legacy_oob_s sm_set_legacy_oob;
    struct sm_set_oob_s sm_set_oob;
    struct sm_set_remote_oob_s sm_set_remote_oob;
    struct sm_set_bonding_data_s sm_set_bonding_data;
    struct ota_set_device_name_s ota_set_device_name;
    struct ota_set_advertising_data_s ota_set_advertising_data;
    struct ota_set_configuration_s ota_set_configuration;
    struct ota_set_rf_path_s ota_set_rf_path;
    struct coex_set_options_s coex_set_options;
    struct coex_set_parameters_s coex_set_parameters;
    struct coex_set_directional_priority_pulse_s coex_set_directional_priority_pulse;
    struct coex_get_parameters_s coex_get_parameters;
    struct coex_get_counters_s coex_get_counters;
    struct sync_set_parameters_s sync_set_parameters;
    struct sync_open_s sync_open;
    struct sync_set_reporting_mode_s sync_set_reporting_mode;
    struct sync_update_sync_parameters_s sync_update_sync_parameters;
    struct sync_close_s sync_close;
    struct l2cap_open_le_channel_s l2cap_open_le_channel;
    struct l2cap_send_le_channel_open_response_s l2cap_send_le_channel_open_response;
    struct l2cap_channel_send_data_s l2cap_channel_send_data;
    struct l2cap_channel_send_credit_s l2cap_channel_send_credit;
    struct l2cap_close_channel_s l2cap_close_channel;
    struct cte_transmitter_set_dtm_parameters_s cte_transmitter_set_dtm_parameters;
    struct cte_transmitter_clear_dtm_parameters_s cte_transmitter_clear_dtm_parameters;
    struct cte_transmitter_enable_connection_cte_s cte_transmitter_enable_connection_cte;
    struct cte_transmitter_disable_connection_cte_s cte_transmitter_disable_connection_cte;
    struct cte_transmitter_enable_connectionless_cte_s cte_transmitter_enable_connectionless_cte;
    struct cte_transmitter_disable_connectionless_cte_s cte_transmitter_disable_connectionless_cte;
    struct cte_transmitter_enable_silabs_cte_s cte_transmitter_enable_silabs_cte;
    struct cte_transmitter_disable_silabs_cte_s cte_transmitter_disable_silabs_cte;
    struct cte_receiver_set_dtm_parameters_s cte_receiver_set_dtm_parameters;
    struct cte_receiver_clear_dtm_parameters_s cte_receiver_clear_dtm_parameters;
    struct cte_receiver_set_sync_cte_type_s cte_receiver_set_sync_cte_type;
    struct cte_receiver_set_default_sync_receive_parameters_s cte_receiver_set_default_sync_receive_parameters;
    struct cte_receiver_set_sync_receive_parameters_s cte_receiver_set_sync_receive_parameters;
    struct cte_receiver_configure_s cte_receiver_configure;
    struct cte_receiver_enable_connection_cte_s cte_receiver_enable_connection_cte;
    struct cte_receiver_disable_connection_cte_s cte_receiver_disable_connection_cte;
    struct cte_receiver_enable_connectionless_cte_s cte_receiver_enable_connectionless_cte;
    struct cte_receiver_disable_connectionless_cte_s cte_receiver_disable_connectionless_cte;
    struct cte_receiver_enable_silabs_cte_s cte_receiver_enable_silabs_cte;
    struct cte_receiver_disable_silabs_cte_s cte_receiver_disable_silabs_cte;
    struct gattdb_new_session_s gattdb_new_session;
    struct gattdb_add_service_s gattdb_add_service;
    struct gattdb_remove_service_s gattdb_remove_service;
    struct gattdb_add_included_service_s gattdb_add_included_service;
    struct gattdb_remove_included_service_s gattdb_remove_included_service;
    struct gattdb_add_uuid16_characteristic_s gattdb_add_uuid16_characteristic;
    struct gattdb_add_uuid128_characteristic_s gattdb_add_uuid128_characteristic;
    struct gattdb_remove_characteristic_s gattdb_remove_characteristic;
    struct gattdb_add_uuid16_descriptor_s gattdb_add_uuid16_descriptor;
    struct gattdb_add_uuid128_descriptor_s gattdb_add_uuid128_descriptor;
    struct gattdb_remove_descriptor_s gattdb_remove_descriptor;
    struct gattdb_start_service_s gattdb_start_service;
    struct gattdb_stop_service_s gattdb_stop_service;
    struct gattdb_start_characteristic_s gattdb_start_characteristic;
    struct gattdb_stop_characteristic_s gattdb_stop_characteristic;
    struct gattdb_commit_s gattdb_commit;
    struct gattdb_abort_s gattdb_abort;
    struct connection_analyzer_start_s connection_analyzer_start;
    struct connection_analyzer_stop_s connection_analyzer_stop;
    struct sync_scanner_set_sync_parameters_s sync_scanner_set_sync_parameters;
    struct sync_scanner_open_s sync_scanner_open;
    struct past_receiver_set_default_sync_receive_parameters_s past_receiver_set_default_sync_receive_parameters;
    struct past_receiver_set_sync_receive_parameters_s past_receiver_set_sync_receive_parameters;
    struct advertiser_past_transfer_s advertiser_past_transfer;
    struct pawr_sync_set_sync_subevents_s pawr_sync_set_sync_subevents;
    struct pawr_sync_set_response_data_s pawr_sync_set_response_data;
    struct pawr_advertiser_start_s pawr_advertiser_start;
    struct pawr_advertiser_set_subevent_data_s pawr_advertiser_set_subevent_data;
    struct pawr_advertiser_create_connection_s pawr_advertiser_create_connection;
    struct pawr_advertiser_stop_s pawr_advertiser_stop;
    struct legacy_advertiser_set_data_s legacy_advertiser_set_data;
    struct legacy_advertiser_generate_data_s legacy_advertiser_generate_data;
    struct legacy_advertiser_start_s legacy_advertiser_start;
    struct legacy_advertiser_start_directed_s legacy_advertiser_start_directed;
    struct extended_advertiser_set_phy_s extended_advertiser_set_phy;
    struct extended_advertiser_set_data_s extended_advertiser_set_data;
    struct extended_advertiser_set_long_data_s extended_advertiser_set_long_data;
    struct extended_advertiser_generate_data_s extended_advertiser_generate_data;
    struct extended_advertiser_start_s extended_advertiser_start;
    struct extended_advertiser_start_directed_s extended_advertiser_start_directed;
    struct periodic_advertiser_set_data_s periodic_advertiser_set_data;
    struct periodic_advertiser_set_long_data_s periodic_advertiser_set_long_data;
    struct periodic_advertiser_start_s periodic_advertiser_start;
    struct periodic_advertiser_stop_s periodic_advertiser_stop;
    struct cs_security_enable_s cs_security_enable;
    struct cs_set_default_settings_s cs_set_default_settings;
    struct cs_create_config_s cs_create_config;
    struct cs_remove_config_s cs_remove_config;
    struct cs_set_channel_classification_s cs_set_channel_classification;
    struct cs_set_procedure_parameters_s cs_set_procedure_parameters;
    struct cs_procedure_enable_s cs_procedure_enable;
    struct cs_set_antenna_configuration_s cs_set_antenna_configuration;
    struct cs_read_local_supported_capabilities_s cs_read_local_supported_capabilities;
    struct cs_test_start_s cs_test_start;
    struct sync_past_transfer_s sync_past_transfer;
    struct external_bondingdb_set_data_s external_bondingdb_set_data;
    struct resolving_list_add_device_by_bonding_s resolving_list_add_device_by_bonding;
    struct resolving_list_add_device_by_address_s resolving_list_add_device_by_address;
    struct resolving_list_remove_device_by_bonding_s resolving_list_remove_device_by_bonding;
    struct resolving_list_remove_device_by_address_s resolving_list_remove_device_by_address;
    struct resolving_list_remove_all_devices_s resolving_list_remove_all_devices;
    struct accept_list_add_device_by_bonding_s accept_list_add_device_by_bonding;
    struct accept_list_add_device_by_address_s accept_list_add_device_by_address;
    struct accept_list_remove_device_by_bonding_s accept_list_remove_device_by_bonding;
    struct accept_list_remove_device_by_address_s accept_list_remove_device_by_address;
    struct accept_list_remove_all_devices_s accept_list_remove_all_devices;
    struct resource_get_status_s resource_get_status;
    struct resource_set_report_threshold_s resource_set_report_threshold;
    struct resource_enable_connection_tx_report_s resource_enable_connection_tx_report;
    struct resource_get_connection_tx_status_s resource_get_connection_tx_status;
    struct resource_disable_connection_tx_report_s resource_disable_connection_tx_report;
    struct user_message_to_target_s user_message_to_target;
    struct user_manage_event_filter_s user_manage_event_filter;
    struct user_reset_to_dfu_s user_reset_to_dfu;
  };
  sl_status_t result;
};
void command_process(void);
void push_dfu_flash_set_address(uint32_t address);
void push_dfu_flash_upload(size_t data_len,uint8_t *data);
void push_dfu_flash_upload_finish();
void push_system_hello();
void push_system_start_bluetooth();
void push_system_stop_bluetooth();
void push_system_forcefully_stop_bluetooth();
void push_system_get_version();
void push_system_reset(uint8_t dfu);
void push_system_halt(uint8_t halt);
void push_system_linklayer_configure(uint8_t key,size_t data_len,uint8_t *data);
void push_system_set_tx_power(int16_t min_power,int16_t max_power);
void push_system_get_tx_power_setting();
void push_system_set_identity_address(bd_addr address,uint8_t type);
void push_system_get_identity_address();
void push_system_get_random_data(uint8_t length);
void push_system_data_buffer_write(size_t data_len,uint8_t *data);
void push_system_data_buffer_clear();
void push_system_get_counters(uint8_t reset);
void push_system_set_lazy_soft_timer(uint32_t time,uint32_t slack,uint8_t handle,uint8_t single_shot);
void push_gap_set_privacy_mode(uint8_t privacy,uint8_t interval);
void push_gap_set_data_channel_classification(size_t channel_map_len,uint8_t *channel_map);
void push_gap_enable_whitelisting(uint8_t enable);
void push_gap_set_identity_address(bd_addr address,uint8_t addr_type);
void push_advertiser_create_set();
void push_advertiser_configure(uint8_t advertising_set,uint32_t flags);
void push_advertiser_set_timing(uint8_t advertising_set,uint32_t interval_min,uint32_t interval_max,uint16_t duration,uint8_t maxevents);
void push_advertiser_set_channel_map(uint8_t advertising_set,uint8_t channel_map);
void push_advertiser_set_tx_power(uint8_t advertising_set,int16_t power);
void push_advertiser_set_report_scan_request(uint8_t advertising_set,uint8_t report_scan_req);
void push_advertiser_set_random_address(uint8_t advertising_set,uint8_t addr_type,bd_addr address);
void push_advertiser_clear_random_address(uint8_t advertising_set);
void push_advertiser_stop(uint8_t advertising_set);
void push_advertiser_delete_set(uint8_t advertising_set);
void push_advertiser_set_phy(uint8_t advertising_set,uint8_t primary_phy,uint8_t secondary_phy);
void push_advertiser_set_configuration(uint8_t advertising_set,uint32_t configurations);
void push_advertiser_clear_configuration(uint8_t advertising_set,uint32_t configurations);
void push_advertiser_set_data(uint8_t advertising_set,uint8_t packet_type,size_t adv_data_len,uint8_t *adv_data);
void push_advertiser_set_long_data(uint8_t advertising_set,uint8_t packet_type);
void push_advertiser_start(uint8_t advertising_set,uint8_t discover,uint8_t connect);
void push_advertiser_start_periodic_advertising(uint8_t advertising_set,uint16_t interval_min,uint16_t interval_max,uint32_t flags);
void push_advertiser_stop_periodic_advertising(uint8_t advertising_set);
void push_scanner_set_parameters(uint8_t mode,uint16_t interval,uint16_t window);
void push_scanner_set_parameters_and_filter(uint8_t mode,uint16_t interval,uint16_t window,uint32_t flags,uint8_t filter_policy);
void push_scanner_stop();
void push_scanner_set_timing(uint8_t phys,uint16_t scan_interval,uint16_t scan_window);
void push_scanner_set_mode(uint8_t phys,uint8_t scan_mode);
void push_scanner_start(uint8_t scanning_phy,uint8_t discover_mode);
void push_connection_set_default_parameters(uint16_t min_interval,uint16_t max_interval,uint16_t latency,uint16_t timeout,uint16_t min_ce_length,uint16_t max_ce_length);
void push_connection_set_default_preferred_phy(uint8_t preferred_phy,uint8_t accepted_phy);
void push_connection_set_default_data_length(uint16_t tx_data_len);
void push_connection_open(bd_addr address,uint8_t address_type,uint8_t initiating_phy);
void push_connection_set_parameters(uint8_t connection,uint16_t min_interval,uint16_t max_interval,uint16_t latency,uint16_t timeout,uint16_t min_ce_length,uint16_t max_ce_length);
void push_connection_set_preferred_phy(uint8_t connection,uint8_t preferred_phy,uint8_t accepted_phy);
void push_connection_disable_slave_latency(uint8_t connection,uint8_t disable);
void push_connection_get_median_rssi(uint8_t connection);
void push_connection_read_channel_map(uint8_t connection);
void push_connection_set_power_reporting(uint8_t connection,uint8_t mode);
void push_connection_set_remote_power_reporting(uint8_t connection,uint8_t mode);
void push_connection_get_tx_power(uint8_t connection,uint8_t phy);
void push_connection_get_remote_tx_power(uint8_t connection,uint8_t phy);
void push_connection_set_tx_power(uint8_t connection,int16_t tx_power);
void push_connection_read_remote_used_features(uint8_t connection);
void push_connection_get_security_status(uint8_t connection);
void push_connection_set_data_length(uint8_t connection,uint16_t tx_data_len,uint16_t tx_time_us);
void push_connection_read_statistics(uint8_t connection,uint8_t reset);
void push_connection_get_scheduling_details(uint8_t connection);
void push_connection_close(uint8_t connection);
void push_connection_forcefully_close(uint8_t connection);
void push_connection_get_rssi(uint8_t connection);
void push_gatt_set_max_mtu(uint16_t max_mtu);
void push_gatt_discover_primary_services(uint8_t connection);
void push_gatt_discover_primary_services_by_uuid(uint8_t connection,size_t uuid_len,uint8_t *uuid);
void push_gatt_find_included_services(uint8_t connection,uint32_t service);
void push_gatt_discover_characteristics(uint8_t connection,uint32_t service);
void push_gatt_discover_characteristics_by_uuid(uint8_t connection,uint32_t service,size_t uuid_len,uint8_t *uuid);
void push_gatt_discover_descriptors(uint8_t connection,uint16_t characteristic);
void push_gatt_discover_characteristic_descriptors(uint8_t connection,uint16_t start,uint16_t end);
void push_gatt_set_characteristic_notification(uint8_t connection,uint16_t characteristic,uint8_t flags);
void push_gatt_send_characteristic_confirmation(uint8_t connection);
void push_gatt_read_characteristic_value(uint8_t connection,uint16_t characteristic);
void push_gatt_read_characteristic_value_from_offset(uint8_t connection,uint16_t characteristic,uint16_t offset,uint16_t maxlen);
void push_gatt_read_multiple_characteristic_values(uint8_t connection,size_t characteristic_list_len,uint8_t *characteristic_list);
void push_gatt_read_characteristic_value_by_uuid(uint8_t connection,uint32_t service,size_t uuid_len,uint8_t *uuid);
void push_gatt_write_characteristic_value(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value);
void push_gatt_write_characteristic_value_without_response(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value);
void push_gatt_prepare_characteristic_value_write(uint8_t connection,uint16_t characteristic,uint16_t offset,size_t value_len,uint8_t *value);
void push_gatt_prepare_characteristic_value_reliable_write(uint8_t connection,uint16_t characteristic,uint16_t offset,size_t value_len,uint8_t *value);
void push_gatt_execute_characteristic_value_write(uint8_t connection,uint8_t flags);
void push_gatt_read_descriptor_value(uint8_t connection,uint16_t descriptor);
void push_gatt_write_descriptor_value(uint8_t connection,uint16_t descriptor,size_t value_len,uint8_t *value);
void push_gatt_server_set_max_mtu(uint16_t max_mtu);
void push_gatt_server_get_mtu(uint8_t connection);
void push_gatt_server_find_attribute(uint16_t start,size_t type_len,uint8_t *type);
void push_gatt_server_read_attribute_value(uint16_t attribute,uint16_t offset);
void push_gatt_server_read_attribute_type(uint16_t attribute);
void push_gatt_server_write_attribute_value(uint16_t attribute,uint16_t offset,size_t value_len,uint8_t *value);
void push_gatt_server_send_user_read_response(uint8_t connection,uint16_t characteristic,uint8_t att_errorcode,size_t value_len,uint8_t *value);
void push_gatt_server_send_user_write_response(uint8_t connection,uint16_t characteristic,uint8_t att_errorcode);
void push_gatt_server_send_notification(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value);
void push_gatt_server_send_indication(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value);
void push_gatt_server_notify_all(uint16_t characteristic,size_t value_len,uint8_t *value);
void push_gatt_server_read_client_configuration(uint8_t connection,uint16_t characteristic);
void push_gatt_server_send_user_prepare_write_response(uint8_t connection,uint16_t characteristic,uint8_t att_errorcode,uint16_t offset,size_t value_len,uint8_t *value);
void push_gatt_server_set_capabilities(uint32_t caps,uint32_t reserved);
void push_gatt_server_enable_capabilities(uint32_t caps);
void push_gatt_server_disable_capabilities(uint32_t caps);
void push_gatt_server_get_enabled_capabilities();
void push_gatt_server_read_client_supported_features(uint8_t connection);
void push_nvm_save(uint16_t key,size_t value_len,uint8_t *value);
void push_nvm_load(uint16_t key);
void push_nvm_erase(uint16_t key);
void push_nvm_erase_all();
void push_test_dtm_tx_v4(uint8_t packet_type,uint8_t length,uint8_t channel,uint8_t phy,int8_t power_level);
void push_test_dtm_tx_cw(uint8_t packet_type,uint8_t channel,uint8_t phy,int16_t power_level);
void push_test_dtm_rx(uint8_t channel,uint8_t phy);
void push_test_dtm_end();
void push_sm_configure(uint8_t flags,uint8_t io_capabilities);
void push_sm_set_minimum_key_size(uint8_t minimum_key_size);
void push_sm_set_debug_mode();
void push_sm_add_to_whitelist(bd_addr address,uint8_t address_type);
void push_sm_store_bonding_configuration(uint8_t max_bonding_count,uint8_t policy_flags);
void push_sm_set_bondable_mode(uint8_t bondable);
void push_sm_set_passkey(int32_t passkey);
void push_sm_increase_security(uint8_t connection);
void push_sm_enter_passkey(uint8_t connection,int32_t passkey);
void push_sm_passkey_confirm(uint8_t connection,uint8_t confirm);
void push_sm_bonding_confirm(uint8_t connection,uint8_t confirm);
void push_sm_delete_bonding(uint8_t bonding);
void push_sm_delete_bondings();
void push_sm_get_bonding_handles(uint32_t reserved);
void push_sm_get_bonding_details(uint32_t bonding);
void push_sm_find_bonding_by_address(bd_addr address);
void push_sm_resolve_rpa(bd_addr rpa);
void push_sm_set_bonding_key(uint32_t bonding,uint8_t key_type,aes_key_128 key);
void push_sm_set_legacy_oob(uint8_t enable,aes_key_128 oob_data);
void push_sm_set_oob(uint8_t enable);
void push_sm_set_remote_oob(uint8_t enable,aes_key_128 random,aes_key_128 confirm);
void push_sm_set_bonding_data(uint8_t connection,uint8_t type,size_t data_len,uint8_t *data);
void push_ota_set_device_name(size_t name_len,uint8_t *name);
void push_ota_set_advertising_data(uint8_t packet_type,size_t adv_data_len,uint8_t *adv_data);
void push_ota_set_configuration(uint32_t flags);
void push_ota_set_rf_path(uint8_t enable,uint8_t antenna);
void push_coex_set_options(uint32_t mask,uint32_t options);
void push_coex_set_parameters(uint8_t priority,uint8_t request,uint8_t pwm_period,uint8_t pwm_dutycycle);
void push_coex_set_directional_priority_pulse(uint8_t pulse);
void push_coex_get_parameters();
void push_coex_get_counters(uint8_t reset);
void push_sync_set_parameters(uint16_t skip,uint16_t timeout,uint32_t flags);
void push_sync_open(bd_addr address,uint8_t address_type,uint8_t adv_sid);
void push_sync_set_reporting_mode(uint16_t sync,uint8_t reporting_mode);
void push_sync_update_sync_parameters(uint16_t sync,uint16_t skip,uint16_t timeout);
void push_sync_close(uint16_t sync);
void push_l2cap_open_le_channel(uint8_t connection,uint16_t spsm,uint16_t max_sdu,uint16_t max_pdu,uint16_t credit);
void push_l2cap_send_le_channel_open_response(uint8_t connection,uint16_t cid,uint16_t max_sdu,uint16_t max_pdu,uint16_t credit,uint16_t errorcode);
void push_l2cap_channel_send_data(uint8_t connection,uint16_t cid,size_t data_len,uint8_t *data);
void push_l2cap_channel_send_credit(uint8_t connection,uint16_t cid,uint16_t credit);
void push_l2cap_close_channel(uint8_t connection,uint16_t cid);
void push_cte_transmitter_set_dtm_parameters(uint8_t cte_length,uint8_t cte_type,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_transmitter_clear_dtm_parameters();
void push_cte_transmitter_enable_connection_cte(uint8_t connection,uint8_t cte_types,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_transmitter_disable_connection_cte(uint8_t connection);
void push_cte_transmitter_enable_connectionless_cte(uint8_t handle,uint8_t cte_length,uint8_t cte_type,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_transmitter_disable_connectionless_cte(uint8_t handle);
void push_cte_transmitter_enable_silabs_cte(uint8_t handle,uint8_t cte_length,uint8_t cte_type,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_transmitter_disable_silabs_cte(uint8_t handle);
void push_cte_receiver_set_dtm_parameters(uint8_t cte_length,uint8_t cte_type,uint8_t slot_durations,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_receiver_clear_dtm_parameters();
void push_cte_receiver_set_sync_cte_type(uint8_t sync_cte_type);
void push_cte_receiver_set_default_sync_receive_parameters(uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t sync_cte_type,uint8_t reporting_mode);
void push_cte_receiver_set_sync_receive_parameters(uint8_t connection,uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t sync_cte_type,uint8_t reporting_mode);
void push_cte_receiver_configure(uint8_t flags);
void push_cte_receiver_enable_connection_cte(uint8_t connection,uint16_t interval,uint8_t cte_length,uint8_t cte_type,uint8_t slot_durations,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_receiver_disable_connection_cte(uint8_t connection);
void push_cte_receiver_enable_connectionless_cte(uint16_t sync,uint8_t slot_durations,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_receiver_disable_connectionless_cte(uint16_t sync);
void push_cte_receiver_enable_silabs_cte(uint8_t slot_durations,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern);
void push_cte_receiver_disable_silabs_cte();
void push_gattdb_new_session();
void push_gattdb_add_service(uint16_t session,uint8_t type,uint8_t property,size_t uuid_len,uint8_t *uuid);
void push_gattdb_remove_service(uint16_t session,uint16_t service);
void push_gattdb_add_included_service(uint16_t session,uint16_t service,uint16_t included_service);
void push_gattdb_remove_included_service(uint16_t session,uint16_t attribute);
void push_gattdb_add_uuid16_characteristic(uint16_t session,uint16_t service,uint16_t property,uint16_t security,uint8_t flag,sl_bt_uuid_16_t uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value);
void push_gattdb_add_uuid128_characteristic(uint16_t session,uint16_t service,uint16_t property,uint16_t security,uint8_t flag,uuid_128 uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value);
void push_gattdb_remove_characteristic(uint16_t session,uint16_t characteristic);
void push_gattdb_add_uuid16_descriptor(uint16_t session,uint16_t characteristic,uint16_t property,uint16_t security,sl_bt_uuid_16_t uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value);
void push_gattdb_add_uuid128_descriptor(uint16_t session,uint16_t characteristic,uint16_t property,uint16_t security,uuid_128 uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value);
void push_gattdb_remove_descriptor(uint16_t session,uint16_t descriptor);
void push_gattdb_start_service(uint16_t session,uint16_t service);
void push_gattdb_stop_service(uint16_t session,uint16_t service);
void push_gattdb_start_characteristic(uint16_t session,uint16_t characteristic);
void push_gattdb_stop_characteristic(uint16_t session,uint16_t characteristic);
void push_gattdb_commit(uint16_t session);
void push_gattdb_abort(uint16_t session);
void push_connection_analyzer_start(uint32_t access_address,uint32_t crc_init,uint16_t interval,uint16_t supervision_timeout,uint8_t central_clock_accuracy,uint8_t central_phy,uint8_t peripheral_phy,uint8_t channel_selection_algorithm,uint8_t hop,sl_bt_connection_channel_map_t *channel_map,uint8_t channel,uint16_t event_counter,int32_t start_time_us,uint32_t flags);
void push_connection_analyzer_stop(uint8_t analyzer);
void push_sync_scanner_set_sync_parameters(uint16_t skip,uint16_t timeout,uint8_t reporting_mode);
void push_sync_scanner_open(bd_addr address,uint8_t address_type,uint8_t adv_sid);
void push_past_receiver_set_default_sync_receive_parameters(uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t reporting_mode);
void push_past_receiver_set_sync_receive_parameters(uint8_t connection,uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t reporting_mode);
void push_advertiser_past_transfer(uint8_t connection,uint16_t service_data,uint8_t advertising_set);
void push_pawr_sync_set_sync_subevents(uint16_t sync,size_t subevents_len,uint8_t *subevents);
void push_pawr_sync_set_response_data(uint16_t sync,uint16_t request_event,uint8_t request_subevent,uint8_t response_subevent,uint8_t response_slot,size_t response_data_len,uint8_t *response_data);
void push_pawr_advertiser_start(uint8_t advertising_set,uint16_t interval_min,uint16_t interval_max,uint32_t flags,uint8_t num_subevents,uint8_t subevent_interval,uint8_t response_slot_delay,uint8_t response_slot_spacing,uint8_t response_slots);
void push_pawr_advertiser_set_subevent_data(uint8_t advertising_set,uint8_t subevent,uint8_t response_slot_start,uint8_t response_slot_count,size_t adv_data_len,uint8_t *adv_data);
void push_pawr_advertiser_create_connection(uint8_t advertising_set,uint8_t subevent,bd_addr address,uint8_t address_type);
void push_pawr_advertiser_stop(uint8_t advertising_set);
void push_legacy_advertiser_set_data(uint8_t advertising_set,uint8_t type,size_t data_len,uint8_t *data);
void push_legacy_advertiser_generate_data(uint8_t advertising_set,uint8_t discover);
void push_legacy_advertiser_start(uint8_t advertising_set,uint8_t connect);
void push_legacy_advertiser_start_directed(uint8_t advertising_set,uint8_t connect,bd_addr peer_addr,uint8_t peer_addr_type);
void push_extended_advertiser_set_phy(uint8_t advertising_set,uint8_t primary_phy,uint8_t secondary_phy);
void push_extended_advertiser_set_data(uint8_t advertising_set,size_t data_len,uint8_t *data);
void push_extended_advertiser_set_long_data(uint8_t advertising_set);
void push_extended_advertiser_generate_data(uint8_t advertising_set,uint8_t discover);
void push_extended_advertiser_start(uint8_t advertising_set,uint8_t connect,uint32_t flags);
void push_extended_advertiser_start_directed(uint8_t advertising_set,uint8_t connect,uint32_t flags,bd_addr peer_addr,uint8_t peer_addr_type);
void push_periodic_advertiser_set_data(uint8_t advertising_set,size_t data_len,uint8_t *data);
void push_periodic_advertiser_set_long_data(uint8_t advertising_set);
void push_periodic_advertiser_start(uint8_t advertising_set,uint16_t interval_min,uint16_t interval_max,uint32_t flags);
void push_periodic_advertiser_stop(uint8_t advertising_set);
void push_cs_security_enable(uint8_t connection);
void push_cs_set_default_settings(uint8_t connection,uint8_t initiator_status,uint8_t reflector_status,uint8_t antenna_identifier,int8_t max_tx_power);
void push_cs_create_config(uint8_t connection,uint8_t config_id,uint8_t create_context,uint8_t main_mode_type,uint8_t sub_mode_type,uint8_t min_main_mode_steps,uint8_t max_main_mode_steps,uint8_t main_mode_repetition,uint8_t mode_calibration_steps,uint8_t role,uint8_t rtt_type,uint8_t cs_sync_phy,sl_bt_cs_channel_map_t *channel_map,uint8_t channel_map_repetition,uint8_t channel_selection_type,uint8_t ch3c_shape,uint8_t ch3c_jump,uint8_t companion_signal_state);
void push_cs_remove_config(uint8_t connection,uint8_t config_id);
void push_cs_set_channel_classification(sl_bt_cs_channel_map_t *channel_map);
void push_cs_set_procedure_parameters(uint8_t connection,uint8_t config_id,uint16_t max_procedure_len,uint16_t min_procedure_interval,uint16_t max_procedure_interval,uint16_t max_procedure_count,uint32_t min_subevent_len,uint32_t max_subevent_len,uint8_t tone_antenna_config_selection,uint8_t phy,int8_t tx_pwr_delta,uint8_t preferred_peer_antenna);
void push_cs_procedure_enable(uint8_t connection,uint8_t enable,uint8_t config_id);
void push_cs_set_antenna_configuration(size_t antenna_element_offset_len,uint8_t *antenna_element_offset);
void push_cs_read_local_supported_capabilities();
void push_cs_test_start(uint8_t main_mode_type,uint8_t sub_mode_type,uint8_t main_mode_repetition,uint8_t mode_calibration_steps,uint8_t role,uint8_t rtt_type,uint8_t cs_sync_phy,uint8_t antenna_selection,sl_bt_cs_subevent_length_t *subevent_len,uint16_t subevent_interval,int8_t tx_power,uint8_t t_ip1_time,uint8_t t_ip2_time,uint8_t t_fcs_time,uint8_t t_pm_time,uint8_t t_sw_time,uint8_t tone_antenna_config,uint8_t companion_signal_state,uint16_t drbg_nonce,uint16_t override_config,size_t override_parameters_len,uint8_t *override_parameters);
void push_sync_past_transfer(uint8_t connection,uint16_t service_data,uint16_t sync);
void push_external_bondingdb_set_data(uint8_t connection,uint8_t type,size_t data_len,uint8_t *data);
void push_resolving_list_add_device_by_bonding(uint32_t bonding,uint8_t privacy_mode);
void push_resolving_list_add_device_by_address(bd_addr address,uint8_t address_type,aes_key_128 key,uint8_t privacy_mode);
void push_resolving_list_remove_device_by_bonding(uint32_t bonding);
void push_resolving_list_remove_device_by_address(bd_addr address,uint8_t address_type);
void push_resolving_list_remove_all_devices();
void push_accept_list_add_device_by_bonding(uint32_t bonding);
void push_accept_list_add_device_by_address(bd_addr address,uint8_t address_type);
void push_accept_list_remove_device_by_bonding(uint32_t bonding);
void push_accept_list_remove_device_by_address(bd_addr address,uint8_t address_type);
void push_accept_list_remove_all_devices();
void push_resource_get_status();
void push_resource_set_report_threshold(uint32_t low,uint32_t high);
void push_resource_enable_connection_tx_report(uint16_t packet_count);
void push_resource_get_connection_tx_status(uint8_t connection);
void push_resource_disable_connection_tx_report();
void push_user_message_to_target(size_t data_len,uint8_t *data);
void push_user_manage_event_filter(size_t data_len,uint8_t *data);
void push_user_reset_to_dfu();

#endif
