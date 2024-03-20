#include "ad_data.h"
#include <string.h>
#include <stdlib.h>

struct ad_data_s *ad_data_create(size_t size) {
  if(size > AD_DATA_MAX_SIZE) return NULL;
  struct ad_data_s *s = malloc(sizeof(struct ad_data_s));
  if(NULL == s) return NULL;
  s->data = malloc(size);
  if(NULL == s->data) {
    free(s);
    return NULL;
  }
  s->allocated = size;
  s->len = 0;
  return s;
}

void ad_data_destroy(struct ad_data_s *ad_data) {
  free(ad_data->data);
  free(ad_data);
}

size_t ad_data_available(struct ad_data_s *ad_data) {
  return ad_data->allocated - ad_data->len;
}

bool ad_data_add_flags(struct ad_data_s *ad_data, uint8_t flags) {
  if(ad_data_available(ad_data) < 3) return false;
  ad_data->data[ad_data->len++] = 2;
  ad_data->data[ad_data->len++] = 1;
  ad_data->data[ad_data->len++] = flags;
  return true;
}

void ad_data_clear(struct ad_data_s *ad_data) {
  ad_data->len = 0;
}

bool ad_data_add_complete_name(struct ad_data_s *ad_data, const char *name) {
  uint8_t len = strlen(name);
  if(ad_data_available(ad_data) < (2+len)) return false;
  ad_data->data[ad_data->len++] = 1+len;
  ad_data->data[ad_data->len++] = 0x09;
  memcpy(&ad_data->data[ad_data->len],name,len);
  ad_data->len += len;
  return true;
}

bool ad_data_add_eddystone(struct ad_data_s *ad_data, uint8_t *frame, uint8_t len) {
  if(ad_data_available(ad_data) < (4+len)) return false;
  uint16_t uuid = 0xfeaa;
  ad_data->data[ad_data->len++] = 3+len;
  ad_data->data[ad_data->len++] = 0x16;
  memcpy(&ad_data->data[ad_data->len],&uuid,2);
  ad_data->len += 2;
  memcpy(&ad_data->data[ad_data->len],frame,len);
  ad_data->len += len;
  return true;
}

bool ad_data_add_eddystone_uid(struct ad_data_s *ad_data, uint8_t ranging_data, const char *nid, uint8_t bid[6]) {
  struct __attribute__((packed)) {
    uint8_t frame_type;
    uint8_t ranging_data;
    uint8_t nid[10];
    uint8_t bid[6];
    uint16_t rfu;
  } frame = { .frame_type = 0x00, .ranging_data = ranging_data, .rfu = 0 };
  if(10 != strlen(nid)) return false;
  if(20 != sizeof(frame)) return false;
  memcpy(&frame.nid,nid,10);
  for(size_t i = 0; i < 6; i++) { // reverse BID because Eddystone is Big Endian
    frame.bid[5-i] = bid[i];
  }
  memcpy(&frame.bid,bid,6);
  return ad_data_add_eddystone(ad_data, (uint8_t*)&frame, sizeof(frame));
}

bool ad_data_add_incomplete_16bit_services(struct ad_data_s *ad_data, uint16_t *services, uint8_t count) {
  uint8_t len = count << 1;
  if(ad_data_available(ad_data) < (2+len)) return false;
  ad_data->data[ad_data->len++] = 1+len;
  ad_data->data[ad_data->len++] = 0x03;
  memcpy(&ad_data->data[ad_data->len],services,len);
  ad_data->len += len;
  return true;
}

bool ad_data_add_incomplete_128bit_services(struct ad_data_s *ad_data, uint8_t services[][16], size_t count) {
  size_t len = count << 4;
  printf("len: %d, allocated:%d, len: %d\n",len,ad_data->allocated,ad_data->len);
  if(ad_data_available(ad_data) < (2+len)) return false;
  ad_data->data[ad_data->len++] = 1+len;
  ad_data->data[ad_data->len++] = 0x07;
  memcpy(&ad_data->data[ad_data->len],services,len);
  ad_data->len += len;
  return true;
}

bool ad_data_add_manufacturer(struct ad_data_s *ad_data,
			      uint16_t uuid,
			      size_t len,
			      uint8_t *data) {
  if(ad_data_available(ad_data) < (4+len)) return false;
  ad_data->data[ad_data->len++] = 3+len;
  ad_data->data[ad_data->len++] = 0xff;
  memcpy(&ad_data->data[ad_data->len],&uuid,2);
  ad_data->len += 2;
  memcpy(&ad_data->data[ad_data->len],data,len);
  ad_data->len += len;
  return true;
}
