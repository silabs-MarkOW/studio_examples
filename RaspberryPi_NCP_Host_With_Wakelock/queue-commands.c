#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sl_bt_api.h>
#include "queue-commands.h"

struct cmds_s {
  struct command_s *head, *tail;
} cmds = { .head= NULL, .tail = NULL };

struct command_s *push_command(enum CMD_TYPE type) {
  struct command_s *ptr;
  assert((ptr = malloc(sizeof(struct command_s))));
  if(cmds.tail) {
    cmds.tail->next = ptr;
    ptr->previous = cmds.tail;
    cmds.tail = ptr;
  } else {
    cmds.tail = ptr;
    cmds.head = ptr;
    ptr->previous = NULL;
    ptr->next = NULL;
  }
  ptr->type = type;
  return ptr;
}

void command_pop(void) {
  struct command_s *ptr = cmds.head;
  if(ptr == cmds.tail) {
    cmds.head = cmds.tail = NULL;
  } else {
    cmds.head = ptr->next;
    cmds.head->previous = NULL;
  }
  free(ptr);
}
void push_dfu_flash_set_address(uint32_t address) {
  struct command_s *cmd = push_command(DFU_FLASH_SET_ADDRESS);
  struct dfu_flash_set_address_s *ptr = &cmd->dfu_flash_set_address;
  ptr->address = address;
};
void push_dfu_flash_upload(size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(DFU_FLASH_UPLOAD);
  struct dfu_flash_upload_s *ptr = &cmd->dfu_flash_upload;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_dfu_flash_upload_finish() {
  struct command_s *cmd = push_command(DFU_FLASH_UPLOAD_FINISH);
  (void)cmd;
};
void push_system_hello() {
  struct command_s *cmd = push_command(SYSTEM_HELLO);
  (void)cmd;
};
void push_system_start_bluetooth() {
  struct command_s *cmd = push_command(SYSTEM_START_BLUETOOTH);
  (void)cmd;
};
void push_system_stop_bluetooth() {
  struct command_s *cmd = push_command(SYSTEM_STOP_BLUETOOTH);
  (void)cmd;
};
void push_system_forcefully_stop_bluetooth() {
  struct command_s *cmd = push_command(SYSTEM_FORCEFULLY_STOP_BLUETOOTH);
  (void)cmd;
};
void push_system_get_version() {
  struct command_s *cmd = push_command(SYSTEM_GET_VERSION);
  (void)cmd;
};
void push_system_reset(uint8_t dfu) {
  struct command_s *cmd = push_command(SYSTEM_RESET);
  struct system_reset_s *ptr = &cmd->system_reset;
  ptr->dfu = dfu;
};
void push_system_halt(uint8_t halt) {
  struct command_s *cmd = push_command(SYSTEM_HALT);
  struct system_halt_s *ptr = &cmd->system_halt;
  ptr->halt = halt;
};
void push_system_linklayer_configure(uint8_t key,size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(SYSTEM_LINKLAYER_CONFIGURE);
  struct system_linklayer_configure_s *ptr = &cmd->system_linklayer_configure;
  ptr->key = key;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_system_set_tx_power(int16_t min_power,int16_t max_power) {
  struct command_s *cmd = push_command(SYSTEM_SET_TX_POWER);
  struct system_set_tx_power_s *ptr = &cmd->system_set_tx_power;
  ptr->min_power = min_power;
  ptr->max_power = max_power;
};
void push_system_get_tx_power_setting() {
  struct command_s *cmd = push_command(SYSTEM_GET_TX_POWER_SETTING);
  (void)cmd;
};
void push_system_set_identity_address(bd_addr address,uint8_t type) {
  struct command_s *cmd = push_command(SYSTEM_SET_IDENTITY_ADDRESS);
  struct system_set_identity_address_s *ptr = &cmd->system_set_identity_address;
  ptr->address = address;
  ptr->type = type;
};
void push_system_get_identity_address() {
  struct command_s *cmd = push_command(SYSTEM_GET_IDENTITY_ADDRESS);
  (void)cmd;
};
void push_system_get_random_data(uint8_t length) {
  struct command_s *cmd = push_command(SYSTEM_GET_RANDOM_DATA);
  struct system_get_random_data_s *ptr = &cmd->system_get_random_data;
  ptr->length = length;
};
void push_system_data_buffer_write(size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(SYSTEM_DATA_BUFFER_WRITE);
  struct system_data_buffer_write_s *ptr = &cmd->system_data_buffer_write;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_system_data_buffer_clear() {
  struct command_s *cmd = push_command(SYSTEM_DATA_BUFFER_CLEAR);
  (void)cmd;
};
void push_system_get_counters(uint8_t reset) {
  struct command_s *cmd = push_command(SYSTEM_GET_COUNTERS);
  struct system_get_counters_s *ptr = &cmd->system_get_counters;
  ptr->reset = reset;
};
void push_system_set_lazy_soft_timer(uint32_t time,uint32_t slack,uint8_t handle,uint8_t single_shot) {
  struct command_s *cmd = push_command(SYSTEM_SET_LAZY_SOFT_TIMER);
  struct system_set_lazy_soft_timer_s *ptr = &cmd->system_set_lazy_soft_timer;
  ptr->time = time;
  ptr->slack = slack;
  ptr->handle = handle;
  ptr->single_shot = single_shot;
};
void push_gap_set_privacy_mode(uint8_t privacy,uint8_t interval) {
  struct command_s *cmd = push_command(GAP_SET_PRIVACY_MODE);
  struct gap_set_privacy_mode_s *ptr = &cmd->gap_set_privacy_mode;
  ptr->privacy = privacy;
  ptr->interval = interval;
};
void push_gap_set_data_channel_classification(size_t channel_map_len,uint8_t *channel_map) {
  struct command_s *cmd = push_command(GAP_SET_DATA_CHANNEL_CLASSIFICATION);
  struct gap_set_data_channel_classification_s *ptr = &cmd->gap_set_data_channel_classification;
  ptr->channel_map_len = channel_map_len;
  ptr->channel_map = channel_map;
};
void push_gap_enable_whitelisting(uint8_t enable) {
  struct command_s *cmd = push_command(GAP_ENABLE_WHITELISTING);
  struct gap_enable_whitelisting_s *ptr = &cmd->gap_enable_whitelisting;
  ptr->enable = enable;
};
void push_gap_set_identity_address(bd_addr address,uint8_t addr_type) {
  struct command_s *cmd = push_command(GAP_SET_IDENTITY_ADDRESS);
  struct gap_set_identity_address_s *ptr = &cmd->gap_set_identity_address;
  ptr->address = address;
  ptr->addr_type = addr_type;
};
void push_advertiser_create_set() {
  struct command_s *cmd = push_command(ADVERTISER_CREATE_SET);
  (void)cmd;
};
void push_advertiser_configure(uint8_t advertising_set,uint32_t flags) {
  struct command_s *cmd = push_command(ADVERTISER_CONFIGURE);
  struct advertiser_configure_s *ptr = &cmd->advertiser_configure;
  ptr->advertising_set = advertising_set;
  ptr->flags = flags;
};
void push_advertiser_set_timing(uint8_t advertising_set,uint32_t interval_min,uint32_t interval_max,uint16_t duration,uint8_t maxevents) {
  struct command_s *cmd = push_command(ADVERTISER_SET_TIMING);
  struct advertiser_set_timing_s *ptr = &cmd->advertiser_set_timing;
  ptr->advertising_set = advertising_set;
  ptr->interval_min = interval_min;
  ptr->interval_max = interval_max;
  ptr->duration = duration;
  ptr->maxevents = maxevents;
};
void push_advertiser_set_channel_map(uint8_t advertising_set,uint8_t channel_map) {
  struct command_s *cmd = push_command(ADVERTISER_SET_CHANNEL_MAP);
  struct advertiser_set_channel_map_s *ptr = &cmd->advertiser_set_channel_map;
  ptr->advertising_set = advertising_set;
  ptr->channel_map = channel_map;
};
void push_advertiser_set_tx_power(uint8_t advertising_set,int16_t power) {
  struct command_s *cmd = push_command(ADVERTISER_SET_TX_POWER);
  struct advertiser_set_tx_power_s *ptr = &cmd->advertiser_set_tx_power;
  ptr->advertising_set = advertising_set;
  ptr->power = power;
};
void push_advertiser_set_report_scan_request(uint8_t advertising_set,uint8_t report_scan_req) {
  struct command_s *cmd = push_command(ADVERTISER_SET_REPORT_SCAN_REQUEST);
  struct advertiser_set_report_scan_request_s *ptr = &cmd->advertiser_set_report_scan_request;
  ptr->advertising_set = advertising_set;
  ptr->report_scan_req = report_scan_req;
};
void push_advertiser_set_random_address(uint8_t advertising_set,uint8_t addr_type,bd_addr address) {
  struct command_s *cmd = push_command(ADVERTISER_SET_RANDOM_ADDRESS);
  struct advertiser_set_random_address_s *ptr = &cmd->advertiser_set_random_address;
  ptr->advertising_set = advertising_set;
  ptr->addr_type = addr_type;
  ptr->address = address;
};
void push_advertiser_clear_random_address(uint8_t advertising_set) {
  struct command_s *cmd = push_command(ADVERTISER_CLEAR_RANDOM_ADDRESS);
  struct advertiser_clear_random_address_s *ptr = &cmd->advertiser_clear_random_address;
  ptr->advertising_set = advertising_set;
};
void push_advertiser_stop(uint8_t advertising_set) {
  struct command_s *cmd = push_command(ADVERTISER_STOP);
  struct advertiser_stop_s *ptr = &cmd->advertiser_stop;
  ptr->advertising_set = advertising_set;
};
void push_advertiser_delete_set(uint8_t advertising_set) {
  struct command_s *cmd = push_command(ADVERTISER_DELETE_SET);
  struct advertiser_delete_set_s *ptr = &cmd->advertiser_delete_set;
  ptr->advertising_set = advertising_set;
};
void push_advertiser_set_phy(uint8_t advertising_set,uint8_t primary_phy,uint8_t secondary_phy) {
  struct command_s *cmd = push_command(ADVERTISER_SET_PHY);
  struct advertiser_set_phy_s *ptr = &cmd->advertiser_set_phy;
  ptr->advertising_set = advertising_set;
  ptr->primary_phy = primary_phy;
  ptr->secondary_phy = secondary_phy;
};
void push_advertiser_set_configuration(uint8_t advertising_set,uint32_t configurations) {
  struct command_s *cmd = push_command(ADVERTISER_SET_CONFIGURATION);
  struct advertiser_set_configuration_s *ptr = &cmd->advertiser_set_configuration;
  ptr->advertising_set = advertising_set;
  ptr->configurations = configurations;
};
void push_advertiser_clear_configuration(uint8_t advertising_set,uint32_t configurations) {
  struct command_s *cmd = push_command(ADVERTISER_CLEAR_CONFIGURATION);
  struct advertiser_clear_configuration_s *ptr = &cmd->advertiser_clear_configuration;
  ptr->advertising_set = advertising_set;
  ptr->configurations = configurations;
};
void push_advertiser_set_data(uint8_t advertising_set,uint8_t packet_type,size_t adv_data_len,uint8_t *adv_data) {
  struct command_s *cmd = push_command(ADVERTISER_SET_DATA);
  struct advertiser_set_data_s *ptr = &cmd->advertiser_set_data;
  ptr->advertising_set = advertising_set;
  ptr->packet_type = packet_type;
  ptr->adv_data_len = adv_data_len;
  ptr->adv_data = adv_data;
};
void push_advertiser_set_long_data(uint8_t advertising_set,uint8_t packet_type) {
  struct command_s *cmd = push_command(ADVERTISER_SET_LONG_DATA);
  struct advertiser_set_long_data_s *ptr = &cmd->advertiser_set_long_data;
  ptr->advertising_set = advertising_set;
  ptr->packet_type = packet_type;
};
void push_advertiser_start(uint8_t advertising_set,uint8_t discover,uint8_t connect) {
  struct command_s *cmd = push_command(ADVERTISER_START);
  struct advertiser_start_s *ptr = &cmd->advertiser_start;
  ptr->advertising_set = advertising_set;
  ptr->discover = discover;
  ptr->connect = connect;
};
void push_advertiser_start_periodic_advertising(uint8_t advertising_set,uint16_t interval_min,uint16_t interval_max,uint32_t flags) {
  struct command_s *cmd = push_command(ADVERTISER_START_PERIODIC_ADVERTISING);
  struct advertiser_start_periodic_advertising_s *ptr = &cmd->advertiser_start_periodic_advertising;
  ptr->advertising_set = advertising_set;
  ptr->interval_min = interval_min;
  ptr->interval_max = interval_max;
  ptr->flags = flags;
};
void push_advertiser_stop_periodic_advertising(uint8_t advertising_set) {
  struct command_s *cmd = push_command(ADVERTISER_STOP_PERIODIC_ADVERTISING);
  struct advertiser_stop_periodic_advertising_s *ptr = &cmd->advertiser_stop_periodic_advertising;
  ptr->advertising_set = advertising_set;
};
void push_scanner_set_parameters(uint8_t mode,uint16_t interval,uint16_t window) {
  struct command_s *cmd = push_command(SCANNER_SET_PARAMETERS);
  struct scanner_set_parameters_s *ptr = &cmd->scanner_set_parameters;
  ptr->mode = mode;
  ptr->interval = interval;
  ptr->window = window;
};
void push_scanner_set_parameters_and_filter(uint8_t mode,uint16_t interval,uint16_t window,uint32_t flags,uint8_t filter_policy) {
  struct command_s *cmd = push_command(SCANNER_SET_PARAMETERS_AND_FILTER);
  struct scanner_set_parameters_and_filter_s *ptr = &cmd->scanner_set_parameters_and_filter;
  ptr->mode = mode;
  ptr->interval = interval;
  ptr->window = window;
  ptr->flags = flags;
  ptr->filter_policy = filter_policy;
};
void push_scanner_stop() {
  struct command_s *cmd = push_command(SCANNER_STOP);
  (void)cmd;
};
void push_scanner_set_timing(uint8_t phys,uint16_t scan_interval,uint16_t scan_window) {
  struct command_s *cmd = push_command(SCANNER_SET_TIMING);
  struct scanner_set_timing_s *ptr = &cmd->scanner_set_timing;
  ptr->phys = phys;
  ptr->scan_interval = scan_interval;
  ptr->scan_window = scan_window;
};
void push_scanner_set_mode(uint8_t phys,uint8_t scan_mode) {
  struct command_s *cmd = push_command(SCANNER_SET_MODE);
  struct scanner_set_mode_s *ptr = &cmd->scanner_set_mode;
  ptr->phys = phys;
  ptr->scan_mode = scan_mode;
};
void push_scanner_start(uint8_t scanning_phy,uint8_t discover_mode) {
  struct command_s *cmd = push_command(SCANNER_START);
  struct scanner_start_s *ptr = &cmd->scanner_start;
  ptr->scanning_phy = scanning_phy;
  ptr->discover_mode = discover_mode;
};
void push_connection_set_default_parameters(uint16_t min_interval,uint16_t max_interval,uint16_t latency,uint16_t timeout,uint16_t min_ce_length,uint16_t max_ce_length) {
  struct command_s *cmd = push_command(CONNECTION_SET_DEFAULT_PARAMETERS);
  struct connection_set_default_parameters_s *ptr = &cmd->connection_set_default_parameters;
  ptr->min_interval = min_interval;
  ptr->max_interval = max_interval;
  ptr->latency = latency;
  ptr->timeout = timeout;
  ptr->min_ce_length = min_ce_length;
  ptr->max_ce_length = max_ce_length;
};
void push_connection_set_default_preferred_phy(uint8_t preferred_phy,uint8_t accepted_phy) {
  struct command_s *cmd = push_command(CONNECTION_SET_DEFAULT_PREFERRED_PHY);
  struct connection_set_default_preferred_phy_s *ptr = &cmd->connection_set_default_preferred_phy;
  ptr->preferred_phy = preferred_phy;
  ptr->accepted_phy = accepted_phy;
};
void push_connection_set_default_data_length(uint16_t tx_data_len) {
  struct command_s *cmd = push_command(CONNECTION_SET_DEFAULT_DATA_LENGTH);
  struct connection_set_default_data_length_s *ptr = &cmd->connection_set_default_data_length;
  ptr->tx_data_len = tx_data_len;
};
void push_connection_open(bd_addr address,uint8_t address_type,uint8_t initiating_phy) {
  struct command_s *cmd = push_command(CONNECTION_OPEN);
  struct connection_open_s *ptr = &cmd->connection_open;
  ptr->address = address;
  ptr->address_type = address_type;
  ptr->initiating_phy = initiating_phy;
};
void push_connection_set_parameters(uint8_t connection,uint16_t min_interval,uint16_t max_interval,uint16_t latency,uint16_t timeout,uint16_t min_ce_length,uint16_t max_ce_length) {
  struct command_s *cmd = push_command(CONNECTION_SET_PARAMETERS);
  struct connection_set_parameters_s *ptr = &cmd->connection_set_parameters;
  ptr->connection = connection;
  ptr->min_interval = min_interval;
  ptr->max_interval = max_interval;
  ptr->latency = latency;
  ptr->timeout = timeout;
  ptr->min_ce_length = min_ce_length;
  ptr->max_ce_length = max_ce_length;
};
void push_connection_set_preferred_phy(uint8_t connection,uint8_t preferred_phy,uint8_t accepted_phy) {
  struct command_s *cmd = push_command(CONNECTION_SET_PREFERRED_PHY);
  struct connection_set_preferred_phy_s *ptr = &cmd->connection_set_preferred_phy;
  ptr->connection = connection;
  ptr->preferred_phy = preferred_phy;
  ptr->accepted_phy = accepted_phy;
};
void push_connection_disable_slave_latency(uint8_t connection,uint8_t disable) {
  struct command_s *cmd = push_command(CONNECTION_DISABLE_SLAVE_LATENCY);
  struct connection_disable_slave_latency_s *ptr = &cmd->connection_disable_slave_latency;
  ptr->connection = connection;
  ptr->disable = disable;
};
void push_connection_get_median_rssi(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_GET_MEDIAN_RSSI);
  struct connection_get_median_rssi_s *ptr = &cmd->connection_get_median_rssi;
  ptr->connection = connection;
};
void push_connection_read_channel_map(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_READ_CHANNEL_MAP);
  struct connection_read_channel_map_s *ptr = &cmd->connection_read_channel_map;
  ptr->connection = connection;
};
void push_connection_set_power_reporting(uint8_t connection,uint8_t mode) {
  struct command_s *cmd = push_command(CONNECTION_SET_POWER_REPORTING);
  struct connection_set_power_reporting_s *ptr = &cmd->connection_set_power_reporting;
  ptr->connection = connection;
  ptr->mode = mode;
};
void push_connection_set_remote_power_reporting(uint8_t connection,uint8_t mode) {
  struct command_s *cmd = push_command(CONNECTION_SET_REMOTE_POWER_REPORTING);
  struct connection_set_remote_power_reporting_s *ptr = &cmd->connection_set_remote_power_reporting;
  ptr->connection = connection;
  ptr->mode = mode;
};
void push_connection_get_tx_power(uint8_t connection,uint8_t phy) {
  struct command_s *cmd = push_command(CONNECTION_GET_TX_POWER);
  struct connection_get_tx_power_s *ptr = &cmd->connection_get_tx_power;
  ptr->connection = connection;
  ptr->phy = phy;
};
void push_connection_get_remote_tx_power(uint8_t connection,uint8_t phy) {
  struct command_s *cmd = push_command(CONNECTION_GET_REMOTE_TX_POWER);
  struct connection_get_remote_tx_power_s *ptr = &cmd->connection_get_remote_tx_power;
  ptr->connection = connection;
  ptr->phy = phy;
};
void push_connection_set_tx_power(uint8_t connection,int16_t tx_power) {
  struct command_s *cmd = push_command(CONNECTION_SET_TX_POWER);
  struct connection_set_tx_power_s *ptr = &cmd->connection_set_tx_power;
  ptr->connection = connection;
  ptr->tx_power = tx_power;
};
void push_connection_read_remote_used_features(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_READ_REMOTE_USED_FEATURES);
  struct connection_read_remote_used_features_s *ptr = &cmd->connection_read_remote_used_features;
  ptr->connection = connection;
};
void push_connection_get_security_status(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_GET_SECURITY_STATUS);
  struct connection_get_security_status_s *ptr = &cmd->connection_get_security_status;
  ptr->connection = connection;
};
void push_connection_set_data_length(uint8_t connection,uint16_t tx_data_len,uint16_t tx_time_us) {
  struct command_s *cmd = push_command(CONNECTION_SET_DATA_LENGTH);
  struct connection_set_data_length_s *ptr = &cmd->connection_set_data_length;
  ptr->connection = connection;
  ptr->tx_data_len = tx_data_len;
  ptr->tx_time_us = tx_time_us;
};
void push_connection_read_statistics(uint8_t connection,uint8_t reset) {
  struct command_s *cmd = push_command(CONNECTION_READ_STATISTICS);
  struct connection_read_statistics_s *ptr = &cmd->connection_read_statistics;
  ptr->connection = connection;
  ptr->reset = reset;
};
void push_connection_get_scheduling_details(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_GET_SCHEDULING_DETAILS);
  struct connection_get_scheduling_details_s *ptr = &cmd->connection_get_scheduling_details;
  ptr->connection = connection;
};
void push_connection_close(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_CLOSE);
  struct connection_close_s *ptr = &cmd->connection_close;
  ptr->connection = connection;
};
void push_connection_forcefully_close(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_FORCEFULLY_CLOSE);
  struct connection_forcefully_close_s *ptr = &cmd->connection_forcefully_close;
  ptr->connection = connection;
};
void push_connection_get_rssi(uint8_t connection) {
  struct command_s *cmd = push_command(CONNECTION_GET_RSSI);
  struct connection_get_rssi_s *ptr = &cmd->connection_get_rssi;
  ptr->connection = connection;
};
void push_gatt_set_max_mtu(uint16_t max_mtu) {
  struct command_s *cmd = push_command(GATT_SET_MAX_MTU);
  struct gatt_set_max_mtu_s *ptr = &cmd->gatt_set_max_mtu;
  ptr->max_mtu = max_mtu;
};
void push_gatt_discover_primary_services(uint8_t connection) {
  struct command_s *cmd = push_command(GATT_DISCOVER_PRIMARY_SERVICES);
  struct gatt_discover_primary_services_s *ptr = &cmd->gatt_discover_primary_services;
  ptr->connection = connection;
};
void push_gatt_discover_primary_services_by_uuid(uint8_t connection,size_t uuid_len,uint8_t *uuid) {
  struct command_s *cmd = push_command(GATT_DISCOVER_PRIMARY_SERVICES_BY_UUID);
  struct gatt_discover_primary_services_by_uuid_s *ptr = &cmd->gatt_discover_primary_services_by_uuid;
  ptr->connection = connection;
  ptr->uuid_len = uuid_len;
  ptr->uuid = uuid;
};
void push_gatt_find_included_services(uint8_t connection,uint32_t service) {
  struct command_s *cmd = push_command(GATT_FIND_INCLUDED_SERVICES);
  struct gatt_find_included_services_s *ptr = &cmd->gatt_find_included_services;
  ptr->connection = connection;
  ptr->service = service;
};
void push_gatt_discover_characteristics(uint8_t connection,uint32_t service) {
  struct command_s *cmd = push_command(GATT_DISCOVER_CHARACTERISTICS);
  struct gatt_discover_characteristics_s *ptr = &cmd->gatt_discover_characteristics;
  ptr->connection = connection;
  ptr->service = service;
};
void push_gatt_discover_characteristics_by_uuid(uint8_t connection,uint32_t service,size_t uuid_len,uint8_t *uuid) {
  struct command_s *cmd = push_command(GATT_DISCOVER_CHARACTERISTICS_BY_UUID);
  struct gatt_discover_characteristics_by_uuid_s *ptr = &cmd->gatt_discover_characteristics_by_uuid;
  ptr->connection = connection;
  ptr->service = service;
  ptr->uuid_len = uuid_len;
  ptr->uuid = uuid;
};
void push_gatt_discover_descriptors(uint8_t connection,uint16_t characteristic) {
  struct command_s *cmd = push_command(GATT_DISCOVER_DESCRIPTORS);
  struct gatt_discover_descriptors_s *ptr = &cmd->gatt_discover_descriptors;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
};
void push_gatt_discover_characteristic_descriptors(uint8_t connection,uint16_t start,uint16_t end) {
  struct command_s *cmd = push_command(GATT_DISCOVER_CHARACTERISTIC_DESCRIPTORS);
  struct gatt_discover_characteristic_descriptors_s *ptr = &cmd->gatt_discover_characteristic_descriptors;
  ptr->connection = connection;
  ptr->start = start;
  ptr->end = end;
};
void push_gatt_set_characteristic_notification(uint8_t connection,uint16_t characteristic,uint8_t flags) {
  struct command_s *cmd = push_command(GATT_SET_CHARACTERISTIC_NOTIFICATION);
  struct gatt_set_characteristic_notification_s *ptr = &cmd->gatt_set_characteristic_notification;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->flags = flags;
};
void push_gatt_send_characteristic_confirmation(uint8_t connection) {
  struct command_s *cmd = push_command(GATT_SEND_CHARACTERISTIC_CONFIRMATION);
  struct gatt_send_characteristic_confirmation_s *ptr = &cmd->gatt_send_characteristic_confirmation;
  ptr->connection = connection;
};
void push_gatt_read_characteristic_value(uint8_t connection,uint16_t characteristic) {
  struct command_s *cmd = push_command(GATT_READ_CHARACTERISTIC_VALUE);
  struct gatt_read_characteristic_value_s *ptr = &cmd->gatt_read_characteristic_value;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
};
void push_gatt_read_characteristic_value_from_offset(uint8_t connection,uint16_t characteristic,uint16_t offset,uint16_t maxlen) {
  struct command_s *cmd = push_command(GATT_READ_CHARACTERISTIC_VALUE_FROM_OFFSET);
  struct gatt_read_characteristic_value_from_offset_s *ptr = &cmd->gatt_read_characteristic_value_from_offset;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->offset = offset;
  ptr->maxlen = maxlen;
};
void push_gatt_read_multiple_characteristic_values(uint8_t connection,size_t characteristic_list_len,uint8_t *characteristic_list) {
  struct command_s *cmd = push_command(GATT_READ_MULTIPLE_CHARACTERISTIC_VALUES);
  struct gatt_read_multiple_characteristic_values_s *ptr = &cmd->gatt_read_multiple_characteristic_values;
  ptr->connection = connection;
  ptr->characteristic_list_len = characteristic_list_len;
  ptr->characteristic_list = characteristic_list;
};
void push_gatt_read_characteristic_value_by_uuid(uint8_t connection,uint32_t service,size_t uuid_len,uint8_t *uuid) {
  struct command_s *cmd = push_command(GATT_READ_CHARACTERISTIC_VALUE_BY_UUID);
  struct gatt_read_characteristic_value_by_uuid_s *ptr = &cmd->gatt_read_characteristic_value_by_uuid;
  ptr->connection = connection;
  ptr->service = service;
  ptr->uuid_len = uuid_len;
  ptr->uuid = uuid;
};
void push_gatt_write_characteristic_value(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_WRITE_CHARACTERISTIC_VALUE);
  struct gatt_write_characteristic_value_s *ptr = &cmd->gatt_write_characteristic_value;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_write_characteristic_value_without_response(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_WRITE_CHARACTERISTIC_VALUE_WITHOUT_RESPONSE);
  struct gatt_write_characteristic_value_without_response_s *ptr = &cmd->gatt_write_characteristic_value_without_response;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_prepare_characteristic_value_write(uint8_t connection,uint16_t characteristic,uint16_t offset,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_PREPARE_CHARACTERISTIC_VALUE_WRITE);
  struct gatt_prepare_characteristic_value_write_s *ptr = &cmd->gatt_prepare_characteristic_value_write;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->offset = offset;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_prepare_characteristic_value_reliable_write(uint8_t connection,uint16_t characteristic,uint16_t offset,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_PREPARE_CHARACTERISTIC_VALUE_RELIABLE_WRITE);
  struct gatt_prepare_characteristic_value_reliable_write_s *ptr = &cmd->gatt_prepare_characteristic_value_reliable_write;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->offset = offset;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_execute_characteristic_value_write(uint8_t connection,uint8_t flags) {
  struct command_s *cmd = push_command(GATT_EXECUTE_CHARACTERISTIC_VALUE_WRITE);
  struct gatt_execute_characteristic_value_write_s *ptr = &cmd->gatt_execute_characteristic_value_write;
  ptr->connection = connection;
  ptr->flags = flags;
};
void push_gatt_read_descriptor_value(uint8_t connection,uint16_t descriptor) {
  struct command_s *cmd = push_command(GATT_READ_DESCRIPTOR_VALUE);
  struct gatt_read_descriptor_value_s *ptr = &cmd->gatt_read_descriptor_value;
  ptr->connection = connection;
  ptr->descriptor = descriptor;
};
void push_gatt_write_descriptor_value(uint8_t connection,uint16_t descriptor,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_WRITE_DESCRIPTOR_VALUE);
  struct gatt_write_descriptor_value_s *ptr = &cmd->gatt_write_descriptor_value;
  ptr->connection = connection;
  ptr->descriptor = descriptor;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_server_set_max_mtu(uint16_t max_mtu) {
  struct command_s *cmd = push_command(GATT_SERVER_SET_MAX_MTU);
  struct gatt_server_set_max_mtu_s *ptr = &cmd->gatt_server_set_max_mtu;
  ptr->max_mtu = max_mtu;
};
void push_gatt_server_get_mtu(uint8_t connection) {
  struct command_s *cmd = push_command(GATT_SERVER_GET_MTU);
  struct gatt_server_get_mtu_s *ptr = &cmd->gatt_server_get_mtu;
  ptr->connection = connection;
};
void push_gatt_server_find_attribute(uint16_t start,size_t type_len,uint8_t *type) {
  struct command_s *cmd = push_command(GATT_SERVER_FIND_ATTRIBUTE);
  struct gatt_server_find_attribute_s *ptr = &cmd->gatt_server_find_attribute;
  ptr->start = start;
  ptr->type_len = type_len;
  ptr->type = type;
};
void push_gatt_server_read_attribute_value(uint16_t attribute,uint16_t offset) {
  struct command_s *cmd = push_command(GATT_SERVER_READ_ATTRIBUTE_VALUE);
  struct gatt_server_read_attribute_value_s *ptr = &cmd->gatt_server_read_attribute_value;
  ptr->attribute = attribute;
  ptr->offset = offset;
};
void push_gatt_server_read_attribute_type(uint16_t attribute) {
  struct command_s *cmd = push_command(GATT_SERVER_READ_ATTRIBUTE_TYPE);
  struct gatt_server_read_attribute_type_s *ptr = &cmd->gatt_server_read_attribute_type;
  ptr->attribute = attribute;
};
void push_gatt_server_write_attribute_value(uint16_t attribute,uint16_t offset,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_SERVER_WRITE_ATTRIBUTE_VALUE);
  struct gatt_server_write_attribute_value_s *ptr = &cmd->gatt_server_write_attribute_value;
  ptr->attribute = attribute;
  ptr->offset = offset;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_server_send_user_read_response(uint8_t connection,uint16_t characteristic,uint8_t att_errorcode,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_SERVER_SEND_USER_READ_RESPONSE);
  struct gatt_server_send_user_read_response_s *ptr = &cmd->gatt_server_send_user_read_response;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->att_errorcode = att_errorcode;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_server_send_user_write_response(uint8_t connection,uint16_t characteristic,uint8_t att_errorcode) {
  struct command_s *cmd = push_command(GATT_SERVER_SEND_USER_WRITE_RESPONSE);
  struct gatt_server_send_user_write_response_s *ptr = &cmd->gatt_server_send_user_write_response;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->att_errorcode = att_errorcode;
};
void push_gatt_server_send_notification(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_SERVER_SEND_NOTIFICATION);
  struct gatt_server_send_notification_s *ptr = &cmd->gatt_server_send_notification;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_server_send_indication(uint8_t connection,uint16_t characteristic,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_SERVER_SEND_INDICATION);
  struct gatt_server_send_indication_s *ptr = &cmd->gatt_server_send_indication;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_server_notify_all(uint16_t characteristic,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_SERVER_NOTIFY_ALL);
  struct gatt_server_notify_all_s *ptr = &cmd->gatt_server_notify_all;
  ptr->characteristic = characteristic;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_server_read_client_configuration(uint8_t connection,uint16_t characteristic) {
  struct command_s *cmd = push_command(GATT_SERVER_READ_CLIENT_CONFIGURATION);
  struct gatt_server_read_client_configuration_s *ptr = &cmd->gatt_server_read_client_configuration;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
};
void push_gatt_server_send_user_prepare_write_response(uint8_t connection,uint16_t characteristic,uint8_t att_errorcode,uint16_t offset,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATT_SERVER_SEND_USER_PREPARE_WRITE_RESPONSE);
  struct gatt_server_send_user_prepare_write_response_s *ptr = &cmd->gatt_server_send_user_prepare_write_response;
  ptr->connection = connection;
  ptr->characteristic = characteristic;
  ptr->att_errorcode = att_errorcode;
  ptr->offset = offset;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gatt_server_set_capabilities(uint32_t caps,uint32_t reserved) {
  struct command_s *cmd = push_command(GATT_SERVER_SET_CAPABILITIES);
  struct gatt_server_set_capabilities_s *ptr = &cmd->gatt_server_set_capabilities;
  ptr->caps = caps;
  ptr->reserved = reserved;
};
void push_gatt_server_enable_capabilities(uint32_t caps) {
  struct command_s *cmd = push_command(GATT_SERVER_ENABLE_CAPABILITIES);
  struct gatt_server_enable_capabilities_s *ptr = &cmd->gatt_server_enable_capabilities;
  ptr->caps = caps;
};
void push_gatt_server_disable_capabilities(uint32_t caps) {
  struct command_s *cmd = push_command(GATT_SERVER_DISABLE_CAPABILITIES);
  struct gatt_server_disable_capabilities_s *ptr = &cmd->gatt_server_disable_capabilities;
  ptr->caps = caps;
};
void push_gatt_server_get_enabled_capabilities() {
  struct command_s *cmd = push_command(GATT_SERVER_GET_ENABLED_CAPABILITIES);
  (void)cmd;
};
void push_gatt_server_read_client_supported_features(uint8_t connection) {
  struct command_s *cmd = push_command(GATT_SERVER_READ_CLIENT_SUPPORTED_FEATURES);
  struct gatt_server_read_client_supported_features_s *ptr = &cmd->gatt_server_read_client_supported_features;
  ptr->connection = connection;
};
void push_nvm_save(uint16_t key,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(NVM_SAVE);
  struct nvm_save_s *ptr = &cmd->nvm_save;
  ptr->key = key;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_nvm_load(uint16_t key) {
  struct command_s *cmd = push_command(NVM_LOAD);
  struct nvm_load_s *ptr = &cmd->nvm_load;
  ptr->key = key;
};
void push_nvm_erase(uint16_t key) {
  struct command_s *cmd = push_command(NVM_ERASE);
  struct nvm_erase_s *ptr = &cmd->nvm_erase;
  ptr->key = key;
};
void push_nvm_erase_all() {
  struct command_s *cmd = push_command(NVM_ERASE_ALL);
  (void)cmd;
};
void push_test_dtm_tx_v4(uint8_t packet_type,uint8_t length,uint8_t channel,uint8_t phy,int8_t power_level) {
  struct command_s *cmd = push_command(TEST_DTM_TX_V4);
  struct test_dtm_tx_v4_s *ptr = &cmd->test_dtm_tx_v4;
  ptr->packet_type = packet_type;
  ptr->length = length;
  ptr->channel = channel;
  ptr->phy = phy;
  ptr->power_level = power_level;
};
void push_test_dtm_tx_cw(uint8_t packet_type,uint8_t channel,uint8_t phy,int16_t power_level) {
  struct command_s *cmd = push_command(TEST_DTM_TX_CW);
  struct test_dtm_tx_cw_s *ptr = &cmd->test_dtm_tx_cw;
  ptr->packet_type = packet_type;
  ptr->channel = channel;
  ptr->phy = phy;
  ptr->power_level = power_level;
};
void push_test_dtm_rx(uint8_t channel,uint8_t phy) {
  struct command_s *cmd = push_command(TEST_DTM_RX);
  struct test_dtm_rx_s *ptr = &cmd->test_dtm_rx;
  ptr->channel = channel;
  ptr->phy = phy;
};
void push_test_dtm_end() {
  struct command_s *cmd = push_command(TEST_DTM_END);
  (void)cmd;
};
void push_sm_configure(uint8_t flags,uint8_t io_capabilities) {
  struct command_s *cmd = push_command(SM_CONFIGURE);
  struct sm_configure_s *ptr = &cmd->sm_configure;
  ptr->flags = flags;
  ptr->io_capabilities = io_capabilities;
};
void push_sm_set_minimum_key_size(uint8_t minimum_key_size) {
  struct command_s *cmd = push_command(SM_SET_MINIMUM_KEY_SIZE);
  struct sm_set_minimum_key_size_s *ptr = &cmd->sm_set_minimum_key_size;
  ptr->minimum_key_size = minimum_key_size;
};
void push_sm_set_debug_mode() {
  struct command_s *cmd = push_command(SM_SET_DEBUG_MODE);
  (void)cmd;
};
void push_sm_add_to_whitelist(bd_addr address,uint8_t address_type) {
  struct command_s *cmd = push_command(SM_ADD_TO_WHITELIST);
  struct sm_add_to_whitelist_s *ptr = &cmd->sm_add_to_whitelist;
  ptr->address = address;
  ptr->address_type = address_type;
};
void push_sm_store_bonding_configuration(uint8_t max_bonding_count,uint8_t policy_flags) {
  struct command_s *cmd = push_command(SM_STORE_BONDING_CONFIGURATION);
  struct sm_store_bonding_configuration_s *ptr = &cmd->sm_store_bonding_configuration;
  ptr->max_bonding_count = max_bonding_count;
  ptr->policy_flags = policy_flags;
};
void push_sm_set_bondable_mode(uint8_t bondable) {
  struct command_s *cmd = push_command(SM_SET_BONDABLE_MODE);
  struct sm_set_bondable_mode_s *ptr = &cmd->sm_set_bondable_mode;
  ptr->bondable = bondable;
};
void push_sm_set_passkey(int32_t passkey) {
  struct command_s *cmd = push_command(SM_SET_PASSKEY);
  struct sm_set_passkey_s *ptr = &cmd->sm_set_passkey;
  ptr->passkey = passkey;
};
void push_sm_increase_security(uint8_t connection) {
  struct command_s *cmd = push_command(SM_INCREASE_SECURITY);
  struct sm_increase_security_s *ptr = &cmd->sm_increase_security;
  ptr->connection = connection;
};
void push_sm_enter_passkey(uint8_t connection,int32_t passkey) {
  struct command_s *cmd = push_command(SM_ENTER_PASSKEY);
  struct sm_enter_passkey_s *ptr = &cmd->sm_enter_passkey;
  ptr->connection = connection;
  ptr->passkey = passkey;
};
void push_sm_passkey_confirm(uint8_t connection,uint8_t confirm) {
  struct command_s *cmd = push_command(SM_PASSKEY_CONFIRM);
  struct sm_passkey_confirm_s *ptr = &cmd->sm_passkey_confirm;
  ptr->connection = connection;
  ptr->confirm = confirm;
};
void push_sm_bonding_confirm(uint8_t connection,uint8_t confirm) {
  struct command_s *cmd = push_command(SM_BONDING_CONFIRM);
  struct sm_bonding_confirm_s *ptr = &cmd->sm_bonding_confirm;
  ptr->connection = connection;
  ptr->confirm = confirm;
};
void push_sm_delete_bonding(uint8_t bonding) {
  struct command_s *cmd = push_command(SM_DELETE_BONDING);
  struct sm_delete_bonding_s *ptr = &cmd->sm_delete_bonding;
  ptr->bonding = bonding;
};
void push_sm_delete_bondings() {
  struct command_s *cmd = push_command(SM_DELETE_BONDINGS);
  (void)cmd;
};
void push_sm_get_bonding_handles(uint32_t reserved) {
  struct command_s *cmd = push_command(SM_GET_BONDING_HANDLES);
  struct sm_get_bonding_handles_s *ptr = &cmd->sm_get_bonding_handles;
  ptr->reserved = reserved;
};
void push_sm_get_bonding_details(uint32_t bonding) {
  struct command_s *cmd = push_command(SM_GET_BONDING_DETAILS);
  struct sm_get_bonding_details_s *ptr = &cmd->sm_get_bonding_details;
  ptr->bonding = bonding;
};
void push_sm_find_bonding_by_address(bd_addr address) {
  struct command_s *cmd = push_command(SM_FIND_BONDING_BY_ADDRESS);
  struct sm_find_bonding_by_address_s *ptr = &cmd->sm_find_bonding_by_address;
  ptr->address = address;
};
void push_sm_resolve_rpa(bd_addr rpa) {
  struct command_s *cmd = push_command(SM_RESOLVE_RPA);
  struct sm_resolve_rpa_s *ptr = &cmd->sm_resolve_rpa;
  ptr->rpa = rpa;
};
void push_sm_set_bonding_key(uint32_t bonding,uint8_t key_type,aes_key_128 key) {
  struct command_s *cmd = push_command(SM_SET_BONDING_KEY);
  struct sm_set_bonding_key_s *ptr = &cmd->sm_set_bonding_key;
  ptr->bonding = bonding;
  ptr->key_type = key_type;
  ptr->key = key;
};
void push_sm_set_legacy_oob(uint8_t enable,aes_key_128 oob_data) {
  struct command_s *cmd = push_command(SM_SET_LEGACY_OOB);
  struct sm_set_legacy_oob_s *ptr = &cmd->sm_set_legacy_oob;
  ptr->enable = enable;
  ptr->oob_data = oob_data;
};
void push_sm_set_oob(uint8_t enable) {
  struct command_s *cmd = push_command(SM_SET_OOB);
  struct sm_set_oob_s *ptr = &cmd->sm_set_oob;
  ptr->enable = enable;
};
void push_sm_set_remote_oob(uint8_t enable,aes_key_128 random,aes_key_128 confirm) {
  struct command_s *cmd = push_command(SM_SET_REMOTE_OOB);
  struct sm_set_remote_oob_s *ptr = &cmd->sm_set_remote_oob;
  ptr->enable = enable;
  ptr->random = random;
  ptr->confirm = confirm;
};
void push_sm_set_bonding_data(uint8_t connection,uint8_t type,size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(SM_SET_BONDING_DATA);
  struct sm_set_bonding_data_s *ptr = &cmd->sm_set_bonding_data;
  ptr->connection = connection;
  ptr->type = type;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_ota_set_device_name(size_t name_len,uint8_t *name) {
  struct command_s *cmd = push_command(OTA_SET_DEVICE_NAME);
  struct ota_set_device_name_s *ptr = &cmd->ota_set_device_name;
  ptr->name_len = name_len;
  ptr->name = name;
};
void push_ota_set_advertising_data(uint8_t packet_type,size_t adv_data_len,uint8_t *adv_data) {
  struct command_s *cmd = push_command(OTA_SET_ADVERTISING_DATA);
  struct ota_set_advertising_data_s *ptr = &cmd->ota_set_advertising_data;
  ptr->packet_type = packet_type;
  ptr->adv_data_len = adv_data_len;
  ptr->adv_data = adv_data;
};
void push_ota_set_configuration(uint32_t flags) {
  struct command_s *cmd = push_command(OTA_SET_CONFIGURATION);
  struct ota_set_configuration_s *ptr = &cmd->ota_set_configuration;
  ptr->flags = flags;
};
void push_ota_set_rf_path(uint8_t enable,uint8_t antenna) {
  struct command_s *cmd = push_command(OTA_SET_RF_PATH);
  struct ota_set_rf_path_s *ptr = &cmd->ota_set_rf_path;
  ptr->enable = enable;
  ptr->antenna = antenna;
};
void push_coex_set_options(uint32_t mask,uint32_t options) {
  struct command_s *cmd = push_command(COEX_SET_OPTIONS);
  struct coex_set_options_s *ptr = &cmd->coex_set_options;
  ptr->mask = mask;
  ptr->options = options;
};
void push_coex_set_parameters(uint8_t priority,uint8_t request,uint8_t pwm_period,uint8_t pwm_dutycycle) {
  struct command_s *cmd = push_command(COEX_SET_PARAMETERS);
  struct coex_set_parameters_s *ptr = &cmd->coex_set_parameters;
  ptr->priority = priority;
  ptr->request = request;
  ptr->pwm_period = pwm_period;
  ptr->pwm_dutycycle = pwm_dutycycle;
};
void push_coex_set_directional_priority_pulse(uint8_t pulse) {
  struct command_s *cmd = push_command(COEX_SET_DIRECTIONAL_PRIORITY_PULSE);
  struct coex_set_directional_priority_pulse_s *ptr = &cmd->coex_set_directional_priority_pulse;
  ptr->pulse = pulse;
};
void push_coex_get_parameters() {
  struct command_s *cmd = push_command(COEX_GET_PARAMETERS);
  (void)cmd;
};
void push_coex_get_counters(uint8_t reset) {
  struct command_s *cmd = push_command(COEX_GET_COUNTERS);
  struct coex_get_counters_s *ptr = &cmd->coex_get_counters;
  ptr->reset = reset;
};
void push_sync_set_parameters(uint16_t skip,uint16_t timeout,uint32_t flags) {
  struct command_s *cmd = push_command(SYNC_SET_PARAMETERS);
  struct sync_set_parameters_s *ptr = &cmd->sync_set_parameters;
  ptr->skip = skip;
  ptr->timeout = timeout;
  ptr->flags = flags;
};
void push_sync_open(bd_addr address,uint8_t address_type,uint8_t adv_sid) {
  struct command_s *cmd = push_command(SYNC_OPEN);
  struct sync_open_s *ptr = &cmd->sync_open;
  ptr->address = address;
  ptr->address_type = address_type;
  ptr->adv_sid = adv_sid;
};
void push_sync_set_reporting_mode(uint16_t sync,uint8_t reporting_mode) {
  struct command_s *cmd = push_command(SYNC_SET_REPORTING_MODE);
  struct sync_set_reporting_mode_s *ptr = &cmd->sync_set_reporting_mode;
  ptr->sync = sync;
  ptr->reporting_mode = reporting_mode;
};
void push_sync_update_sync_parameters(uint16_t sync,uint16_t skip,uint16_t timeout) {
  struct command_s *cmd = push_command(SYNC_UPDATE_SYNC_PARAMETERS);
  struct sync_update_sync_parameters_s *ptr = &cmd->sync_update_sync_parameters;
  ptr->sync = sync;
  ptr->skip = skip;
  ptr->timeout = timeout;
};
void push_sync_close(uint16_t sync) {
  struct command_s *cmd = push_command(SYNC_CLOSE);
  struct sync_close_s *ptr = &cmd->sync_close;
  ptr->sync = sync;
};
void push_l2cap_open_le_channel(uint8_t connection,uint16_t spsm,uint16_t max_sdu,uint16_t max_pdu,uint16_t credit) {
  struct command_s *cmd = push_command(L2CAP_OPEN_LE_CHANNEL);
  struct l2cap_open_le_channel_s *ptr = &cmd->l2cap_open_le_channel;
  ptr->connection = connection;
  ptr->spsm = spsm;
  ptr->max_sdu = max_sdu;
  ptr->max_pdu = max_pdu;
  ptr->credit = credit;
};
void push_l2cap_send_le_channel_open_response(uint8_t connection,uint16_t cid,uint16_t max_sdu,uint16_t max_pdu,uint16_t credit,uint16_t errorcode) {
  struct command_s *cmd = push_command(L2CAP_SEND_LE_CHANNEL_OPEN_RESPONSE);
  struct l2cap_send_le_channel_open_response_s *ptr = &cmd->l2cap_send_le_channel_open_response;
  ptr->connection = connection;
  ptr->cid = cid;
  ptr->max_sdu = max_sdu;
  ptr->max_pdu = max_pdu;
  ptr->credit = credit;
  ptr->errorcode = errorcode;
};
void push_l2cap_channel_send_data(uint8_t connection,uint16_t cid,size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(L2CAP_CHANNEL_SEND_DATA);
  struct l2cap_channel_send_data_s *ptr = &cmd->l2cap_channel_send_data;
  ptr->connection = connection;
  ptr->cid = cid;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_l2cap_channel_send_credit(uint8_t connection,uint16_t cid,uint16_t credit) {
  struct command_s *cmd = push_command(L2CAP_CHANNEL_SEND_CREDIT);
  struct l2cap_channel_send_credit_s *ptr = &cmd->l2cap_channel_send_credit;
  ptr->connection = connection;
  ptr->cid = cid;
  ptr->credit = credit;
};
void push_l2cap_close_channel(uint8_t connection,uint16_t cid) {
  struct command_s *cmd = push_command(L2CAP_CLOSE_CHANNEL);
  struct l2cap_close_channel_s *ptr = &cmd->l2cap_close_channel;
  ptr->connection = connection;
  ptr->cid = cid;
};
void push_cte_transmitter_set_dtm_parameters(uint8_t cte_length,uint8_t cte_type,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_SET_DTM_PARAMETERS);
  struct cte_transmitter_set_dtm_parameters_s *ptr = &cmd->cte_transmitter_set_dtm_parameters;
  ptr->cte_length = cte_length;
  ptr->cte_type = cte_type;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_transmitter_clear_dtm_parameters() {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_CLEAR_DTM_PARAMETERS);
  (void)cmd;
};
void push_cte_transmitter_enable_connection_cte(uint8_t connection,uint8_t cte_types,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_ENABLE_CONNECTION_CTE);
  struct cte_transmitter_enable_connection_cte_s *ptr = &cmd->cte_transmitter_enable_connection_cte;
  ptr->connection = connection;
  ptr->cte_types = cte_types;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_transmitter_disable_connection_cte(uint8_t connection) {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_DISABLE_CONNECTION_CTE);
  struct cte_transmitter_disable_connection_cte_s *ptr = &cmd->cte_transmitter_disable_connection_cte;
  ptr->connection = connection;
};
void push_cte_transmitter_enable_connectionless_cte(uint8_t handle,uint8_t cte_length,uint8_t cte_type,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_ENABLE_CONNECTIONLESS_CTE);
  struct cte_transmitter_enable_connectionless_cte_s *ptr = &cmd->cte_transmitter_enable_connectionless_cte;
  ptr->handle = handle;
  ptr->cte_length = cte_length;
  ptr->cte_type = cte_type;
  ptr->cte_count = cte_count;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_transmitter_disable_connectionless_cte(uint8_t handle) {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_DISABLE_CONNECTIONLESS_CTE);
  struct cte_transmitter_disable_connectionless_cte_s *ptr = &cmd->cte_transmitter_disable_connectionless_cte;
  ptr->handle = handle;
};
void push_cte_transmitter_enable_silabs_cte(uint8_t handle,uint8_t cte_length,uint8_t cte_type,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_ENABLE_SILABS_CTE);
  struct cte_transmitter_enable_silabs_cte_s *ptr = &cmd->cte_transmitter_enable_silabs_cte;
  ptr->handle = handle;
  ptr->cte_length = cte_length;
  ptr->cte_type = cte_type;
  ptr->cte_count = cte_count;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_transmitter_disable_silabs_cte(uint8_t handle) {
  struct command_s *cmd = push_command(CTE_TRANSMITTER_DISABLE_SILABS_CTE);
  struct cte_transmitter_disable_silabs_cte_s *ptr = &cmd->cte_transmitter_disable_silabs_cte;
  ptr->handle = handle;
};
void push_cte_receiver_set_dtm_parameters(uint8_t cte_length,uint8_t cte_type,uint8_t slot_durations,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_RECEIVER_SET_DTM_PARAMETERS);
  struct cte_receiver_set_dtm_parameters_s *ptr = &cmd->cte_receiver_set_dtm_parameters;
  ptr->cte_length = cte_length;
  ptr->cte_type = cte_type;
  ptr->slot_durations = slot_durations;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_receiver_clear_dtm_parameters() {
  struct command_s *cmd = push_command(CTE_RECEIVER_CLEAR_DTM_PARAMETERS);
  (void)cmd;
};
void push_cte_receiver_set_sync_cte_type(uint8_t sync_cte_type) {
  struct command_s *cmd = push_command(CTE_RECEIVER_SET_SYNC_CTE_TYPE);
  struct cte_receiver_set_sync_cte_type_s *ptr = &cmd->cte_receiver_set_sync_cte_type;
  ptr->sync_cte_type = sync_cte_type;
};
void push_cte_receiver_set_default_sync_receive_parameters(uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t sync_cte_type,uint8_t reporting_mode) {
  struct command_s *cmd = push_command(CTE_RECEIVER_SET_DEFAULT_SYNC_RECEIVE_PARAMETERS);
  struct cte_receiver_set_default_sync_receive_parameters_s *ptr = &cmd->cte_receiver_set_default_sync_receive_parameters;
  ptr->mode = mode;
  ptr->skip = skip;
  ptr->timeout = timeout;
  ptr->sync_cte_type = sync_cte_type;
  ptr->reporting_mode = reporting_mode;
};
void push_cte_receiver_set_sync_receive_parameters(uint8_t connection,uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t sync_cte_type,uint8_t reporting_mode) {
  struct command_s *cmd = push_command(CTE_RECEIVER_SET_SYNC_RECEIVE_PARAMETERS);
  struct cte_receiver_set_sync_receive_parameters_s *ptr = &cmd->cte_receiver_set_sync_receive_parameters;
  ptr->connection = connection;
  ptr->mode = mode;
  ptr->skip = skip;
  ptr->timeout = timeout;
  ptr->sync_cte_type = sync_cte_type;
  ptr->reporting_mode = reporting_mode;
};
void push_cte_receiver_configure(uint8_t flags) {
  struct command_s *cmd = push_command(CTE_RECEIVER_CONFIGURE);
  struct cte_receiver_configure_s *ptr = &cmd->cte_receiver_configure;
  ptr->flags = flags;
};
void push_cte_receiver_enable_connection_cte(uint8_t connection,uint16_t interval,uint8_t cte_length,uint8_t cte_type,uint8_t slot_durations,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_RECEIVER_ENABLE_CONNECTION_CTE);
  struct cte_receiver_enable_connection_cte_s *ptr = &cmd->cte_receiver_enable_connection_cte;
  ptr->connection = connection;
  ptr->interval = interval;
  ptr->cte_length = cte_length;
  ptr->cte_type = cte_type;
  ptr->slot_durations = slot_durations;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_receiver_disable_connection_cte(uint8_t connection) {
  struct command_s *cmd = push_command(CTE_RECEIVER_DISABLE_CONNECTION_CTE);
  struct cte_receiver_disable_connection_cte_s *ptr = &cmd->cte_receiver_disable_connection_cte;
  ptr->connection = connection;
};
void push_cte_receiver_enable_connectionless_cte(uint16_t sync,uint8_t slot_durations,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_RECEIVER_ENABLE_CONNECTIONLESS_CTE);
  struct cte_receiver_enable_connectionless_cte_s *ptr = &cmd->cte_receiver_enable_connectionless_cte;
  ptr->sync = sync;
  ptr->slot_durations = slot_durations;
  ptr->cte_count = cte_count;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_receiver_disable_connectionless_cte(uint16_t sync) {
  struct command_s *cmd = push_command(CTE_RECEIVER_DISABLE_CONNECTIONLESS_CTE);
  struct cte_receiver_disable_connectionless_cte_s *ptr = &cmd->cte_receiver_disable_connectionless_cte;
  ptr->sync = sync;
};
void push_cte_receiver_enable_silabs_cte(uint8_t slot_durations,uint8_t cte_count,size_t switching_pattern_len,uint8_t *switching_pattern) {
  struct command_s *cmd = push_command(CTE_RECEIVER_ENABLE_SILABS_CTE);
  struct cte_receiver_enable_silabs_cte_s *ptr = &cmd->cte_receiver_enable_silabs_cte;
  ptr->slot_durations = slot_durations;
  ptr->cte_count = cte_count;
  ptr->switching_pattern_len = switching_pattern_len;
  ptr->switching_pattern = switching_pattern;
};
void push_cte_receiver_disable_silabs_cte() {
  struct command_s *cmd = push_command(CTE_RECEIVER_DISABLE_SILABS_CTE);
  (void)cmd;
};
void push_gattdb_new_session() {
  struct command_s *cmd = push_command(GATTDB_NEW_SESSION);
  (void)cmd;
};
void push_gattdb_add_service(uint16_t session,uint8_t type,uint8_t property,size_t uuid_len,uint8_t *uuid) {
  struct command_s *cmd = push_command(GATTDB_ADD_SERVICE);
  struct gattdb_add_service_s *ptr = &cmd->gattdb_add_service;
  ptr->session = session;
  ptr->type = type;
  ptr->property = property;
  ptr->uuid_len = uuid_len;
  ptr->uuid = uuid;
};
void push_gattdb_remove_service(uint16_t session,uint16_t service) {
  struct command_s *cmd = push_command(GATTDB_REMOVE_SERVICE);
  struct gattdb_remove_service_s *ptr = &cmd->gattdb_remove_service;
  ptr->session = session;
  ptr->service = service;
};
void push_gattdb_add_included_service(uint16_t session,uint16_t service,uint16_t included_service) {
  struct command_s *cmd = push_command(GATTDB_ADD_INCLUDED_SERVICE);
  struct gattdb_add_included_service_s *ptr = &cmd->gattdb_add_included_service;
  ptr->session = session;
  ptr->service = service;
  ptr->included_service = included_service;
};
void push_gattdb_remove_included_service(uint16_t session,uint16_t attribute) {
  struct command_s *cmd = push_command(GATTDB_REMOVE_INCLUDED_SERVICE);
  struct gattdb_remove_included_service_s *ptr = &cmd->gattdb_remove_included_service;
  ptr->session = session;
  ptr->attribute = attribute;
};
void push_gattdb_add_uuid16_characteristic(uint16_t session,uint16_t service,uint16_t property,uint16_t security,uint8_t flag,sl_bt_uuid_16_t uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATTDB_ADD_UUID16_CHARACTERISTIC);
  struct gattdb_add_uuid16_characteristic_s *ptr = &cmd->gattdb_add_uuid16_characteristic;
  ptr->session = session;
  ptr->service = service;
  ptr->property = property;
  ptr->security = security;
  ptr->flag = flag;
  ptr->uuid = uuid;
  ptr->value_type = value_type;
  ptr->maxlen = maxlen;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gattdb_add_uuid128_characteristic(uint16_t session,uint16_t service,uint16_t property,uint16_t security,uint8_t flag,uuid_128 uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATTDB_ADD_UUID128_CHARACTERISTIC);
  struct gattdb_add_uuid128_characteristic_s *ptr = &cmd->gattdb_add_uuid128_characteristic;
  ptr->session = session;
  ptr->service = service;
  ptr->property = property;
  ptr->security = security;
  ptr->flag = flag;
  ptr->uuid = uuid;
  ptr->value_type = value_type;
  ptr->maxlen = maxlen;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gattdb_remove_characteristic(uint16_t session,uint16_t characteristic) {
  struct command_s *cmd = push_command(GATTDB_REMOVE_CHARACTERISTIC);
  struct gattdb_remove_characteristic_s *ptr = &cmd->gattdb_remove_characteristic;
  ptr->session = session;
  ptr->characteristic = characteristic;
};
void push_gattdb_add_uuid16_descriptor(uint16_t session,uint16_t characteristic,uint16_t property,uint16_t security,sl_bt_uuid_16_t uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATTDB_ADD_UUID16_DESCRIPTOR);
  struct gattdb_add_uuid16_descriptor_s *ptr = &cmd->gattdb_add_uuid16_descriptor;
  ptr->session = session;
  ptr->characteristic = characteristic;
  ptr->property = property;
  ptr->security = security;
  ptr->uuid = uuid;
  ptr->value_type = value_type;
  ptr->maxlen = maxlen;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gattdb_add_uuid128_descriptor(uint16_t session,uint16_t characteristic,uint16_t property,uint16_t security,uuid_128 uuid,uint8_t value_type,uint16_t maxlen,size_t value_len,uint8_t *value) {
  struct command_s *cmd = push_command(GATTDB_ADD_UUID128_DESCRIPTOR);
  struct gattdb_add_uuid128_descriptor_s *ptr = &cmd->gattdb_add_uuid128_descriptor;
  ptr->session = session;
  ptr->characteristic = characteristic;
  ptr->property = property;
  ptr->security = security;
  ptr->uuid = uuid;
  ptr->value_type = value_type;
  ptr->maxlen = maxlen;
  ptr->value_len = value_len;
  ptr->value = value;
};
void push_gattdb_remove_descriptor(uint16_t session,uint16_t descriptor) {
  struct command_s *cmd = push_command(GATTDB_REMOVE_DESCRIPTOR);
  struct gattdb_remove_descriptor_s *ptr = &cmd->gattdb_remove_descriptor;
  ptr->session = session;
  ptr->descriptor = descriptor;
};
void push_gattdb_start_service(uint16_t session,uint16_t service) {
  struct command_s *cmd = push_command(GATTDB_START_SERVICE);
  struct gattdb_start_service_s *ptr = &cmd->gattdb_start_service;
  ptr->session = session;
  ptr->service = service;
};
void push_gattdb_stop_service(uint16_t session,uint16_t service) {
  struct command_s *cmd = push_command(GATTDB_STOP_SERVICE);
  struct gattdb_stop_service_s *ptr = &cmd->gattdb_stop_service;
  ptr->session = session;
  ptr->service = service;
};
void push_gattdb_start_characteristic(uint16_t session,uint16_t characteristic) {
  struct command_s *cmd = push_command(GATTDB_START_CHARACTERISTIC);
  struct gattdb_start_characteristic_s *ptr = &cmd->gattdb_start_characteristic;
  ptr->session = session;
  ptr->characteristic = characteristic;
};
void push_gattdb_stop_characteristic(uint16_t session,uint16_t characteristic) {
  struct command_s *cmd = push_command(GATTDB_STOP_CHARACTERISTIC);
  struct gattdb_stop_characteristic_s *ptr = &cmd->gattdb_stop_characteristic;
  ptr->session = session;
  ptr->characteristic = characteristic;
};
void push_gattdb_commit(uint16_t session) {
  struct command_s *cmd = push_command(GATTDB_COMMIT);
  struct gattdb_commit_s *ptr = &cmd->gattdb_commit;
  ptr->session = session;
};
void push_gattdb_abort(uint16_t session) {
  struct command_s *cmd = push_command(GATTDB_ABORT);
  struct gattdb_abort_s *ptr = &cmd->gattdb_abort;
  ptr->session = session;
};
void push_connection_analyzer_start(uint32_t access_address,uint32_t crc_init,uint16_t interval,uint16_t supervision_timeout,uint8_t central_clock_accuracy,uint8_t central_phy,uint8_t peripheral_phy,uint8_t channel_selection_algorithm,uint8_t hop,sl_bt_connection_channel_map_t *channel_map,uint8_t channel,uint16_t event_counter,int32_t start_time_us,uint32_t flags) {
  struct command_s *cmd = push_command(CONNECTION_ANALYZER_START);
  struct connection_analyzer_start_s *ptr = &cmd->connection_analyzer_start;
  ptr->access_address = access_address;
  ptr->crc_init = crc_init;
  ptr->interval = interval;
  ptr->supervision_timeout = supervision_timeout;
  ptr->central_clock_accuracy = central_clock_accuracy;
  ptr->central_phy = central_phy;
  ptr->peripheral_phy = peripheral_phy;
  ptr->channel_selection_algorithm = channel_selection_algorithm;
  ptr->hop = hop;
  ptr->channel_map = channel_map;
  ptr->channel = channel;
  ptr->event_counter = event_counter;
  ptr->start_time_us = start_time_us;
  ptr->flags = flags;
};
void push_connection_analyzer_stop(uint8_t analyzer) {
  struct command_s *cmd = push_command(CONNECTION_ANALYZER_STOP);
  struct connection_analyzer_stop_s *ptr = &cmd->connection_analyzer_stop;
  ptr->analyzer = analyzer;
};
void push_sync_scanner_set_sync_parameters(uint16_t skip,uint16_t timeout,uint8_t reporting_mode) {
  struct command_s *cmd = push_command(SYNC_SCANNER_SET_SYNC_PARAMETERS);
  struct sync_scanner_set_sync_parameters_s *ptr = &cmd->sync_scanner_set_sync_parameters;
  ptr->skip = skip;
  ptr->timeout = timeout;
  ptr->reporting_mode = reporting_mode;
};
void push_sync_scanner_open(bd_addr address,uint8_t address_type,uint8_t adv_sid) {
  struct command_s *cmd = push_command(SYNC_SCANNER_OPEN);
  struct sync_scanner_open_s *ptr = &cmd->sync_scanner_open;
  ptr->address = address;
  ptr->address_type = address_type;
  ptr->adv_sid = adv_sid;
};
void push_past_receiver_set_default_sync_receive_parameters(uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t reporting_mode) {
  struct command_s *cmd = push_command(PAST_RECEIVER_SET_DEFAULT_SYNC_RECEIVE_PARAMETERS);
  struct past_receiver_set_default_sync_receive_parameters_s *ptr = &cmd->past_receiver_set_default_sync_receive_parameters;
  ptr->mode = mode;
  ptr->skip = skip;
  ptr->timeout = timeout;
  ptr->reporting_mode = reporting_mode;
};
void push_past_receiver_set_sync_receive_parameters(uint8_t connection,uint8_t mode,uint16_t skip,uint16_t timeout,uint8_t reporting_mode) {
  struct command_s *cmd = push_command(PAST_RECEIVER_SET_SYNC_RECEIVE_PARAMETERS);
  struct past_receiver_set_sync_receive_parameters_s *ptr = &cmd->past_receiver_set_sync_receive_parameters;
  ptr->connection = connection;
  ptr->mode = mode;
  ptr->skip = skip;
  ptr->timeout = timeout;
  ptr->reporting_mode = reporting_mode;
};
void push_advertiser_past_transfer(uint8_t connection,uint16_t service_data,uint8_t advertising_set) {
  struct command_s *cmd = push_command(ADVERTISER_PAST_TRANSFER);
  struct advertiser_past_transfer_s *ptr = &cmd->advertiser_past_transfer;
  ptr->connection = connection;
  ptr->service_data = service_data;
  ptr->advertising_set = advertising_set;
};
void push_pawr_sync_set_sync_subevents(uint16_t sync,size_t subevents_len,uint8_t *subevents) {
  struct command_s *cmd = push_command(PAWR_SYNC_SET_SYNC_SUBEVENTS);
  struct pawr_sync_set_sync_subevents_s *ptr = &cmd->pawr_sync_set_sync_subevents;
  ptr->sync = sync;
  ptr->subevents_len = subevents_len;
  ptr->subevents = subevents;
};
void push_pawr_sync_set_response_data(uint16_t sync,uint16_t request_event,uint8_t request_subevent,uint8_t response_subevent,uint8_t response_slot,size_t response_data_len,uint8_t *response_data) {
  struct command_s *cmd = push_command(PAWR_SYNC_SET_RESPONSE_DATA);
  struct pawr_sync_set_response_data_s *ptr = &cmd->pawr_sync_set_response_data;
  ptr->sync = sync;
  ptr->request_event = request_event;
  ptr->request_subevent = request_subevent;
  ptr->response_subevent = response_subevent;
  ptr->response_slot = response_slot;
  ptr->response_data_len = response_data_len;
  ptr->response_data = response_data;
};
void push_pawr_advertiser_start(uint8_t advertising_set,uint16_t interval_min,uint16_t interval_max,uint32_t flags,uint8_t num_subevents,uint8_t subevent_interval,uint8_t response_slot_delay,uint8_t response_slot_spacing,uint8_t response_slots) {
  struct command_s *cmd = push_command(PAWR_ADVERTISER_START);
  struct pawr_advertiser_start_s *ptr = &cmd->pawr_advertiser_start;
  ptr->advertising_set = advertising_set;
  ptr->interval_min = interval_min;
  ptr->interval_max = interval_max;
  ptr->flags = flags;
  ptr->num_subevents = num_subevents;
  ptr->subevent_interval = subevent_interval;
  ptr->response_slot_delay = response_slot_delay;
  ptr->response_slot_spacing = response_slot_spacing;
  ptr->response_slots = response_slots;
};
void push_pawr_advertiser_set_subevent_data(uint8_t advertising_set,uint8_t subevent,uint8_t response_slot_start,uint8_t response_slot_count,size_t adv_data_len,uint8_t *adv_data) {
  struct command_s *cmd = push_command(PAWR_ADVERTISER_SET_SUBEVENT_DATA);
  struct pawr_advertiser_set_subevent_data_s *ptr = &cmd->pawr_advertiser_set_subevent_data;
  ptr->advertising_set = advertising_set;
  ptr->subevent = subevent;
  ptr->response_slot_start = response_slot_start;
  ptr->response_slot_count = response_slot_count;
  ptr->adv_data_len = adv_data_len;
  ptr->adv_data = adv_data;
};
void push_pawr_advertiser_create_connection(uint8_t advertising_set,uint8_t subevent,bd_addr address,uint8_t address_type) {
  struct command_s *cmd = push_command(PAWR_ADVERTISER_CREATE_CONNECTION);
  struct pawr_advertiser_create_connection_s *ptr = &cmd->pawr_advertiser_create_connection;
  ptr->advertising_set = advertising_set;
  ptr->subevent = subevent;
  ptr->address = address;
  ptr->address_type = address_type;
};
void push_pawr_advertiser_stop(uint8_t advertising_set) {
  struct command_s *cmd = push_command(PAWR_ADVERTISER_STOP);
  struct pawr_advertiser_stop_s *ptr = &cmd->pawr_advertiser_stop;
  ptr->advertising_set = advertising_set;
};
void push_legacy_advertiser_set_data(uint8_t advertising_set,uint8_t type,size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(LEGACY_ADVERTISER_SET_DATA);
  struct legacy_advertiser_set_data_s *ptr = &cmd->legacy_advertiser_set_data;
  ptr->advertising_set = advertising_set;
  ptr->type = type;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_legacy_advertiser_generate_data(uint8_t advertising_set,uint8_t discover) {
  struct command_s *cmd = push_command(LEGACY_ADVERTISER_GENERATE_DATA);
  struct legacy_advertiser_generate_data_s *ptr = &cmd->legacy_advertiser_generate_data;
  ptr->advertising_set = advertising_set;
  ptr->discover = discover;
};
void push_legacy_advertiser_start(uint8_t advertising_set,uint8_t connect) {
  struct command_s *cmd = push_command(LEGACY_ADVERTISER_START);
  struct legacy_advertiser_start_s *ptr = &cmd->legacy_advertiser_start;
  ptr->advertising_set = advertising_set;
  ptr->connect = connect;
};
void push_legacy_advertiser_start_directed(uint8_t advertising_set,uint8_t connect,bd_addr peer_addr,uint8_t peer_addr_type) {
  struct command_s *cmd = push_command(LEGACY_ADVERTISER_START_DIRECTED);
  struct legacy_advertiser_start_directed_s *ptr = &cmd->legacy_advertiser_start_directed;
  ptr->advertising_set = advertising_set;
  ptr->connect = connect;
  ptr->peer_addr = peer_addr;
  ptr->peer_addr_type = peer_addr_type;
};
void push_extended_advertiser_set_phy(uint8_t advertising_set,uint8_t primary_phy,uint8_t secondary_phy) {
  struct command_s *cmd = push_command(EXTENDED_ADVERTISER_SET_PHY);
  struct extended_advertiser_set_phy_s *ptr = &cmd->extended_advertiser_set_phy;
  ptr->advertising_set = advertising_set;
  ptr->primary_phy = primary_phy;
  ptr->secondary_phy = secondary_phy;
};
void push_extended_advertiser_set_data(uint8_t advertising_set,size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(EXTENDED_ADVERTISER_SET_DATA);
  struct extended_advertiser_set_data_s *ptr = &cmd->extended_advertiser_set_data;
  ptr->advertising_set = advertising_set;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_extended_advertiser_set_long_data(uint8_t advertising_set) {
  struct command_s *cmd = push_command(EXTENDED_ADVERTISER_SET_LONG_DATA);
  struct extended_advertiser_set_long_data_s *ptr = &cmd->extended_advertiser_set_long_data;
  ptr->advertising_set = advertising_set;
};
void push_extended_advertiser_generate_data(uint8_t advertising_set,uint8_t discover) {
  struct command_s *cmd = push_command(EXTENDED_ADVERTISER_GENERATE_DATA);
  struct extended_advertiser_generate_data_s *ptr = &cmd->extended_advertiser_generate_data;
  ptr->advertising_set = advertising_set;
  ptr->discover = discover;
};
void push_extended_advertiser_start(uint8_t advertising_set,uint8_t connect,uint32_t flags) {
  struct command_s *cmd = push_command(EXTENDED_ADVERTISER_START);
  struct extended_advertiser_start_s *ptr = &cmd->extended_advertiser_start;
  ptr->advertising_set = advertising_set;
  ptr->connect = connect;
  ptr->flags = flags;
};
void push_extended_advertiser_start_directed(uint8_t advertising_set,uint8_t connect,uint32_t flags,bd_addr peer_addr,uint8_t peer_addr_type) {
  struct command_s *cmd = push_command(EXTENDED_ADVERTISER_START_DIRECTED);
  struct extended_advertiser_start_directed_s *ptr = &cmd->extended_advertiser_start_directed;
  ptr->advertising_set = advertising_set;
  ptr->connect = connect;
  ptr->flags = flags;
  ptr->peer_addr = peer_addr;
  ptr->peer_addr_type = peer_addr_type;
};
void push_periodic_advertiser_set_data(uint8_t advertising_set,size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(PERIODIC_ADVERTISER_SET_DATA);
  struct periodic_advertiser_set_data_s *ptr = &cmd->periodic_advertiser_set_data;
  ptr->advertising_set = advertising_set;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_periodic_advertiser_set_long_data(uint8_t advertising_set) {
  struct command_s *cmd = push_command(PERIODIC_ADVERTISER_SET_LONG_DATA);
  struct periodic_advertiser_set_long_data_s *ptr = &cmd->periodic_advertiser_set_long_data;
  ptr->advertising_set = advertising_set;
};
void push_periodic_advertiser_start(uint8_t advertising_set,uint16_t interval_min,uint16_t interval_max,uint32_t flags) {
  struct command_s *cmd = push_command(PERIODIC_ADVERTISER_START);
  struct periodic_advertiser_start_s *ptr = &cmd->periodic_advertiser_start;
  ptr->advertising_set = advertising_set;
  ptr->interval_min = interval_min;
  ptr->interval_max = interval_max;
  ptr->flags = flags;
};
void push_periodic_advertiser_stop(uint8_t advertising_set) {
  struct command_s *cmd = push_command(PERIODIC_ADVERTISER_STOP);
  struct periodic_advertiser_stop_s *ptr = &cmd->periodic_advertiser_stop;
  ptr->advertising_set = advertising_set;
};
void push_cs_security_enable(uint8_t connection) {
  struct command_s *cmd = push_command(CS_SECURITY_ENABLE);
  struct cs_security_enable_s *ptr = &cmd->cs_security_enable;
  ptr->connection = connection;
};
void push_cs_set_default_settings(uint8_t connection,uint8_t initiator_status,uint8_t reflector_status,uint8_t antenna_identifier,int8_t max_tx_power) {
  struct command_s *cmd = push_command(CS_SET_DEFAULT_SETTINGS);
  struct cs_set_default_settings_s *ptr = &cmd->cs_set_default_settings;
  ptr->connection = connection;
  ptr->initiator_status = initiator_status;
  ptr->reflector_status = reflector_status;
  ptr->antenna_identifier = antenna_identifier;
  ptr->max_tx_power = max_tx_power;
};
void push_cs_create_config(uint8_t connection,uint8_t config_id,uint8_t create_context,uint8_t main_mode_type,uint8_t sub_mode_type,uint8_t min_main_mode_steps,uint8_t max_main_mode_steps,uint8_t main_mode_repetition,uint8_t mode_calibration_steps,uint8_t role,uint8_t rtt_type,uint8_t cs_sync_phy,sl_bt_cs_channel_map_t *channel_map,uint8_t channel_map_repetition,uint8_t channel_selection_type,uint8_t ch3c_shape,uint8_t ch3c_jump,uint8_t companion_signal_state) {
  struct command_s *cmd = push_command(CS_CREATE_CONFIG);
  struct cs_create_config_s *ptr = &cmd->cs_create_config;
  ptr->connection = connection;
  ptr->config_id = config_id;
  ptr->create_context = create_context;
  ptr->main_mode_type = main_mode_type;
  ptr->sub_mode_type = sub_mode_type;
  ptr->min_main_mode_steps = min_main_mode_steps;
  ptr->max_main_mode_steps = max_main_mode_steps;
  ptr->main_mode_repetition = main_mode_repetition;
  ptr->mode_calibration_steps = mode_calibration_steps;
  ptr->role = role;
  ptr->rtt_type = rtt_type;
  ptr->cs_sync_phy = cs_sync_phy;
  ptr->channel_map = channel_map;
  ptr->channel_map_repetition = channel_map_repetition;
  ptr->channel_selection_type = channel_selection_type;
  ptr->ch3c_shape = ch3c_shape;
  ptr->ch3c_jump = ch3c_jump;
  ptr->companion_signal_state = companion_signal_state;
};
void push_cs_remove_config(uint8_t connection,uint8_t config_id) {
  struct command_s *cmd = push_command(CS_REMOVE_CONFIG);
  struct cs_remove_config_s *ptr = &cmd->cs_remove_config;
  ptr->connection = connection;
  ptr->config_id = config_id;
};
void push_cs_set_channel_classification(sl_bt_cs_channel_map_t *channel_map) {
  struct command_s *cmd = push_command(CS_SET_CHANNEL_CLASSIFICATION);
  struct cs_set_channel_classification_s *ptr = &cmd->cs_set_channel_classification;
  ptr->channel_map = channel_map;
};
void push_cs_set_procedure_parameters(uint8_t connection,uint8_t config_id,uint16_t max_procedure_len,uint16_t min_procedure_interval,uint16_t max_procedure_interval,uint16_t max_procedure_count,uint32_t min_subevent_len,uint32_t max_subevent_len,uint8_t tone_antenna_config_selection,uint8_t phy,int8_t tx_pwr_delta,uint8_t preferred_peer_antenna) {
  struct command_s *cmd = push_command(CS_SET_PROCEDURE_PARAMETERS);
  struct cs_set_procedure_parameters_s *ptr = &cmd->cs_set_procedure_parameters;
  ptr->connection = connection;
  ptr->config_id = config_id;
  ptr->max_procedure_len = max_procedure_len;
  ptr->min_procedure_interval = min_procedure_interval;
  ptr->max_procedure_interval = max_procedure_interval;
  ptr->max_procedure_count = max_procedure_count;
  ptr->min_subevent_len = min_subevent_len;
  ptr->max_subevent_len = max_subevent_len;
  ptr->tone_antenna_config_selection = tone_antenna_config_selection;
  ptr->phy = phy;
  ptr->tx_pwr_delta = tx_pwr_delta;
  ptr->preferred_peer_antenna = preferred_peer_antenna;
};
void push_cs_procedure_enable(uint8_t connection,uint8_t enable,uint8_t config_id) {
  struct command_s *cmd = push_command(CS_PROCEDURE_ENABLE);
  struct cs_procedure_enable_s *ptr = &cmd->cs_procedure_enable;
  ptr->connection = connection;
  ptr->enable = enable;
  ptr->config_id = config_id;
};
void push_cs_set_antenna_configuration(size_t antenna_element_offset_len,uint8_t *antenna_element_offset) {
  struct command_s *cmd = push_command(CS_SET_ANTENNA_CONFIGURATION);
  struct cs_set_antenna_configuration_s *ptr = &cmd->cs_set_antenna_configuration;
  ptr->antenna_element_offset_len = antenna_element_offset_len;
  ptr->antenna_element_offset = antenna_element_offset;
};
void push_cs_read_local_supported_capabilities() {
  struct command_s *cmd = push_command(CS_READ_LOCAL_SUPPORTED_CAPABILITIES);
  (void)cmd;
};
void push_cs_test_start(uint8_t main_mode_type,uint8_t sub_mode_type,uint8_t main_mode_repetition,uint8_t mode_calibration_steps,uint8_t role,uint8_t rtt_type,uint8_t cs_sync_phy,uint8_t antenna_selection,sl_bt_cs_subevent_length_t *subevent_len,uint16_t subevent_interval,int8_t tx_power,uint8_t t_ip1_time,uint8_t t_ip2_time,uint8_t t_fcs_time,uint8_t t_pm_time,uint8_t t_sw_time,uint8_t tone_antenna_config,uint8_t companion_signal_state,uint16_t drbg_nonce,uint16_t override_config,size_t override_parameters_len,uint8_t *override_parameters) {
  struct command_s *cmd = push_command(CS_TEST_START);
  struct cs_test_start_s *ptr = &cmd->cs_test_start;
  ptr->main_mode_type = main_mode_type;
  ptr->sub_mode_type = sub_mode_type;
  ptr->main_mode_repetition = main_mode_repetition;
  ptr->mode_calibration_steps = mode_calibration_steps;
  ptr->role = role;
  ptr->rtt_type = rtt_type;
  ptr->cs_sync_phy = cs_sync_phy;
  ptr->antenna_selection = antenna_selection;
  ptr->subevent_len = subevent_len;
  ptr->subevent_interval = subevent_interval;
  ptr->tx_power = tx_power;
  ptr->t_ip1_time = t_ip1_time;
  ptr->t_ip2_time = t_ip2_time;
  ptr->t_fcs_time = t_fcs_time;
  ptr->t_pm_time = t_pm_time;
  ptr->t_sw_time = t_sw_time;
  ptr->tone_antenna_config = tone_antenna_config;
  ptr->companion_signal_state = companion_signal_state;
  ptr->drbg_nonce = drbg_nonce;
  ptr->override_config = override_config;
  ptr->override_parameters_len = override_parameters_len;
  ptr->override_parameters = override_parameters;
};
void push_sync_past_transfer(uint8_t connection,uint16_t service_data,uint16_t sync) {
  struct command_s *cmd = push_command(SYNC_PAST_TRANSFER);
  struct sync_past_transfer_s *ptr = &cmd->sync_past_transfer;
  ptr->connection = connection;
  ptr->service_data = service_data;
  ptr->sync = sync;
};
void push_external_bondingdb_set_data(uint8_t connection,uint8_t type,size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(EXTERNAL_BONDINGDB_SET_DATA);
  struct external_bondingdb_set_data_s *ptr = &cmd->external_bondingdb_set_data;
  ptr->connection = connection;
  ptr->type = type;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_resolving_list_add_device_by_bonding(uint32_t bonding,uint8_t privacy_mode) {
  struct command_s *cmd = push_command(RESOLVING_LIST_ADD_DEVICE_BY_BONDING);
  struct resolving_list_add_device_by_bonding_s *ptr = &cmd->resolving_list_add_device_by_bonding;
  ptr->bonding = bonding;
  ptr->privacy_mode = privacy_mode;
};
void push_resolving_list_add_device_by_address(bd_addr address,uint8_t address_type,aes_key_128 key,uint8_t privacy_mode) {
  struct command_s *cmd = push_command(RESOLVING_LIST_ADD_DEVICE_BY_ADDRESS);
  struct resolving_list_add_device_by_address_s *ptr = &cmd->resolving_list_add_device_by_address;
  ptr->address = address;
  ptr->address_type = address_type;
  ptr->key = key;
  ptr->privacy_mode = privacy_mode;
};
void push_resolving_list_remove_device_by_bonding(uint32_t bonding) {
  struct command_s *cmd = push_command(RESOLVING_LIST_REMOVE_DEVICE_BY_BONDING);
  struct resolving_list_remove_device_by_bonding_s *ptr = &cmd->resolving_list_remove_device_by_bonding;
  ptr->bonding = bonding;
};
void push_resolving_list_remove_device_by_address(bd_addr address,uint8_t address_type) {
  struct command_s *cmd = push_command(RESOLVING_LIST_REMOVE_DEVICE_BY_ADDRESS);
  struct resolving_list_remove_device_by_address_s *ptr = &cmd->resolving_list_remove_device_by_address;
  ptr->address = address;
  ptr->address_type = address_type;
};
void push_resolving_list_remove_all_devices() {
  struct command_s *cmd = push_command(RESOLVING_LIST_REMOVE_ALL_DEVICES);
  (void)cmd;
};
void push_accept_list_add_device_by_bonding(uint32_t bonding) {
  struct command_s *cmd = push_command(ACCEPT_LIST_ADD_DEVICE_BY_BONDING);
  struct accept_list_add_device_by_bonding_s *ptr = &cmd->accept_list_add_device_by_bonding;
  ptr->bonding = bonding;
};
void push_accept_list_add_device_by_address(bd_addr address,uint8_t address_type) {
  struct command_s *cmd = push_command(ACCEPT_LIST_ADD_DEVICE_BY_ADDRESS);
  struct accept_list_add_device_by_address_s *ptr = &cmd->accept_list_add_device_by_address;
  ptr->address = address;
  ptr->address_type = address_type;
};
void push_accept_list_remove_device_by_bonding(uint32_t bonding) {
  struct command_s *cmd = push_command(ACCEPT_LIST_REMOVE_DEVICE_BY_BONDING);
  struct accept_list_remove_device_by_bonding_s *ptr = &cmd->accept_list_remove_device_by_bonding;
  ptr->bonding = bonding;
};
void push_accept_list_remove_device_by_address(bd_addr address,uint8_t address_type) {
  struct command_s *cmd = push_command(ACCEPT_LIST_REMOVE_DEVICE_BY_ADDRESS);
  struct accept_list_remove_device_by_address_s *ptr = &cmd->accept_list_remove_device_by_address;
  ptr->address = address;
  ptr->address_type = address_type;
};
void push_accept_list_remove_all_devices() {
  struct command_s *cmd = push_command(ACCEPT_LIST_REMOVE_ALL_DEVICES);
  (void)cmd;
};
void push_resource_get_status() {
  struct command_s *cmd = push_command(RESOURCE_GET_STATUS);
  (void)cmd;
};
void push_resource_set_report_threshold(uint32_t low,uint32_t high) {
  struct command_s *cmd = push_command(RESOURCE_SET_REPORT_THRESHOLD);
  struct resource_set_report_threshold_s *ptr = &cmd->resource_set_report_threshold;
  ptr->low = low;
  ptr->high = high;
};
void push_resource_enable_connection_tx_report(uint16_t packet_count) {
  struct command_s *cmd = push_command(RESOURCE_ENABLE_CONNECTION_TX_REPORT);
  struct resource_enable_connection_tx_report_s *ptr = &cmd->resource_enable_connection_tx_report;
  ptr->packet_count = packet_count;
};
void push_resource_get_connection_tx_status(uint8_t connection) {
  struct command_s *cmd = push_command(RESOURCE_GET_CONNECTION_TX_STATUS);
  struct resource_get_connection_tx_status_s *ptr = &cmd->resource_get_connection_tx_status;
  ptr->connection = connection;
};
void push_resource_disable_connection_tx_report() {
  struct command_s *cmd = push_command(RESOURCE_DISABLE_CONNECTION_TX_REPORT);
  (void)cmd;
};
void push_user_message_to_target(size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(USER_MESSAGE_TO_TARGET);
  struct user_message_to_target_s *ptr = &cmd->user_message_to_target;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_user_manage_event_filter(size_t data_len,uint8_t *data) {
  struct command_s *cmd = push_command(USER_MANAGE_EVENT_FILTER);
  struct user_manage_event_filter_s *ptr = &cmd->user_manage_event_filter;
  ptr->data_len = data_len;
  ptr->data = data;
};
void push_user_reset_to_dfu() {
  struct command_s *cmd = push_command(USER_RESET_TO_DFU);
  (void)cmd;
};

void command_process(void) {
  sl_status_t sc;
  struct command_s *ptr = cmds.head;
  if(NULL == ptr) return;
  switch(ptr->type) {
  case DFU_FLASH_SET_ADDRESS :
    sc = sl_bt_dfu_flash_set_address(ptr->dfu_flash_set_address.address);
    ptr->result = sc;
    break;
  case DFU_FLASH_UPLOAD :
    sc = sl_bt_dfu_flash_upload(ptr->dfu_flash_upload.data_len, ptr->dfu_flash_upload.data);
    ptr->result = sc;
    break;
  case DFU_FLASH_UPLOAD_FINISH :
    sc = sl_bt_dfu_flash_upload_finish();
    ptr->result = sc;
    break;
  case SYSTEM_HELLO :
    sc = sl_bt_system_hello();
    ptr->result = sc;
    break;
  case SYSTEM_START_BLUETOOTH :
    sc = sl_bt_system_start_bluetooth();
    ptr->result = sc;
    break;
  case SYSTEM_STOP_BLUETOOTH :
    sc = sl_bt_system_stop_bluetooth();
    ptr->result = sc;
    break;
  case SYSTEM_FORCEFULLY_STOP_BLUETOOTH :
    sc = sl_bt_system_forcefully_stop_bluetooth();
    ptr->result = sc;
    break;
  case SYSTEM_GET_VERSION :
    sc = sl_bt_system_get_version(&ptr->system_get_version.major, &ptr->system_get_version.minor, &ptr->system_get_version.patch, &ptr->system_get_version.build, &ptr->system_get_version.bootloader, &ptr->system_get_version.hash);
    ptr->result = sc;
    break;
  case SYSTEM_RESET :
    sl_bt_system_reset(ptr->system_reset.dfu);
    break;
  case SYSTEM_HALT :
    sc = sl_bt_system_halt(ptr->system_halt.halt);
    ptr->result = sc;
    break;
  case SYSTEM_LINKLAYER_CONFIGURE :
    sc = sl_bt_system_linklayer_configure(ptr->system_linklayer_configure.key, ptr->system_linklayer_configure.data_len, ptr->system_linklayer_configure.data);
    ptr->result = sc;
    break;
  case SYSTEM_SET_TX_POWER :
    sc = sl_bt_system_set_tx_power(ptr->system_set_tx_power.min_power, ptr->system_set_tx_power.max_power, &ptr->system_set_tx_power.set_min, &ptr->system_set_tx_power.set_max);
    ptr->result = sc;
    break;
  case SYSTEM_GET_TX_POWER_SETTING :
    sc = sl_bt_system_get_tx_power_setting(&ptr->system_get_tx_power_setting.support_min, &ptr->system_get_tx_power_setting.support_max, &ptr->system_get_tx_power_setting.set_min, &ptr->system_get_tx_power_setting.set_max, &ptr->system_get_tx_power_setting.rf_path_gain);
    ptr->result = sc;
    break;
  case SYSTEM_SET_IDENTITY_ADDRESS :
    sc = sl_bt_system_set_identity_address(ptr->system_set_identity_address.address, ptr->system_set_identity_address.type);
    ptr->result = sc;
    break;
  case SYSTEM_GET_IDENTITY_ADDRESS :
    sc = sl_bt_system_get_identity_address(&ptr->system_get_identity_address.address, &ptr->system_get_identity_address.type);
    ptr->result = sc;
    break;
  case SYSTEM_GET_RANDOM_DATA :
    sc = sl_bt_system_get_random_data(ptr->system_get_random_data.length, ptr->system_get_random_data.data_max_len, ptr->system_get_random_data.data_len, ptr->system_get_random_data.data);
    ptr->result = sc;
    break;
  case SYSTEM_DATA_BUFFER_WRITE :
    sc = sl_bt_system_data_buffer_write(ptr->system_data_buffer_write.data_len, ptr->system_data_buffer_write.data);
    ptr->result = sc;
    break;
  case SYSTEM_DATA_BUFFER_CLEAR :
    sc = sl_bt_system_data_buffer_clear();
    ptr->result = sc;
    break;
  case SYSTEM_GET_COUNTERS :
    sc = sl_bt_system_get_counters(ptr->system_get_counters.reset, &ptr->system_get_counters.tx_packets, &ptr->system_get_counters.rx_packets, &ptr->system_get_counters.crc_errors, &ptr->system_get_counters.failures);
    ptr->result = sc;
    break;
  case SYSTEM_SET_LAZY_SOFT_TIMER :
    sc = sl_bt_system_set_lazy_soft_timer(ptr->system_set_lazy_soft_timer.time, ptr->system_set_lazy_soft_timer.slack, ptr->system_set_lazy_soft_timer.handle, ptr->system_set_lazy_soft_timer.single_shot);
    ptr->result = sc;
    break;
  case GAP_SET_PRIVACY_MODE :
    sc = sl_bt_gap_set_privacy_mode(ptr->gap_set_privacy_mode.privacy, ptr->gap_set_privacy_mode.interval);
    ptr->result = sc;
    break;
  case GAP_SET_DATA_CHANNEL_CLASSIFICATION :
    sc = sl_bt_gap_set_data_channel_classification(ptr->gap_set_data_channel_classification.channel_map_len, ptr->gap_set_data_channel_classification.channel_map);
    ptr->result = sc;
    break;
  case GAP_ENABLE_WHITELISTING :
    sc = sl_bt_gap_enable_whitelisting(ptr->gap_enable_whitelisting.enable);
    ptr->result = sc;
    break;
  case GAP_SET_IDENTITY_ADDRESS :
    sc = sl_bt_gap_set_identity_address(ptr->gap_set_identity_address.address, ptr->gap_set_identity_address.addr_type);
    ptr->result = sc;
    break;
  case ADVERTISER_CREATE_SET :
    sc = sl_bt_advertiser_create_set(&ptr->advertiser_create_set.handle);
    ptr->result = sc;
    break;
  case ADVERTISER_CONFIGURE :
    sc = sl_bt_advertiser_configure(ptr->advertiser_configure.advertising_set, ptr->advertiser_configure.flags);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_TIMING :
    sc = sl_bt_advertiser_set_timing(ptr->advertiser_set_timing.advertising_set, ptr->advertiser_set_timing.interval_min, ptr->advertiser_set_timing.interval_max, ptr->advertiser_set_timing.duration, ptr->advertiser_set_timing.maxevents);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_CHANNEL_MAP :
    sc = sl_bt_advertiser_set_channel_map(ptr->advertiser_set_channel_map.advertising_set, ptr->advertiser_set_channel_map.channel_map);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_TX_POWER :
    sc = sl_bt_advertiser_set_tx_power(ptr->advertiser_set_tx_power.advertising_set, ptr->advertiser_set_tx_power.power, &ptr->advertiser_set_tx_power.set_power);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_REPORT_SCAN_REQUEST :
    sc = sl_bt_advertiser_set_report_scan_request(ptr->advertiser_set_report_scan_request.advertising_set, ptr->advertiser_set_report_scan_request.report_scan_req);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_RANDOM_ADDRESS :
    sc = sl_bt_advertiser_set_random_address(ptr->advertiser_set_random_address.advertising_set, ptr->advertiser_set_random_address.addr_type, ptr->advertiser_set_random_address.address, &ptr->advertiser_set_random_address.address_out);
    ptr->result = sc;
    break;
  case ADVERTISER_CLEAR_RANDOM_ADDRESS :
    sc = sl_bt_advertiser_clear_random_address(ptr->advertiser_clear_random_address.advertising_set);
    ptr->result = sc;
    break;
  case ADVERTISER_STOP :
    sc = sl_bt_advertiser_stop(ptr->advertiser_stop.advertising_set);
    ptr->result = sc;
    break;
  case ADVERTISER_DELETE_SET :
    sc = sl_bt_advertiser_delete_set(ptr->advertiser_delete_set.advertising_set);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_PHY :
    sc = sl_bt_advertiser_set_phy(ptr->advertiser_set_phy.advertising_set, ptr->advertiser_set_phy.primary_phy, ptr->advertiser_set_phy.secondary_phy);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_CONFIGURATION :
    sc = sl_bt_advertiser_set_configuration(ptr->advertiser_set_configuration.advertising_set, ptr->advertiser_set_configuration.configurations);
    ptr->result = sc;
    break;
  case ADVERTISER_CLEAR_CONFIGURATION :
    sc = sl_bt_advertiser_clear_configuration(ptr->advertiser_clear_configuration.advertising_set, ptr->advertiser_clear_configuration.configurations);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_DATA :
    sc = sl_bt_advertiser_set_data(ptr->advertiser_set_data.advertising_set, ptr->advertiser_set_data.packet_type, ptr->advertiser_set_data.adv_data_len, ptr->advertiser_set_data.adv_data);
    ptr->result = sc;
    break;
  case ADVERTISER_SET_LONG_DATA :
    sc = sl_bt_advertiser_set_long_data(ptr->advertiser_set_long_data.advertising_set, ptr->advertiser_set_long_data.packet_type);
    ptr->result = sc;
    break;
  case ADVERTISER_START :
    sc = sl_bt_advertiser_start(ptr->advertiser_start.advertising_set, ptr->advertiser_start.discover, ptr->advertiser_start.connect);
    ptr->result = sc;
    break;
  case ADVERTISER_START_PERIODIC_ADVERTISING :
    sc = sl_bt_advertiser_start_periodic_advertising(ptr->advertiser_start_periodic_advertising.advertising_set, ptr->advertiser_start_periodic_advertising.interval_min, ptr->advertiser_start_periodic_advertising.interval_max, ptr->advertiser_start_periodic_advertising.flags);
    ptr->result = sc;
    break;
  case ADVERTISER_STOP_PERIODIC_ADVERTISING :
    sc = sl_bt_advertiser_stop_periodic_advertising(ptr->advertiser_stop_periodic_advertising.advertising_set);
    ptr->result = sc;
    break;
  case SCANNER_SET_PARAMETERS :
    sc = sl_bt_scanner_set_parameters(ptr->scanner_set_parameters.mode, ptr->scanner_set_parameters.interval, ptr->scanner_set_parameters.window);
    ptr->result = sc;
    break;
  case SCANNER_SET_PARAMETERS_AND_FILTER :
    sc = sl_bt_scanner_set_parameters_and_filter(ptr->scanner_set_parameters_and_filter.mode, ptr->scanner_set_parameters_and_filter.interval, ptr->scanner_set_parameters_and_filter.window, ptr->scanner_set_parameters_and_filter.flags, ptr->scanner_set_parameters_and_filter.filter_policy);
    ptr->result = sc;
    break;
  case SCANNER_STOP :
    sc = sl_bt_scanner_stop();
    ptr->result = sc;
    break;
  case SCANNER_SET_TIMING :
    sc = sl_bt_scanner_set_timing(ptr->scanner_set_timing.phys, ptr->scanner_set_timing.scan_interval, ptr->scanner_set_timing.scan_window);
    ptr->result = sc;
    break;
  case SCANNER_SET_MODE :
    sc = sl_bt_scanner_set_mode(ptr->scanner_set_mode.phys, ptr->scanner_set_mode.scan_mode);
    ptr->result = sc;
    break;
  case SCANNER_START :
    sc = sl_bt_scanner_start(ptr->scanner_start.scanning_phy, ptr->scanner_start.discover_mode);
    ptr->result = sc;
    break;
  case CONNECTION_SET_DEFAULT_PARAMETERS :
    sc = sl_bt_connection_set_default_parameters(ptr->connection_set_default_parameters.min_interval, ptr->connection_set_default_parameters.max_interval, ptr->connection_set_default_parameters.latency, ptr->connection_set_default_parameters.timeout, ptr->connection_set_default_parameters.min_ce_length, ptr->connection_set_default_parameters.max_ce_length);
    ptr->result = sc;
    break;
  case CONNECTION_SET_DEFAULT_PREFERRED_PHY :
    sc = sl_bt_connection_set_default_preferred_phy(ptr->connection_set_default_preferred_phy.preferred_phy, ptr->connection_set_default_preferred_phy.accepted_phy);
    ptr->result = sc;
    break;
  case CONNECTION_SET_DEFAULT_DATA_LENGTH :
    sc = sl_bt_connection_set_default_data_length(ptr->connection_set_default_data_length.tx_data_len);
    ptr->result = sc;
    break;
  case CONNECTION_OPEN :
    sc = sl_bt_connection_open(ptr->connection_open.address, ptr->connection_open.address_type, ptr->connection_open.initiating_phy, &ptr->connection_open.connection);
    ptr->result = sc;
    break;
  case CONNECTION_SET_PARAMETERS :
    sc = sl_bt_connection_set_parameters(ptr->connection_set_parameters.connection, ptr->connection_set_parameters.min_interval, ptr->connection_set_parameters.max_interval, ptr->connection_set_parameters.latency, ptr->connection_set_parameters.timeout, ptr->connection_set_parameters.min_ce_length, ptr->connection_set_parameters.max_ce_length);
    ptr->result = sc;
    break;
  case CONNECTION_SET_PREFERRED_PHY :
    sc = sl_bt_connection_set_preferred_phy(ptr->connection_set_preferred_phy.connection, ptr->connection_set_preferred_phy.preferred_phy, ptr->connection_set_preferred_phy.accepted_phy);
    ptr->result = sc;
    break;
  case CONNECTION_DISABLE_SLAVE_LATENCY :
    sc = sl_bt_connection_disable_slave_latency(ptr->connection_disable_slave_latency.connection, ptr->connection_disable_slave_latency.disable);
    ptr->result = sc;
    break;
  case CONNECTION_GET_MEDIAN_RSSI :
    sc = sl_bt_connection_get_median_rssi(ptr->connection_get_median_rssi.connection, &ptr->connection_get_median_rssi.rssi);
    ptr->result = sc;
    break;
  case CONNECTION_READ_CHANNEL_MAP :
    sc = sl_bt_connection_read_channel_map(ptr->connection_read_channel_map.connection, ptr->connection_read_channel_map.channel_map_max_len, ptr->connection_read_channel_map.channel_map_len, ptr->connection_read_channel_map.channel_map);
    ptr->result = sc;
    break;
  case CONNECTION_SET_POWER_REPORTING :
    sc = sl_bt_connection_set_power_reporting(ptr->connection_set_power_reporting.connection, ptr->connection_set_power_reporting.mode);
    ptr->result = sc;
    break;
  case CONNECTION_SET_REMOTE_POWER_REPORTING :
    sc = sl_bt_connection_set_remote_power_reporting(ptr->connection_set_remote_power_reporting.connection, ptr->connection_set_remote_power_reporting.mode);
    ptr->result = sc;
    break;
  case CONNECTION_GET_TX_POWER :
    sc = sl_bt_connection_get_tx_power(ptr->connection_get_tx_power.connection, ptr->connection_get_tx_power.phy, &ptr->connection_get_tx_power.current_level, &ptr->connection_get_tx_power.max_level);
    ptr->result = sc;
    break;
  case CONNECTION_GET_REMOTE_TX_POWER :
    sc = sl_bt_connection_get_remote_tx_power(ptr->connection_get_remote_tx_power.connection, ptr->connection_get_remote_tx_power.phy);
    ptr->result = sc;
    break;
  case CONNECTION_SET_TX_POWER :
    sc = sl_bt_connection_set_tx_power(ptr->connection_set_tx_power.connection, ptr->connection_set_tx_power.tx_power, &ptr->connection_set_tx_power.tx_power_out);
    ptr->result = sc;
    break;
  case CONNECTION_READ_REMOTE_USED_FEATURES :
    sc = sl_bt_connection_read_remote_used_features(ptr->connection_read_remote_used_features.connection);
    ptr->result = sc;
    break;
  case CONNECTION_GET_SECURITY_STATUS :
    sc = sl_bt_connection_get_security_status(ptr->connection_get_security_status.connection, &ptr->connection_get_security_status.security_mode, &ptr->connection_get_security_status.key_size, &ptr->connection_get_security_status.bonding_handle);
    ptr->result = sc;
    break;
  case CONNECTION_SET_DATA_LENGTH :
    sc = sl_bt_connection_set_data_length(ptr->connection_set_data_length.connection, ptr->connection_set_data_length.tx_data_len, ptr->connection_set_data_length.tx_time_us);
    ptr->result = sc;
    break;
  case CONNECTION_READ_STATISTICS :
    sc = sl_bt_connection_read_statistics(ptr->connection_read_statistics.connection, ptr->connection_read_statistics.reset);
    ptr->result = sc;
    break;
  case CONNECTION_GET_SCHEDULING_DETAILS :
    sc = sl_bt_connection_get_scheduling_details(ptr->connection_get_scheduling_details.connection, &ptr->connection_get_scheduling_details.access_address, &ptr->connection_get_scheduling_details.role, &ptr->connection_get_scheduling_details.crc_init, &ptr->connection_get_scheduling_details.interval, &ptr->connection_get_scheduling_details.supervision_timeout, &ptr->connection_get_scheduling_details.central_clock_accuracy, &ptr->connection_get_scheduling_details.central_phy, &ptr->connection_get_scheduling_details.peripheral_phy, &ptr->connection_get_scheduling_details.channel_selection_algorithm, &ptr->connection_get_scheduling_details.hop, ptr->connection_get_scheduling_details.channel_map, &ptr->connection_get_scheduling_details.channel, &ptr->connection_get_scheduling_details.event_counter, &ptr->connection_get_scheduling_details.start_time_us);
    ptr->result = sc;
    break;
  case CONNECTION_CLOSE :
    sc = sl_bt_connection_close(ptr->connection_close.connection);
    ptr->result = sc;
    break;
  case CONNECTION_FORCEFULLY_CLOSE :
    sc = sl_bt_connection_forcefully_close(ptr->connection_forcefully_close.connection);
    ptr->result = sc;
    break;
  case CONNECTION_GET_RSSI :
    sc = sl_bt_connection_get_rssi(ptr->connection_get_rssi.connection);
    ptr->result = sc;
    break;
  case GATT_SET_MAX_MTU :
    sc = sl_bt_gatt_set_max_mtu(ptr->gatt_set_max_mtu.max_mtu, &ptr->gatt_set_max_mtu.max_mtu_out);
    ptr->result = sc;
    break;
  case GATT_DISCOVER_PRIMARY_SERVICES :
    sc = sl_bt_gatt_discover_primary_services(ptr->gatt_discover_primary_services.connection);
    ptr->result = sc;
    break;
  case GATT_DISCOVER_PRIMARY_SERVICES_BY_UUID :
    sc = sl_bt_gatt_discover_primary_services_by_uuid(ptr->gatt_discover_primary_services_by_uuid.connection, ptr->gatt_discover_primary_services_by_uuid.uuid_len, ptr->gatt_discover_primary_services_by_uuid.uuid);
    ptr->result = sc;
    break;
  case GATT_FIND_INCLUDED_SERVICES :
    sc = sl_bt_gatt_find_included_services(ptr->gatt_find_included_services.connection, ptr->gatt_find_included_services.service);
    ptr->result = sc;
    break;
  case GATT_DISCOVER_CHARACTERISTICS :
    sc = sl_bt_gatt_discover_characteristics(ptr->gatt_discover_characteristics.connection, ptr->gatt_discover_characteristics.service);
    ptr->result = sc;
    break;
  case GATT_DISCOVER_CHARACTERISTICS_BY_UUID :
    sc = sl_bt_gatt_discover_characteristics_by_uuid(ptr->gatt_discover_characteristics_by_uuid.connection, ptr->gatt_discover_characteristics_by_uuid.service, ptr->gatt_discover_characteristics_by_uuid.uuid_len, ptr->gatt_discover_characteristics_by_uuid.uuid);
    ptr->result = sc;
    break;
  case GATT_DISCOVER_DESCRIPTORS :
    sc = sl_bt_gatt_discover_descriptors(ptr->gatt_discover_descriptors.connection, ptr->gatt_discover_descriptors.characteristic);
    ptr->result = sc;
    break;
  case GATT_DISCOVER_CHARACTERISTIC_DESCRIPTORS :
    sc = sl_bt_gatt_discover_characteristic_descriptors(ptr->gatt_discover_characteristic_descriptors.connection, ptr->gatt_discover_characteristic_descriptors.start, ptr->gatt_discover_characteristic_descriptors.end);
    ptr->result = sc;
    break;
  case GATT_SET_CHARACTERISTIC_NOTIFICATION :
    sc = sl_bt_gatt_set_characteristic_notification(ptr->gatt_set_characteristic_notification.connection, ptr->gatt_set_characteristic_notification.characteristic, ptr->gatt_set_characteristic_notification.flags);
    ptr->result = sc;
    break;
  case GATT_SEND_CHARACTERISTIC_CONFIRMATION :
    sc = sl_bt_gatt_send_characteristic_confirmation(ptr->gatt_send_characteristic_confirmation.connection);
    ptr->result = sc;
    break;
  case GATT_READ_CHARACTERISTIC_VALUE :
    sc = sl_bt_gatt_read_characteristic_value(ptr->gatt_read_characteristic_value.connection, ptr->gatt_read_characteristic_value.characteristic);
    ptr->result = sc;
    break;
  case GATT_READ_CHARACTERISTIC_VALUE_FROM_OFFSET :
    sc = sl_bt_gatt_read_characteristic_value_from_offset(ptr->gatt_read_characteristic_value_from_offset.connection, ptr->gatt_read_characteristic_value_from_offset.characteristic, ptr->gatt_read_characteristic_value_from_offset.offset, ptr->gatt_read_characteristic_value_from_offset.maxlen);
    ptr->result = sc;
    break;
  case GATT_READ_MULTIPLE_CHARACTERISTIC_VALUES :
    sc = sl_bt_gatt_read_multiple_characteristic_values(ptr->gatt_read_multiple_characteristic_values.connection, ptr->gatt_read_multiple_characteristic_values.characteristic_list_len, ptr->gatt_read_multiple_characteristic_values.characteristic_list);
    ptr->result = sc;
    break;
  case GATT_READ_CHARACTERISTIC_VALUE_BY_UUID :
    sc = sl_bt_gatt_read_characteristic_value_by_uuid(ptr->gatt_read_characteristic_value_by_uuid.connection, ptr->gatt_read_characteristic_value_by_uuid.service, ptr->gatt_read_characteristic_value_by_uuid.uuid_len, ptr->gatt_read_characteristic_value_by_uuid.uuid);
    ptr->result = sc;
    break;
  case GATT_WRITE_CHARACTERISTIC_VALUE :
    sc = sl_bt_gatt_write_characteristic_value(ptr->gatt_write_characteristic_value.connection, ptr->gatt_write_characteristic_value.characteristic, ptr->gatt_write_characteristic_value.value_len, ptr->gatt_write_characteristic_value.value);
    ptr->result = sc;
    break;
  case GATT_WRITE_CHARACTERISTIC_VALUE_WITHOUT_RESPONSE :
    sc = sl_bt_gatt_write_characteristic_value_without_response(ptr->gatt_write_characteristic_value_without_response.connection, ptr->gatt_write_characteristic_value_without_response.characteristic, ptr->gatt_write_characteristic_value_without_response.value_len, ptr->gatt_write_characteristic_value_without_response.value, &ptr->gatt_write_characteristic_value_without_response.sent_len);
    ptr->result = sc;
    break;
  case GATT_PREPARE_CHARACTERISTIC_VALUE_WRITE :
    sc = sl_bt_gatt_prepare_characteristic_value_write(ptr->gatt_prepare_characteristic_value_write.connection, ptr->gatt_prepare_characteristic_value_write.characteristic, ptr->gatt_prepare_characteristic_value_write.offset, ptr->gatt_prepare_characteristic_value_write.value_len, ptr->gatt_prepare_characteristic_value_write.value, &ptr->gatt_prepare_characteristic_value_write.sent_len);
    ptr->result = sc;
    break;
  case GATT_PREPARE_CHARACTERISTIC_VALUE_RELIABLE_WRITE :
    sc = sl_bt_gatt_prepare_characteristic_value_reliable_write(ptr->gatt_prepare_characteristic_value_reliable_write.connection, ptr->gatt_prepare_characteristic_value_reliable_write.characteristic, ptr->gatt_prepare_characteristic_value_reliable_write.offset, ptr->gatt_prepare_characteristic_value_reliable_write.value_len, ptr->gatt_prepare_characteristic_value_reliable_write.value, &ptr->gatt_prepare_characteristic_value_reliable_write.sent_len);
    ptr->result = sc;
    break;
  case GATT_EXECUTE_CHARACTERISTIC_VALUE_WRITE :
    sc = sl_bt_gatt_execute_characteristic_value_write(ptr->gatt_execute_characteristic_value_write.connection, ptr->gatt_execute_characteristic_value_write.flags);
    ptr->result = sc;
    break;
  case GATT_READ_DESCRIPTOR_VALUE :
    sc = sl_bt_gatt_read_descriptor_value(ptr->gatt_read_descriptor_value.connection, ptr->gatt_read_descriptor_value.descriptor);
    ptr->result = sc;
    break;
  case GATT_WRITE_DESCRIPTOR_VALUE :
    sc = sl_bt_gatt_write_descriptor_value(ptr->gatt_write_descriptor_value.connection, ptr->gatt_write_descriptor_value.descriptor, ptr->gatt_write_descriptor_value.value_len, ptr->gatt_write_descriptor_value.value);
    ptr->result = sc;
    break;
  case GATT_SERVER_SET_MAX_MTU :
    sc = sl_bt_gatt_server_set_max_mtu(ptr->gatt_server_set_max_mtu.max_mtu, &ptr->gatt_server_set_max_mtu.max_mtu_out);
    ptr->result = sc;
    break;
  case GATT_SERVER_GET_MTU :
    sc = sl_bt_gatt_server_get_mtu(ptr->gatt_server_get_mtu.connection, &ptr->gatt_server_get_mtu.mtu);
    ptr->result = sc;
    break;
  case GATT_SERVER_FIND_ATTRIBUTE :
    sc = sl_bt_gatt_server_find_attribute(ptr->gatt_server_find_attribute.start, ptr->gatt_server_find_attribute.type_len, ptr->gatt_server_find_attribute.type, &ptr->gatt_server_find_attribute.attribute);
    ptr->result = sc;
    break;
  case GATT_SERVER_READ_ATTRIBUTE_VALUE :
    sc = sl_bt_gatt_server_read_attribute_value(ptr->gatt_server_read_attribute_value.attribute, ptr->gatt_server_read_attribute_value.offset, ptr->gatt_server_read_attribute_value.value_max_len, ptr->gatt_server_read_attribute_value.value_len, ptr->gatt_server_read_attribute_value.value);
    ptr->result = sc;
    break;
  case GATT_SERVER_READ_ATTRIBUTE_TYPE :
    sc = sl_bt_gatt_server_read_attribute_type(ptr->gatt_server_read_attribute_type.attribute, ptr->gatt_server_read_attribute_type.type_max_len, ptr->gatt_server_read_attribute_type.type_len, ptr->gatt_server_read_attribute_type.type);
    ptr->result = sc;
    break;
  case GATT_SERVER_WRITE_ATTRIBUTE_VALUE :
    sc = sl_bt_gatt_server_write_attribute_value(ptr->gatt_server_write_attribute_value.attribute, ptr->gatt_server_write_attribute_value.offset, ptr->gatt_server_write_attribute_value.value_len, ptr->gatt_server_write_attribute_value.value);
    ptr->result = sc;
    break;
  case GATT_SERVER_SEND_USER_READ_RESPONSE :
    sc = sl_bt_gatt_server_send_user_read_response(ptr->gatt_server_send_user_read_response.connection, ptr->gatt_server_send_user_read_response.characteristic, ptr->gatt_server_send_user_read_response.att_errorcode, ptr->gatt_server_send_user_read_response.value_len, ptr->gatt_server_send_user_read_response.value, &ptr->gatt_server_send_user_read_response.sent_len);
    ptr->result = sc;
    break;
  case GATT_SERVER_SEND_USER_WRITE_RESPONSE :
    sc = sl_bt_gatt_server_send_user_write_response(ptr->gatt_server_send_user_write_response.connection, ptr->gatt_server_send_user_write_response.characteristic, ptr->gatt_server_send_user_write_response.att_errorcode);
    ptr->result = sc;
    break;
  case GATT_SERVER_SEND_NOTIFICATION :
    sc = sl_bt_gatt_server_send_notification(ptr->gatt_server_send_notification.connection, ptr->gatt_server_send_notification.characteristic, ptr->gatt_server_send_notification.value_len, ptr->gatt_server_send_notification.value);
    ptr->result = sc;
    break;
  case GATT_SERVER_SEND_INDICATION :
    sc = sl_bt_gatt_server_send_indication(ptr->gatt_server_send_indication.connection, ptr->gatt_server_send_indication.characteristic, ptr->gatt_server_send_indication.value_len, ptr->gatt_server_send_indication.value);
    ptr->result = sc;
    break;
  case GATT_SERVER_NOTIFY_ALL :
    sc = sl_bt_gatt_server_notify_all(ptr->gatt_server_notify_all.characteristic, ptr->gatt_server_notify_all.value_len, ptr->gatt_server_notify_all.value);
    ptr->result = sc;
    break;
  case GATT_SERVER_READ_CLIENT_CONFIGURATION :
    sc = sl_bt_gatt_server_read_client_configuration(ptr->gatt_server_read_client_configuration.connection, ptr->gatt_server_read_client_configuration.characteristic, &ptr->gatt_server_read_client_configuration.client_config_flags);
    ptr->result = sc;
    break;
  case GATT_SERVER_SEND_USER_PREPARE_WRITE_RESPONSE :
    sc = sl_bt_gatt_server_send_user_prepare_write_response(ptr->gatt_server_send_user_prepare_write_response.connection, ptr->gatt_server_send_user_prepare_write_response.characteristic, ptr->gatt_server_send_user_prepare_write_response.att_errorcode, ptr->gatt_server_send_user_prepare_write_response.offset, ptr->gatt_server_send_user_prepare_write_response.value_len, ptr->gatt_server_send_user_prepare_write_response.value);
    ptr->result = sc;
    break;
  case GATT_SERVER_SET_CAPABILITIES :
    sc = sl_bt_gatt_server_set_capabilities(ptr->gatt_server_set_capabilities.caps, ptr->gatt_server_set_capabilities.reserved);
    ptr->result = sc;
    break;
  case GATT_SERVER_ENABLE_CAPABILITIES :
    sc = sl_bt_gatt_server_enable_capabilities(ptr->gatt_server_enable_capabilities.caps);
    ptr->result = sc;
    break;
  case GATT_SERVER_DISABLE_CAPABILITIES :
    sc = sl_bt_gatt_server_disable_capabilities(ptr->gatt_server_disable_capabilities.caps);
    ptr->result = sc;
    break;
  case GATT_SERVER_GET_ENABLED_CAPABILITIES :
    sc = sl_bt_gatt_server_get_enabled_capabilities(&ptr->gatt_server_get_enabled_capabilities.caps);
    ptr->result = sc;
    break;
  case GATT_SERVER_READ_CLIENT_SUPPORTED_FEATURES :
    sc = sl_bt_gatt_server_read_client_supported_features(ptr->gatt_server_read_client_supported_features.connection, &ptr->gatt_server_read_client_supported_features.client_features);
    ptr->result = sc;
    break;
  case NVM_SAVE :
    sc = sl_bt_nvm_save(ptr->nvm_save.key, ptr->nvm_save.value_len, ptr->nvm_save.value);
    ptr->result = sc;
    break;
  case NVM_LOAD :
    sc = sl_bt_nvm_load(ptr->nvm_load.key, ptr->nvm_load.value_max_len, ptr->nvm_load.value_len, ptr->nvm_load.value);
    ptr->result = sc;
    break;
  case NVM_ERASE :
    sc = sl_bt_nvm_erase(ptr->nvm_erase.key);
    ptr->result = sc;
    break;
  case NVM_ERASE_ALL :
    sc = sl_bt_nvm_erase_all();
    ptr->result = sc;
    break;
  case TEST_DTM_TX_V4 :
    sc = sl_bt_test_dtm_tx_v4(ptr->test_dtm_tx_v4.packet_type, ptr->test_dtm_tx_v4.length, ptr->test_dtm_tx_v4.channel, ptr->test_dtm_tx_v4.phy, ptr->test_dtm_tx_v4.power_level);
    ptr->result = sc;
    break;
  case TEST_DTM_TX_CW :
    sc = sl_bt_test_dtm_tx_cw(ptr->test_dtm_tx_cw.packet_type, ptr->test_dtm_tx_cw.channel, ptr->test_dtm_tx_cw.phy, ptr->test_dtm_tx_cw.power_level);
    ptr->result = sc;
    break;
  case TEST_DTM_RX :
    sc = sl_bt_test_dtm_rx(ptr->test_dtm_rx.channel, ptr->test_dtm_rx.phy);
    ptr->result = sc;
    break;
  case TEST_DTM_END :
    sc = sl_bt_test_dtm_end();
    ptr->result = sc;
    break;
  case SM_CONFIGURE :
    sc = sl_bt_sm_configure(ptr->sm_configure.flags, ptr->sm_configure.io_capabilities);
    ptr->result = sc;
    break;
  case SM_SET_MINIMUM_KEY_SIZE :
    sc = sl_bt_sm_set_minimum_key_size(ptr->sm_set_minimum_key_size.minimum_key_size);
    ptr->result = sc;
    break;
  case SM_SET_DEBUG_MODE :
    sc = sl_bt_sm_set_debug_mode();
    ptr->result = sc;
    break;
  case SM_ADD_TO_WHITELIST :
    sc = sl_bt_sm_add_to_whitelist(ptr->sm_add_to_whitelist.address, ptr->sm_add_to_whitelist.address_type);
    ptr->result = sc;
    break;
  case SM_STORE_BONDING_CONFIGURATION :
    sc = sl_bt_sm_store_bonding_configuration(ptr->sm_store_bonding_configuration.max_bonding_count, ptr->sm_store_bonding_configuration.policy_flags);
    ptr->result = sc;
    break;
  case SM_SET_BONDABLE_MODE :
    sc = sl_bt_sm_set_bondable_mode(ptr->sm_set_bondable_mode.bondable);
    ptr->result = sc;
    break;
  case SM_SET_PASSKEY :
    sc = sl_bt_sm_set_passkey(ptr->sm_set_passkey.passkey);
    ptr->result = sc;
    break;
  case SM_INCREASE_SECURITY :
    sc = sl_bt_sm_increase_security(ptr->sm_increase_security.connection);
    ptr->result = sc;
    break;
  case SM_ENTER_PASSKEY :
    sc = sl_bt_sm_enter_passkey(ptr->sm_enter_passkey.connection, ptr->sm_enter_passkey.passkey);
    ptr->result = sc;
    break;
  case SM_PASSKEY_CONFIRM :
    sc = sl_bt_sm_passkey_confirm(ptr->sm_passkey_confirm.connection, ptr->sm_passkey_confirm.confirm);
    ptr->result = sc;
    break;
  case SM_BONDING_CONFIRM :
    sc = sl_bt_sm_bonding_confirm(ptr->sm_bonding_confirm.connection, ptr->sm_bonding_confirm.confirm);
    ptr->result = sc;
    break;
  case SM_DELETE_BONDING :
    sc = sl_bt_sm_delete_bonding(ptr->sm_delete_bonding.bonding);
    ptr->result = sc;
    break;
  case SM_DELETE_BONDINGS :
    sc = sl_bt_sm_delete_bondings();
    ptr->result = sc;
    break;
  case SM_GET_BONDING_HANDLES :
    sc = sl_bt_sm_get_bonding_handles(ptr->sm_get_bonding_handles.reserved, &ptr->sm_get_bonding_handles.num_bondings, ptr->sm_get_bonding_handles.bondings_max_len, ptr->sm_get_bonding_handles.bondings_len, ptr->sm_get_bonding_handles.bondings);
    ptr->result = sc;
    break;
  case SM_GET_BONDING_DETAILS :
    sc = sl_bt_sm_get_bonding_details(ptr->sm_get_bonding_details.bonding, &ptr->sm_get_bonding_details.address, &ptr->sm_get_bonding_details.address_type, &ptr->sm_get_bonding_details.security_mode, &ptr->sm_get_bonding_details.key_size);
    ptr->result = sc;
    break;
  case SM_FIND_BONDING_BY_ADDRESS :
    sc = sl_bt_sm_find_bonding_by_address(ptr->sm_find_bonding_by_address.address, &ptr->sm_find_bonding_by_address.bonding, &ptr->sm_find_bonding_by_address.security_mode, &ptr->sm_find_bonding_by_address.key_size);
    ptr->result = sc;
    break;
  case SM_RESOLVE_RPA :
    sc = sl_bt_sm_resolve_rpa(ptr->sm_resolve_rpa.rpa, &ptr->sm_resolve_rpa.address, &ptr->sm_resolve_rpa.address_type, &ptr->sm_resolve_rpa.bonding);
    ptr->result = sc;
    break;
  case SM_SET_BONDING_KEY :
    sc = sl_bt_sm_set_bonding_key(ptr->sm_set_bonding_key.bonding, ptr->sm_set_bonding_key.key_type, ptr->sm_set_bonding_key.key);
    ptr->result = sc;
    break;
  case SM_SET_LEGACY_OOB :
    sc = sl_bt_sm_set_legacy_oob(ptr->sm_set_legacy_oob.enable, ptr->sm_set_legacy_oob.oob_data);
    ptr->result = sc;
    break;
  case SM_SET_OOB :
    sc = sl_bt_sm_set_oob(ptr->sm_set_oob.enable, &ptr->sm_set_oob.random, &ptr->sm_set_oob.confirm);
    ptr->result = sc;
    break;
  case SM_SET_REMOTE_OOB :
    sc = sl_bt_sm_set_remote_oob(ptr->sm_set_remote_oob.enable, ptr->sm_set_remote_oob.random, ptr->sm_set_remote_oob.confirm);
    ptr->result = sc;
    break;
  case SM_SET_BONDING_DATA :
    sc = sl_bt_sm_set_bonding_data(ptr->sm_set_bonding_data.connection, ptr->sm_set_bonding_data.type, ptr->sm_set_bonding_data.data_len, ptr->sm_set_bonding_data.data);
    ptr->result = sc;
    break;
  case OTA_SET_DEVICE_NAME :
    sc = sl_bt_ota_set_device_name(ptr->ota_set_device_name.name_len, ptr->ota_set_device_name.name);
    ptr->result = sc;
    break;
  case OTA_SET_ADVERTISING_DATA :
    sc = sl_bt_ota_set_advertising_data(ptr->ota_set_advertising_data.packet_type, ptr->ota_set_advertising_data.adv_data_len, ptr->ota_set_advertising_data.adv_data);
    ptr->result = sc;
    break;
  case OTA_SET_CONFIGURATION :
    sc = sl_bt_ota_set_configuration(ptr->ota_set_configuration.flags);
    ptr->result = sc;
    break;
  case OTA_SET_RF_PATH :
    sc = sl_bt_ota_set_rf_path(ptr->ota_set_rf_path.enable, ptr->ota_set_rf_path.antenna);
    ptr->result = sc;
    break;
  case COEX_SET_OPTIONS :
    sc = sl_bt_coex_set_options(ptr->coex_set_options.mask, ptr->coex_set_options.options);
    ptr->result = sc;
    break;
  case COEX_SET_PARAMETERS :
    sc = sl_bt_coex_set_parameters(ptr->coex_set_parameters.priority, ptr->coex_set_parameters.request, ptr->coex_set_parameters.pwm_period, ptr->coex_set_parameters.pwm_dutycycle);
    ptr->result = sc;
    break;
  case COEX_SET_DIRECTIONAL_PRIORITY_PULSE :
    sc = sl_bt_coex_set_directional_priority_pulse(ptr->coex_set_directional_priority_pulse.pulse);
    ptr->result = sc;
    break;
  case COEX_GET_PARAMETERS :
    sc = sl_bt_coex_get_parameters(&ptr->coex_get_parameters.priority, &ptr->coex_get_parameters.request, &ptr->coex_get_parameters.pwm_period, &ptr->coex_get_parameters.pwm_dutycycle);
    ptr->result = sc;
    break;
  case COEX_GET_COUNTERS :
    sc = sl_bt_coex_get_counters(ptr->coex_get_counters.reset, ptr->coex_get_counters.counters_max_len, ptr->coex_get_counters.counters_len, ptr->coex_get_counters.counters);
    ptr->result = sc;
    break;
  case SYNC_SET_PARAMETERS :
    sc = sl_bt_sync_set_parameters(ptr->sync_set_parameters.skip, ptr->sync_set_parameters.timeout, ptr->sync_set_parameters.flags);
    ptr->result = sc;
    break;
  case SYNC_OPEN :
    sc = sl_bt_sync_open(ptr->sync_open.address, ptr->sync_open.address_type, ptr->sync_open.adv_sid, &ptr->sync_open.sync);
    ptr->result = sc;
    break;
  case SYNC_SET_REPORTING_MODE :
    sc = sl_bt_sync_set_reporting_mode(ptr->sync_set_reporting_mode.sync, ptr->sync_set_reporting_mode.reporting_mode);
    ptr->result = sc;
    break;
  case SYNC_UPDATE_SYNC_PARAMETERS :
    sc = sl_bt_sync_update_sync_parameters(ptr->sync_update_sync_parameters.sync, ptr->sync_update_sync_parameters.skip, ptr->sync_update_sync_parameters.timeout);
    ptr->result = sc;
    break;
  case SYNC_CLOSE :
    sc = sl_bt_sync_close(ptr->sync_close.sync);
    ptr->result = sc;
    break;
  case L2CAP_OPEN_LE_CHANNEL :
    sc = sl_bt_l2cap_open_le_channel(ptr->l2cap_open_le_channel.connection, ptr->l2cap_open_le_channel.spsm, ptr->l2cap_open_le_channel.max_sdu, ptr->l2cap_open_le_channel.max_pdu, ptr->l2cap_open_le_channel.credit, &ptr->l2cap_open_le_channel.cid);
    ptr->result = sc;
    break;
  case L2CAP_SEND_LE_CHANNEL_OPEN_RESPONSE :
    sc = sl_bt_l2cap_send_le_channel_open_response(ptr->l2cap_send_le_channel_open_response.connection, ptr->l2cap_send_le_channel_open_response.cid, ptr->l2cap_send_le_channel_open_response.max_sdu, ptr->l2cap_send_le_channel_open_response.max_pdu, ptr->l2cap_send_le_channel_open_response.credit, ptr->l2cap_send_le_channel_open_response.errorcode);
    ptr->result = sc;
    break;
  case L2CAP_CHANNEL_SEND_DATA :
    sc = sl_bt_l2cap_channel_send_data(ptr->l2cap_channel_send_data.connection, ptr->l2cap_channel_send_data.cid, ptr->l2cap_channel_send_data.data_len, ptr->l2cap_channel_send_data.data);
    ptr->result = sc;
    break;
  case L2CAP_CHANNEL_SEND_CREDIT :
    sc = sl_bt_l2cap_channel_send_credit(ptr->l2cap_channel_send_credit.connection, ptr->l2cap_channel_send_credit.cid, ptr->l2cap_channel_send_credit.credit);
    ptr->result = sc;
    break;
  case L2CAP_CLOSE_CHANNEL :
    sc = sl_bt_l2cap_close_channel(ptr->l2cap_close_channel.connection, ptr->l2cap_close_channel.cid);
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_SET_DTM_PARAMETERS :
    sc = sl_bt_cte_transmitter_set_dtm_parameters(ptr->cte_transmitter_set_dtm_parameters.cte_length, ptr->cte_transmitter_set_dtm_parameters.cte_type, ptr->cte_transmitter_set_dtm_parameters.switching_pattern_len, ptr->cte_transmitter_set_dtm_parameters.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_CLEAR_DTM_PARAMETERS :
    sc = sl_bt_cte_transmitter_clear_dtm_parameters();
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_ENABLE_CONNECTION_CTE :
    sc = sl_bt_cte_transmitter_enable_connection_cte(ptr->cte_transmitter_enable_connection_cte.connection, ptr->cte_transmitter_enable_connection_cte.cte_types, ptr->cte_transmitter_enable_connection_cte.switching_pattern_len, ptr->cte_transmitter_enable_connection_cte.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_DISABLE_CONNECTION_CTE :
    sc = sl_bt_cte_transmitter_disable_connection_cte(ptr->cte_transmitter_disable_connection_cte.connection);
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_ENABLE_CONNECTIONLESS_CTE :
    sc = sl_bt_cte_transmitter_enable_connectionless_cte(ptr->cte_transmitter_enable_connectionless_cte.handle, ptr->cte_transmitter_enable_connectionless_cte.cte_length, ptr->cte_transmitter_enable_connectionless_cte.cte_type, ptr->cte_transmitter_enable_connectionless_cte.cte_count, ptr->cte_transmitter_enable_connectionless_cte.switching_pattern_len, ptr->cte_transmitter_enable_connectionless_cte.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_DISABLE_CONNECTIONLESS_CTE :
    sc = sl_bt_cte_transmitter_disable_connectionless_cte(ptr->cte_transmitter_disable_connectionless_cte.handle);
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_ENABLE_SILABS_CTE :
    sc = sl_bt_cte_transmitter_enable_silabs_cte(ptr->cte_transmitter_enable_silabs_cte.handle, ptr->cte_transmitter_enable_silabs_cte.cte_length, ptr->cte_transmitter_enable_silabs_cte.cte_type, ptr->cte_transmitter_enable_silabs_cte.cte_count, ptr->cte_transmitter_enable_silabs_cte.switching_pattern_len, ptr->cte_transmitter_enable_silabs_cte.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_TRANSMITTER_DISABLE_SILABS_CTE :
    sc = sl_bt_cte_transmitter_disable_silabs_cte(ptr->cte_transmitter_disable_silabs_cte.handle);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_SET_DTM_PARAMETERS :
    sc = sl_bt_cte_receiver_set_dtm_parameters(ptr->cte_receiver_set_dtm_parameters.cte_length, ptr->cte_receiver_set_dtm_parameters.cte_type, ptr->cte_receiver_set_dtm_parameters.slot_durations, ptr->cte_receiver_set_dtm_parameters.switching_pattern_len, ptr->cte_receiver_set_dtm_parameters.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_CLEAR_DTM_PARAMETERS :
    sc = sl_bt_cte_receiver_clear_dtm_parameters();
    ptr->result = sc;
    break;
  case CTE_RECEIVER_SET_SYNC_CTE_TYPE :
    sc = sl_bt_cte_receiver_set_sync_cte_type(ptr->cte_receiver_set_sync_cte_type.sync_cte_type);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_SET_DEFAULT_SYNC_RECEIVE_PARAMETERS :
    sc = sl_bt_cte_receiver_set_default_sync_receive_parameters(ptr->cte_receiver_set_default_sync_receive_parameters.mode, ptr->cte_receiver_set_default_sync_receive_parameters.skip, ptr->cte_receiver_set_default_sync_receive_parameters.timeout, ptr->cte_receiver_set_default_sync_receive_parameters.sync_cte_type, ptr->cte_receiver_set_default_sync_receive_parameters.reporting_mode);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_SET_SYNC_RECEIVE_PARAMETERS :
    sc = sl_bt_cte_receiver_set_sync_receive_parameters(ptr->cte_receiver_set_sync_receive_parameters.connection, ptr->cte_receiver_set_sync_receive_parameters.mode, ptr->cte_receiver_set_sync_receive_parameters.skip, ptr->cte_receiver_set_sync_receive_parameters.timeout, ptr->cte_receiver_set_sync_receive_parameters.sync_cte_type, ptr->cte_receiver_set_sync_receive_parameters.reporting_mode);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_CONFIGURE :
    sc = sl_bt_cte_receiver_configure(ptr->cte_receiver_configure.flags);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_ENABLE_CONNECTION_CTE :
    sc = sl_bt_cte_receiver_enable_connection_cte(ptr->cte_receiver_enable_connection_cte.connection, ptr->cte_receiver_enable_connection_cte.interval, ptr->cte_receiver_enable_connection_cte.cte_length, ptr->cte_receiver_enable_connection_cte.cte_type, ptr->cte_receiver_enable_connection_cte.slot_durations, ptr->cte_receiver_enable_connection_cte.switching_pattern_len, ptr->cte_receiver_enable_connection_cte.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_DISABLE_CONNECTION_CTE :
    sc = sl_bt_cte_receiver_disable_connection_cte(ptr->cte_receiver_disable_connection_cte.connection);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_ENABLE_CONNECTIONLESS_CTE :
    sc = sl_bt_cte_receiver_enable_connectionless_cte(ptr->cte_receiver_enable_connectionless_cte.sync, ptr->cte_receiver_enable_connectionless_cte.slot_durations, ptr->cte_receiver_enable_connectionless_cte.cte_count, ptr->cte_receiver_enable_connectionless_cte.switching_pattern_len, ptr->cte_receiver_enable_connectionless_cte.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_DISABLE_CONNECTIONLESS_CTE :
    sc = sl_bt_cte_receiver_disable_connectionless_cte(ptr->cte_receiver_disable_connectionless_cte.sync);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_ENABLE_SILABS_CTE :
    sc = sl_bt_cte_receiver_enable_silabs_cte(ptr->cte_receiver_enable_silabs_cte.slot_durations, ptr->cte_receiver_enable_silabs_cte.cte_count, ptr->cte_receiver_enable_silabs_cte.switching_pattern_len, ptr->cte_receiver_enable_silabs_cte.switching_pattern);
    ptr->result = sc;
    break;
  case CTE_RECEIVER_DISABLE_SILABS_CTE :
    sc = sl_bt_cte_receiver_disable_silabs_cte();
    ptr->result = sc;
    break;
  case GATTDB_NEW_SESSION :
    sc = sl_bt_gattdb_new_session(&ptr->gattdb_new_session.session);
    ptr->result = sc;
    break;
  case GATTDB_ADD_SERVICE :
    sc = sl_bt_gattdb_add_service(ptr->gattdb_add_service.session, ptr->gattdb_add_service.type, ptr->gattdb_add_service.property, ptr->gattdb_add_service.uuid_len, ptr->gattdb_add_service.uuid, &ptr->gattdb_add_service.service);
    ptr->result = sc;
    break;
  case GATTDB_REMOVE_SERVICE :
    sc = sl_bt_gattdb_remove_service(ptr->gattdb_remove_service.session, ptr->gattdb_remove_service.service);
    ptr->result = sc;
    break;
  case GATTDB_ADD_INCLUDED_SERVICE :
    sc = sl_bt_gattdb_add_included_service(ptr->gattdb_add_included_service.session, ptr->gattdb_add_included_service.service, ptr->gattdb_add_included_service.included_service, &ptr->gattdb_add_included_service.attribute);
    ptr->result = sc;
    break;
  case GATTDB_REMOVE_INCLUDED_SERVICE :
    sc = sl_bt_gattdb_remove_included_service(ptr->gattdb_remove_included_service.session, ptr->gattdb_remove_included_service.attribute);
    ptr->result = sc;
    break;
  case GATTDB_ADD_UUID16_CHARACTERISTIC :
    sc = sl_bt_gattdb_add_uuid16_characteristic(ptr->gattdb_add_uuid16_characteristic.session, ptr->gattdb_add_uuid16_characteristic.service, ptr->gattdb_add_uuid16_characteristic.property, ptr->gattdb_add_uuid16_characteristic.security, ptr->gattdb_add_uuid16_characteristic.flag, ptr->gattdb_add_uuid16_characteristic.uuid, ptr->gattdb_add_uuid16_characteristic.value_type, ptr->gattdb_add_uuid16_characteristic.maxlen, ptr->gattdb_add_uuid16_characteristic.value_len, ptr->gattdb_add_uuid16_characteristic.value, &ptr->gattdb_add_uuid16_characteristic.characteristic);
    ptr->result = sc;
    break;
  case GATTDB_ADD_UUID128_CHARACTERISTIC :
    sc = sl_bt_gattdb_add_uuid128_characteristic(ptr->gattdb_add_uuid128_characteristic.session, ptr->gattdb_add_uuid128_characteristic.service, ptr->gattdb_add_uuid128_characteristic.property, ptr->gattdb_add_uuid128_characteristic.security, ptr->gattdb_add_uuid128_characteristic.flag, ptr->gattdb_add_uuid128_characteristic.uuid, ptr->gattdb_add_uuid128_characteristic.value_type, ptr->gattdb_add_uuid128_characteristic.maxlen, ptr->gattdb_add_uuid128_characteristic.value_len, ptr->gattdb_add_uuid128_characteristic.value, &ptr->gattdb_add_uuid128_characteristic.characteristic);
    ptr->result = sc;
    break;
  case GATTDB_REMOVE_CHARACTERISTIC :
    sc = sl_bt_gattdb_remove_characteristic(ptr->gattdb_remove_characteristic.session, ptr->gattdb_remove_characteristic.characteristic);
    ptr->result = sc;
    break;
  case GATTDB_ADD_UUID16_DESCRIPTOR :
    sc = sl_bt_gattdb_add_uuid16_descriptor(ptr->gattdb_add_uuid16_descriptor.session, ptr->gattdb_add_uuid16_descriptor.characteristic, ptr->gattdb_add_uuid16_descriptor.property, ptr->gattdb_add_uuid16_descriptor.security, ptr->gattdb_add_uuid16_descriptor.uuid, ptr->gattdb_add_uuid16_descriptor.value_type, ptr->gattdb_add_uuid16_descriptor.maxlen, ptr->gattdb_add_uuid16_descriptor.value_len, ptr->gattdb_add_uuid16_descriptor.value, &ptr->gattdb_add_uuid16_descriptor.descriptor);
    ptr->result = sc;
    break;
  case GATTDB_ADD_UUID128_DESCRIPTOR :
    sc = sl_bt_gattdb_add_uuid128_descriptor(ptr->gattdb_add_uuid128_descriptor.session, ptr->gattdb_add_uuid128_descriptor.characteristic, ptr->gattdb_add_uuid128_descriptor.property, ptr->gattdb_add_uuid128_descriptor.security, ptr->gattdb_add_uuid128_descriptor.uuid, ptr->gattdb_add_uuid128_descriptor.value_type, ptr->gattdb_add_uuid128_descriptor.maxlen, ptr->gattdb_add_uuid128_descriptor.value_len, ptr->gattdb_add_uuid128_descriptor.value, &ptr->gattdb_add_uuid128_descriptor.descriptor);
    ptr->result = sc;
    break;
  case GATTDB_REMOVE_DESCRIPTOR :
    sc = sl_bt_gattdb_remove_descriptor(ptr->gattdb_remove_descriptor.session, ptr->gattdb_remove_descriptor.descriptor);
    ptr->result = sc;
    break;
  case GATTDB_START_SERVICE :
    sc = sl_bt_gattdb_start_service(ptr->gattdb_start_service.session, ptr->gattdb_start_service.service);
    ptr->result = sc;
    break;
  case GATTDB_STOP_SERVICE :
    sc = sl_bt_gattdb_stop_service(ptr->gattdb_stop_service.session, ptr->gattdb_stop_service.service);
    ptr->result = sc;
    break;
  case GATTDB_START_CHARACTERISTIC :
    sc = sl_bt_gattdb_start_characteristic(ptr->gattdb_start_characteristic.session, ptr->gattdb_start_characteristic.characteristic);
    ptr->result = sc;
    break;
  case GATTDB_STOP_CHARACTERISTIC :
    sc = sl_bt_gattdb_stop_characteristic(ptr->gattdb_stop_characteristic.session, ptr->gattdb_stop_characteristic.characteristic);
    ptr->result = sc;
    break;
  case GATTDB_COMMIT :
    sc = sl_bt_gattdb_commit(ptr->gattdb_commit.session);
    ptr->result = sc;
    break;
  case GATTDB_ABORT :
    sc = sl_bt_gattdb_abort(ptr->gattdb_abort.session);
    ptr->result = sc;
    break;
  case CONNECTION_ANALYZER_START :
    sc = sl_bt_connection_analyzer_start(ptr->connection_analyzer_start.access_address, ptr->connection_analyzer_start.crc_init, ptr->connection_analyzer_start.interval, ptr->connection_analyzer_start.supervision_timeout, ptr->connection_analyzer_start.central_clock_accuracy, ptr->connection_analyzer_start.central_phy, ptr->connection_analyzer_start.peripheral_phy, ptr->connection_analyzer_start.channel_selection_algorithm, ptr->connection_analyzer_start.hop, ptr->connection_analyzer_start.channel_map, ptr->connection_analyzer_start.channel, ptr->connection_analyzer_start.event_counter, ptr->connection_analyzer_start.start_time_us, ptr->connection_analyzer_start.flags, &ptr->connection_analyzer_start.analyzer);
    ptr->result = sc;
    break;
  case CONNECTION_ANALYZER_STOP :
    sc = sl_bt_connection_analyzer_stop(ptr->connection_analyzer_stop.analyzer);
    ptr->result = sc;
    break;
  case SYNC_SCANNER_SET_SYNC_PARAMETERS :
    sc = sl_bt_sync_scanner_set_sync_parameters(ptr->sync_scanner_set_sync_parameters.skip, ptr->sync_scanner_set_sync_parameters.timeout, ptr->sync_scanner_set_sync_parameters.reporting_mode);
    ptr->result = sc;
    break;
  case SYNC_SCANNER_OPEN :
    sc = sl_bt_sync_scanner_open(ptr->sync_scanner_open.address, ptr->sync_scanner_open.address_type, ptr->sync_scanner_open.adv_sid, &ptr->sync_scanner_open.sync);
    ptr->result = sc;
    break;
  case PAST_RECEIVER_SET_DEFAULT_SYNC_RECEIVE_PARAMETERS :
    sc = sl_bt_past_receiver_set_default_sync_receive_parameters(ptr->past_receiver_set_default_sync_receive_parameters.mode, ptr->past_receiver_set_default_sync_receive_parameters.skip, ptr->past_receiver_set_default_sync_receive_parameters.timeout, ptr->past_receiver_set_default_sync_receive_parameters.reporting_mode);
    ptr->result = sc;
    break;
  case PAST_RECEIVER_SET_SYNC_RECEIVE_PARAMETERS :
    sc = sl_bt_past_receiver_set_sync_receive_parameters(ptr->past_receiver_set_sync_receive_parameters.connection, ptr->past_receiver_set_sync_receive_parameters.mode, ptr->past_receiver_set_sync_receive_parameters.skip, ptr->past_receiver_set_sync_receive_parameters.timeout, ptr->past_receiver_set_sync_receive_parameters.reporting_mode);
    ptr->result = sc;
    break;
  case ADVERTISER_PAST_TRANSFER :
    sc = sl_bt_advertiser_past_transfer(ptr->advertiser_past_transfer.connection, ptr->advertiser_past_transfer.service_data, ptr->advertiser_past_transfer.advertising_set);
    ptr->result = sc;
    break;
  case PAWR_SYNC_SET_SYNC_SUBEVENTS :
    sc = sl_bt_pawr_sync_set_sync_subevents(ptr->pawr_sync_set_sync_subevents.sync, ptr->pawr_sync_set_sync_subevents.subevents_len, ptr->pawr_sync_set_sync_subevents.subevents);
    ptr->result = sc;
    break;
  case PAWR_SYNC_SET_RESPONSE_DATA :
    sc = sl_bt_pawr_sync_set_response_data(ptr->pawr_sync_set_response_data.sync, ptr->pawr_sync_set_response_data.request_event, ptr->pawr_sync_set_response_data.request_subevent, ptr->pawr_sync_set_response_data.response_subevent, ptr->pawr_sync_set_response_data.response_slot, ptr->pawr_sync_set_response_data.response_data_len, ptr->pawr_sync_set_response_data.response_data);
    ptr->result = sc;
    break;
  case PAWR_ADVERTISER_START :
    sc = sl_bt_pawr_advertiser_start(ptr->pawr_advertiser_start.advertising_set, ptr->pawr_advertiser_start.interval_min, ptr->pawr_advertiser_start.interval_max, ptr->pawr_advertiser_start.flags, ptr->pawr_advertiser_start.num_subevents, ptr->pawr_advertiser_start.subevent_interval, ptr->pawr_advertiser_start.response_slot_delay, ptr->pawr_advertiser_start.response_slot_spacing, ptr->pawr_advertiser_start.response_slots);
    ptr->result = sc;
    break;
  case PAWR_ADVERTISER_SET_SUBEVENT_DATA :
    sc = sl_bt_pawr_advertiser_set_subevent_data(ptr->pawr_advertiser_set_subevent_data.advertising_set, ptr->pawr_advertiser_set_subevent_data.subevent, ptr->pawr_advertiser_set_subevent_data.response_slot_start, ptr->pawr_advertiser_set_subevent_data.response_slot_count, ptr->pawr_advertiser_set_subevent_data.adv_data_len, ptr->pawr_advertiser_set_subevent_data.adv_data);
    ptr->result = sc;
    break;
  case PAWR_ADVERTISER_CREATE_CONNECTION :
    sc = sl_bt_pawr_advertiser_create_connection(ptr->pawr_advertiser_create_connection.advertising_set, ptr->pawr_advertiser_create_connection.subevent, ptr->pawr_advertiser_create_connection.address, ptr->pawr_advertiser_create_connection.address_type, &ptr->pawr_advertiser_create_connection.connection);
    ptr->result = sc;
    break;
  case PAWR_ADVERTISER_STOP :
    sc = sl_bt_pawr_advertiser_stop(ptr->pawr_advertiser_stop.advertising_set);
    ptr->result = sc;
    break;
  case LEGACY_ADVERTISER_SET_DATA :
    sc = sl_bt_legacy_advertiser_set_data(ptr->legacy_advertiser_set_data.advertising_set, ptr->legacy_advertiser_set_data.type, ptr->legacy_advertiser_set_data.data_len, ptr->legacy_advertiser_set_data.data);
    ptr->result = sc;
    break;
  case LEGACY_ADVERTISER_GENERATE_DATA :
    sc = sl_bt_legacy_advertiser_generate_data(ptr->legacy_advertiser_generate_data.advertising_set, ptr->legacy_advertiser_generate_data.discover);
    ptr->result = sc;
    break;
  case LEGACY_ADVERTISER_START :
    sc = sl_bt_legacy_advertiser_start(ptr->legacy_advertiser_start.advertising_set, ptr->legacy_advertiser_start.connect);
    ptr->result = sc;
    break;
  case LEGACY_ADVERTISER_START_DIRECTED :
    sc = sl_bt_legacy_advertiser_start_directed(ptr->legacy_advertiser_start_directed.advertising_set, ptr->legacy_advertiser_start_directed.connect, ptr->legacy_advertiser_start_directed.peer_addr, ptr->legacy_advertiser_start_directed.peer_addr_type);
    ptr->result = sc;
    break;
  case EXTENDED_ADVERTISER_SET_PHY :
    sc = sl_bt_extended_advertiser_set_phy(ptr->extended_advertiser_set_phy.advertising_set, ptr->extended_advertiser_set_phy.primary_phy, ptr->extended_advertiser_set_phy.secondary_phy);
    ptr->result = sc;
    break;
  case EXTENDED_ADVERTISER_SET_DATA :
    sc = sl_bt_extended_advertiser_set_data(ptr->extended_advertiser_set_data.advertising_set, ptr->extended_advertiser_set_data.data_len, ptr->extended_advertiser_set_data.data);
    ptr->result = sc;
    break;
  case EXTENDED_ADVERTISER_SET_LONG_DATA :
    sc = sl_bt_extended_advertiser_set_long_data(ptr->extended_advertiser_set_long_data.advertising_set);
    ptr->result = sc;
    break;
  case EXTENDED_ADVERTISER_GENERATE_DATA :
    sc = sl_bt_extended_advertiser_generate_data(ptr->extended_advertiser_generate_data.advertising_set, ptr->extended_advertiser_generate_data.discover);
    ptr->result = sc;
    break;
  case EXTENDED_ADVERTISER_START :
    sc = sl_bt_extended_advertiser_start(ptr->extended_advertiser_start.advertising_set, ptr->extended_advertiser_start.connect, ptr->extended_advertiser_start.flags);
    ptr->result = sc;
    break;
  case EXTENDED_ADVERTISER_START_DIRECTED :
    sc = sl_bt_extended_advertiser_start_directed(ptr->extended_advertiser_start_directed.advertising_set, ptr->extended_advertiser_start_directed.connect, ptr->extended_advertiser_start_directed.flags, ptr->extended_advertiser_start_directed.peer_addr, ptr->extended_advertiser_start_directed.peer_addr_type);
    ptr->result = sc;
    break;
  case PERIODIC_ADVERTISER_SET_DATA :
    sc = sl_bt_periodic_advertiser_set_data(ptr->periodic_advertiser_set_data.advertising_set, ptr->periodic_advertiser_set_data.data_len, ptr->periodic_advertiser_set_data.data);
    ptr->result = sc;
    break;
  case PERIODIC_ADVERTISER_SET_LONG_DATA :
    sc = sl_bt_periodic_advertiser_set_long_data(ptr->periodic_advertiser_set_long_data.advertising_set);
    ptr->result = sc;
    break;
  case PERIODIC_ADVERTISER_START :
    sc = sl_bt_periodic_advertiser_start(ptr->periodic_advertiser_start.advertising_set, ptr->periodic_advertiser_start.interval_min, ptr->periodic_advertiser_start.interval_max, ptr->periodic_advertiser_start.flags);
    ptr->result = sc;
    break;
  case PERIODIC_ADVERTISER_STOP :
    sc = sl_bt_periodic_advertiser_stop(ptr->periodic_advertiser_stop.advertising_set);
    ptr->result = sc;
    break;
  case CS_SECURITY_ENABLE :
    sc = sl_bt_cs_security_enable(ptr->cs_security_enable.connection);
    ptr->result = sc;
    break;
  case CS_SET_DEFAULT_SETTINGS :
    sc = sl_bt_cs_set_default_settings(ptr->cs_set_default_settings.connection, ptr->cs_set_default_settings.initiator_status, ptr->cs_set_default_settings.reflector_status, ptr->cs_set_default_settings.antenna_identifier, ptr->cs_set_default_settings.max_tx_power);
    ptr->result = sc;
    break;
  case CS_CREATE_CONFIG :
    sc = sl_bt_cs_create_config(ptr->cs_create_config.connection, ptr->cs_create_config.config_id, ptr->cs_create_config.create_context, ptr->cs_create_config.main_mode_type, ptr->cs_create_config.sub_mode_type, ptr->cs_create_config.min_main_mode_steps, ptr->cs_create_config.max_main_mode_steps, ptr->cs_create_config.main_mode_repetition, ptr->cs_create_config.mode_calibration_steps, ptr->cs_create_config.role, ptr->cs_create_config.rtt_type, ptr->cs_create_config.cs_sync_phy, ptr->cs_create_config.channel_map, ptr->cs_create_config.channel_map_repetition, ptr->cs_create_config.channel_selection_type, ptr->cs_create_config.ch3c_shape, ptr->cs_create_config.ch3c_jump, ptr->cs_create_config.companion_signal_state);
    ptr->result = sc;
    break;
  case CS_REMOVE_CONFIG :
    sc = sl_bt_cs_remove_config(ptr->cs_remove_config.connection, ptr->cs_remove_config.config_id);
    ptr->result = sc;
    break;
  case CS_SET_CHANNEL_CLASSIFICATION :
    sc = sl_bt_cs_set_channel_classification(ptr->cs_set_channel_classification.channel_map);
    ptr->result = sc;
    break;
  case CS_SET_PROCEDURE_PARAMETERS :
    sc = sl_bt_cs_set_procedure_parameters(ptr->cs_set_procedure_parameters.connection, ptr->cs_set_procedure_parameters.config_id, ptr->cs_set_procedure_parameters.max_procedure_len, ptr->cs_set_procedure_parameters.min_procedure_interval, ptr->cs_set_procedure_parameters.max_procedure_interval, ptr->cs_set_procedure_parameters.max_procedure_count, ptr->cs_set_procedure_parameters.min_subevent_len, ptr->cs_set_procedure_parameters.max_subevent_len, ptr->cs_set_procedure_parameters.tone_antenna_config_selection, ptr->cs_set_procedure_parameters.phy, ptr->cs_set_procedure_parameters.tx_pwr_delta, ptr->cs_set_procedure_parameters.preferred_peer_antenna);
    ptr->result = sc;
    break;
  case CS_PROCEDURE_ENABLE :
    sc = sl_bt_cs_procedure_enable(ptr->cs_procedure_enable.connection, ptr->cs_procedure_enable.enable, ptr->cs_procedure_enable.config_id);
    ptr->result = sc;
    break;
  case CS_SET_ANTENNA_CONFIGURATION :
    sc = sl_bt_cs_set_antenna_configuration(ptr->cs_set_antenna_configuration.antenna_element_offset_len, ptr->cs_set_antenna_configuration.antenna_element_offset);
    ptr->result = sc;
    break;
  case CS_READ_LOCAL_SUPPORTED_CAPABILITIES :
    sc = sl_bt_cs_read_local_supported_capabilities(&ptr->cs_read_local_supported_capabilities.num_config, &ptr->cs_read_local_supported_capabilities.max_consecutive_procedures, &ptr->cs_read_local_supported_capabilities.num_antennas, &ptr->cs_read_local_supported_capabilities.max_antenna_paths, &ptr->cs_read_local_supported_capabilities.roles, &ptr->cs_read_local_supported_capabilities.optional_modes, &ptr->cs_read_local_supported_capabilities.rtt_capability, &ptr->cs_read_local_supported_capabilities.rtt_aa_only, &ptr->cs_read_local_supported_capabilities.rtt_sounding, &ptr->cs_read_local_supported_capabilities.rtt_random_payload, &ptr->cs_read_local_supported_capabilities.optional_cs_sync_phys, &ptr->cs_read_local_supported_capabilities.optional_subfeatures, &ptr->cs_read_local_supported_capabilities.optional_t_ip1_times, &ptr->cs_read_local_supported_capabilities.optional_t_ip2_times, &ptr->cs_read_local_supported_capabilities.optional_t_fcs_times, &ptr->cs_read_local_supported_capabilities.optional_t_pm_times, &ptr->cs_read_local_supported_capabilities.t_sw_times);
    ptr->result = sc;
    break;
  case CS_TEST_START :
    sc = sl_bt_cs_test_start(ptr->cs_test_start.main_mode_type, ptr->cs_test_start.sub_mode_type, ptr->cs_test_start.main_mode_repetition, ptr->cs_test_start.mode_calibration_steps, ptr->cs_test_start.role, ptr->cs_test_start.rtt_type, ptr->cs_test_start.cs_sync_phy, ptr->cs_test_start.antenna_selection, ptr->cs_test_start.subevent_len, ptr->cs_test_start.subevent_interval, ptr->cs_test_start.tx_power, ptr->cs_test_start.t_ip1_time, ptr->cs_test_start.t_ip2_time, ptr->cs_test_start.t_fcs_time, ptr->cs_test_start.t_pm_time, ptr->cs_test_start.t_sw_time, ptr->cs_test_start.tone_antenna_config, ptr->cs_test_start.companion_signal_state, ptr->cs_test_start.drbg_nonce, ptr->cs_test_start.override_config, ptr->cs_test_start.override_parameters_len, ptr->cs_test_start.override_parameters);
    ptr->result = sc;
    break;
  case SYNC_PAST_TRANSFER :
    sc = sl_bt_sync_past_transfer(ptr->sync_past_transfer.connection, ptr->sync_past_transfer.service_data, ptr->sync_past_transfer.sync);
    ptr->result = sc;
    break;
  case EXTERNAL_BONDINGDB_SET_DATA :
    sc = sl_bt_external_bondingdb_set_data(ptr->external_bondingdb_set_data.connection, ptr->external_bondingdb_set_data.type, ptr->external_bondingdb_set_data.data_len, ptr->external_bondingdb_set_data.data);
    ptr->result = sc;
    break;
  case RESOLVING_LIST_ADD_DEVICE_BY_BONDING :
    sc = sl_bt_resolving_list_add_device_by_bonding(ptr->resolving_list_add_device_by_bonding.bonding, ptr->resolving_list_add_device_by_bonding.privacy_mode);
    ptr->result = sc;
    break;
  case RESOLVING_LIST_ADD_DEVICE_BY_ADDRESS :
    sc = sl_bt_resolving_list_add_device_by_address(ptr->resolving_list_add_device_by_address.address, ptr->resolving_list_add_device_by_address.address_type, ptr->resolving_list_add_device_by_address.key, ptr->resolving_list_add_device_by_address.privacy_mode);
    ptr->result = sc;
    break;
  case RESOLVING_LIST_REMOVE_DEVICE_BY_BONDING :
    sc = sl_bt_resolving_list_remove_device_by_bonding(ptr->resolving_list_remove_device_by_bonding.bonding);
    ptr->result = sc;
    break;
  case RESOLVING_LIST_REMOVE_DEVICE_BY_ADDRESS :
    sc = sl_bt_resolving_list_remove_device_by_address(ptr->resolving_list_remove_device_by_address.address, ptr->resolving_list_remove_device_by_address.address_type);
    ptr->result = sc;
    break;
  case RESOLVING_LIST_REMOVE_ALL_DEVICES :
    sc = sl_bt_resolving_list_remove_all_devices();
    ptr->result = sc;
    break;
  case ACCEPT_LIST_ADD_DEVICE_BY_BONDING :
    sc = sl_bt_accept_list_add_device_by_bonding(ptr->accept_list_add_device_by_bonding.bonding);
    ptr->result = sc;
    break;
  case ACCEPT_LIST_ADD_DEVICE_BY_ADDRESS :
    sc = sl_bt_accept_list_add_device_by_address(ptr->accept_list_add_device_by_address.address, ptr->accept_list_add_device_by_address.address_type);
    ptr->result = sc;
    break;
  case ACCEPT_LIST_REMOVE_DEVICE_BY_BONDING :
    sc = sl_bt_accept_list_remove_device_by_bonding(ptr->accept_list_remove_device_by_bonding.bonding);
    ptr->result = sc;
    break;
  case ACCEPT_LIST_REMOVE_DEVICE_BY_ADDRESS :
    sc = sl_bt_accept_list_remove_device_by_address(ptr->accept_list_remove_device_by_address.address, ptr->accept_list_remove_device_by_address.address_type);
    ptr->result = sc;
    break;
  case ACCEPT_LIST_REMOVE_ALL_DEVICES :
    sc = sl_bt_accept_list_remove_all_devices();
    ptr->result = sc;
    break;
  case RESOURCE_GET_STATUS :
    sc = sl_bt_resource_get_status(&ptr->resource_get_status.total_bytes, &ptr->resource_get_status.free_bytes);
    ptr->result = sc;
    break;
  case RESOURCE_SET_REPORT_THRESHOLD :
    sc = sl_bt_resource_set_report_threshold(ptr->resource_set_report_threshold.low, ptr->resource_set_report_threshold.high);
    ptr->result = sc;
    break;
  case RESOURCE_ENABLE_CONNECTION_TX_REPORT :
    sc = sl_bt_resource_enable_connection_tx_report(ptr->resource_enable_connection_tx_report.packet_count);
    ptr->result = sc;
    break;
  case RESOURCE_GET_CONNECTION_TX_STATUS :
    sc = sl_bt_resource_get_connection_tx_status(ptr->resource_get_connection_tx_status.connection, &ptr->resource_get_connection_tx_status.flags, &ptr->resource_get_connection_tx_status.packet_count, &ptr->resource_get_connection_tx_status.data_len);
    ptr->result = sc;
    break;
  case RESOURCE_DISABLE_CONNECTION_TX_REPORT :
    sc = sl_bt_resource_disable_connection_tx_report();
    ptr->result = sc;
    break;
  case USER_MESSAGE_TO_TARGET :
    sc = sl_bt_user_message_to_target(ptr->user_message_to_target.data_len, ptr->user_message_to_target.data, ptr->user_message_to_target.response_max_len, ptr->user_message_to_target.response_len, ptr->user_message_to_target.response);
    ptr->result = sc;
    break;
  case USER_MANAGE_EVENT_FILTER :
    sc = sl_bt_user_manage_event_filter(ptr->user_manage_event_filter.data_len, ptr->user_manage_event_filter.data);
    ptr->result = sc;
    break;
  case USER_RESET_TO_DFU :
    sl_bt_user_reset_to_dfu();
    break;
  }
}
