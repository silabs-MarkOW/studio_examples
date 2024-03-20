#ifndef __ADVERTISER_H__
#define __ADVERTISER_H__

#include <stddef.h>

void initialize_advertisers();
void update_extended_private_address(void);
void start_legacy_advertisement(void);
void update_periodic_advertisement(size_t len, uint8_t *data);

#endif
