#ifndef POOL_H
#define POOL_H
#include "bitmap.h"
#include "debug.h"
#include "stdio.h"
#include "stddef.h"
#define PHYSIC 1
#define VIRTUAL 2
#define USING 0
#define FREE 1
typedef struct memory_pool {
	bitmap_t bitmap;
	uint32_t memory_begin_address;
	uint32_t type;
} __attribute__((packed)) memory_pool_t;
void create_memory_pool(memory_pool_t *pool,uint32_t bitmap_address,uint32_t begin_address,uint32_t size,uint32_t type);
void show_use_memory(memory_pool_t *pool);
void show_unuse_memory(memory_pool_t *pool);
uint32_t query_unuse_memory_one(memory_pool_t *pool,uint32_t address);
uint32_t query_unuse_memory(memory_pool_t *pool,uint32_t address,uint32_t count);
void set_memory_pool_one(memory_pool_t *pool,uint32_t index,uint8_t value);
void set_memory_pool(memory_pool_t *pool,uint32_t index,uint32_t count,uint8_t size);
void show_memory_pool_message(memory_pool_t *pool);
#endif // POOL_H