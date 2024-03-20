#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*
 * Maximum packet size, for legacy this would be 31 by spec,
 * 190 here is an arbitary limit due use of simple API
 * Actual limit imposed by full API is 1650
 */ 
#define AD_DATA_MAX_SIZE (190)

struct ad_data_s {
  uint8_t *data;
  uint8_t len;
  size_t allocated;
};

struct ad_data_s *ad_data_create(size_t size);
void ad_data_destroy(struct ad_data_s *ad_data);
size_t ad_data_available(struct ad_data_s *ad_data);
void ad_data_clear(struct ad_data_s *ad_data);
bool ad_data_add_flags(struct ad_data_s *ad_data, uint8_t flags);
bool ad_data_add_complete_name(struct ad_data_s *ad_data, const char *name);
bool ad_data_add_eddystone(struct ad_data_s *ad_data, uint8_t *frame, uint8_t len);
bool ad_data_add_eddystone_uid(struct ad_data_s *ad_data, uint8_t ranging_data, const char *nid, uint8_t bid[6]);
bool ad_data_add_incomplete_16bit_services(struct ad_data_s *ad_data, uint16_t *services, uint8_t count);
bool ad_data_add_incomplete_128bit_services(struct ad_data_s *ad_data, uint8_t services[][16], size_t count);
bool ad_data_add_manufacturer(struct ad_data_s *ad_data, uint16_t uuid, size_t len, uint8_t *data);
