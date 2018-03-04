#ifndef HEAP_H
#define HEAP_H
#include "types.h"
#define HEAP_START 0xE0000000
typedef struct header {
	struct header *prev;
	struct header *next;
	uint32_t allocated : 1;
	uint32_t length : 31;
} header_t;
void init_heap();
void *kmalloc(uint32_t len);
void kfree(void *p);
void test_heap();
#endif // HEAP_H