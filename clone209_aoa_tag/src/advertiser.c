#include <assert.h>
#include "gatt_db.h"
#include "app_assert.h"
#include "sl_bt_api.h"
#include "ad_data.h"

#define PERIODIC_PAYLOAD_MAX_SIZE 64

static uint8_t adv_cte_min_len = 20;
static uint8_t adv_cte_min_tx_count = 1;

static const uint16_t legacy_interval_ms = 1000;
static const uint16_t extended_interval_ms = 250;
static const uint16_t periodic_interval_ms = 50;

static uint8_t legacy_set; // advertising set for legacy advertisements
static uint8_t extended_set; // advertising set for extended and periodic with CTE

static bd_addr legacy_static_random_address;

const char *namespace = "NINA-B4TAG";

static struct ad_data_s *ad_data_periodic;

void get_random_address(bd_addr *address) {
  sl_status_t sc;
  size_t bytes_read;
  // fill address with random data
  sc = sl_bt_system_get_random_data(6, // length requested
				    6, // size of buffer
				    &bytes_read,
				    &address->addr[0]);
  app_assert_status(sc);
  assert(6 == bytes_read);
}

void initialize_static_random_address (bd_addr *address) {
  get_random_address(address);
  // Core 5.4,Vol 6, Part B, Section 1.3.2 indicates static random address
  // must have two most significant bit set
  address->addr[5] |= 0xc0;
}

void initialize_nonresolvable_random_address(bd_addr *address) {
  get_random_address(address);
  // Core 5.4,Vol 6, Part B, Section 1.3.2 indicates non-resolvable private
  // random address  must have two most significant bit clear
  address->addr[5] &= 0x3f; 
}

void stop_extended_and_periodic_advertisement(void) {
  sl_status_t sc;
  sc = sl_bt_cte_transmitter_disable_connectionless_cte(extended_set);
  app_assert_status(sc);

  sc = sl_bt_periodic_advertiser_stop(extended_set);
  app_assert_status(sc);

  sc = sl_bt_advertiser_stop(extended_set);
  app_assert_status(sc);
}

void start_extended_and_periodic_advertisement(void) {
  sl_status_t sc;
  uint8_t switching_pattern[] = { 0 };
  // Start advertising and disable connections
  sc = sl_bt_extended_advertiser_start(extended_set,
				       sl_bt_extended_advertiser_non_connectable,
				       SL_BT_EXTENDED_ADVERTISER_INCLUDE_TX_POWER);
  app_assert_status(sc);

  // Add periodic advertisement to extended set
  // extended advertisement will include coordinates of periodic data
  // periodic data will be follwoed by CTE data
  uint16_t interval = ((uint32_t)periodic_interval_ms << 2) / 5;
  sc = sl_bt_periodic_advertiser_start(extended_set,
				       interval,
				       interval,
				       SL_BT_PERIODIC_ADVERTISER_INCLUDE_TX_POWER);
  app_assert_status(sc);

  // Add CTE to periodic advertisements
  sc = sl_bt_cte_transmitter_enable_connectionless_cte(extended_set,
						       adv_cte_min_len,
						       0, // AoA CTE
						       adv_cte_min_tx_count,
						       sizeof(switching_pattern),
						       switching_pattern);
  app_assert_status(sc);
}
  
/* update_extended_private_address() will be called periodically from 
 * app.c:sl_bt_on_event() due to event generated by sleeptimer after
 * advertisement is active
 */ 
void update_extended_private_address(void) {
  sl_status_t sc;
  bd_addr address;
  bd_addr dummy; // API requires location to store actual address used

  initialize_nonresolvable_random_address(&address);
  stop_extended_and_periodic_advertisement();
  sc = sl_bt_advertiser_set_random_address(extended_set,
					   sl_bt_gap_random_nonresolvable_address,
					   address,
					   &dummy);
  app_assert_status(sc);
  start_extended_and_periodic_advertisement();
}

void start_legacy_advertisement(void) {
  sl_status_t sc;
  sc = sl_bt_legacy_advertiser_start(legacy_set,
                                     sl_bt_legacy_advertiser_connectable);
  app_assert_status(sc);
}

void initialize_legacy_advertiser(const char *device_name) {
  sl_status_t sc;
  bd_addr dummy; // API requires location to store actual address used
  uint8_t services_128bit[][16] = { { 0x6e, 0x40, 0x00, 0x01, 0xb5, 0xa3, 0xf3, 0x93,
				      0xe0, 0xa9, 0xe5, 0x0e, 0x24, 0xdc, 0xca, 0x9e } };
  // allocate set for legacy advertising
  sc = sl_bt_advertiser_create_set(&legacy_set);
  app_assert_status(sc);

  // set static random address
  sc = sl_bt_advertiser_set_random_address(legacy_set,
					   sl_bt_gap_static_address,
					   legacy_static_random_address,
					   &dummy); // for resolvable, this would return address used
  app_assert_status(sc);

  struct ad_data_s *adv = ad_data_create(31); // main/broadcast advertisement
  ad_data_add_flags(adv,6);
  assert(ad_data_add_incomplete_128bit_services(adv,services_128bit,1));
  sc = sl_bt_legacy_advertiser_set_data(legacy_set,0,adv->len,adv->data);
  ad_data_destroy(adv);
  
  struct ad_data_s *scan_resp = ad_data_create(31); // scan response
  assert(ad_data_add_complete_name(scan_resp,device_name));
  sc = sl_bt_legacy_advertiser_set_data(legacy_set,1,scan_resp->len,scan_resp->data);
  ad_data_destroy(scan_resp);

  // set legacy advertising timing
  uint16_t interval = ((uint32_t)legacy_interval_ms << 2) / 5;
  sc = sl_bt_advertiser_set_timing(legacy_set, interval, interval, 0, 0);
  app_assert_status(sc);

  start_legacy_advertisement();
}

void initialize_extended_advertiser(const char *device_name) {
  sl_status_t sc;
  uint16_t services_16bit[] = { 0xFEAA };
  bd_addr address;
  uint8_t address_type;
  bd_addr dummy; // API requires location to store actual address used

  // get device address to use as Eddystone-UID BID
  sc = sl_bt_system_get_identity_address(&address, &address_type);
  app_assert_status(sc);
  (void)address_type;

  // allocate set for extended advertising
  sc = sl_bt_advertiser_create_set(&extended_set);
  app_assert_status(sc);

  struct ad_data_s *ext = ad_data_create(80); // extended advertisement
  ad_data_add_flags(ext,4);
  assert(ad_data_add_incomplete_16bit_services(ext,services_16bit,1));
  assert(ad_data_add_eddystone_uid(ext,4,namespace,(void*)&address.addr));
  assert(ad_data_add_complete_name(ext,device_name));
  sc = sl_bt_extended_advertiser_set_data(extended_set,ext->len,ext->data);
  app_assert_status(sc);
  ad_data_destroy(ext);

  // set extended advertising timing
  uint16_t interval = ((uint32_t)extended_interval_ms << 2) / 5;
  sc = sl_bt_advertiser_set_timing(extended_set, interval, interval, 0, 0);
  app_assert_status(sc);

  // set phy used for primary and secondary packets
  sc = sl_bt_extended_advertiser_set_phy(extended_set,
					 sl_bt_gap_phy_1m,
					 sl_bt_gap_phy_2m);
  app_assert_status(sc);

  // generate a nonresolvable random address
  initialize_nonresolvable_random_address(&address);

  sc = sl_bt_advertiser_set_random_address(extended_set,
					   sl_bt_gap_random_nonresolvable_address,
					   address,
					   &dummy);
  app_assert_status(sc);

  start_extended_and_periodic_advertisement();

  // allocate this once and use many in update_periodic_advertisement
  ad_data_periodic = ad_data_create(PERIODIC_PAYLOAD_MAX_SIZE);
}

void initialize_advertisers() {
  sl_status_t sc;
  size_t len;
  uint8_t device_name[64];

  // c209 uses a static random address for connectable legacy advertisement
  // Bluetooth Spec indicates this may change at device reset, but should
  // not change during operation.
  initialize_static_random_address(&legacy_static_random_address);
  
  // Read device name from GATT database
  sc = sl_bt_gatt_server_read_attribute_value(gattdb_device_name,
					      0, // offset
					      sizeof(device_name),
					      &len,
					      device_name);
  app_assert_status(sc);
  device_name[len] = 0;
  //initialize_legacy_advertiser((const char *)device_name);
  initialize_extended_advertiser((const char *)device_name);
}

void update_periodic_advertisement(size_t len, uint8_t *data) {
  sl_status_t sc;
  ad_data_clear(ad_data_periodic);
  ad_data_add_manufacturer(ad_data_periodic, 0x0710, len, data);
  sc = sl_bt_periodic_advertiser_set_data(extended_set, ad_data_periodic->len, ad_data_periodic->data);
  app_assert_status(sc);
}