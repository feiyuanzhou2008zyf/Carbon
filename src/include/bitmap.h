#ifndef BITMAP_H
#define BITMAP_H
#include "stddef.h"
#include "common.h"
typedef struct bitmap {
	uint32_t address;
	uint32_t size;
} __attribute__((packed)) bitmap_t;
void create_bitmap(bitmap_t *bit,uint32_t map_address,uint32_t size);
void set_bitmap(bitmap_t *bit,uint32_t index,uint8_t value);
uint8_t query_bitmap(bitmap_t *bit,uint32_t index);
#endif // BITMAP_H