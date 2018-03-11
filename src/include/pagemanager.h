#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H
#include "page.h"
#include "stddef.h"
#include "pool.h"
typedef struct page_manager_t {
	memory_pool_t physical_memory_pool;
	uint32_t pbl_address;
	char bitmap[128];
	bitmap_t pbl_bitmap;
} __attribute__((packed)) page_manager_t;
void create_page_manager(page_manager_t *p,uint32_t kernel_begin_address,uint32_t kernel_size,uint32_t physical_memory_size,...);
void set_page(page_manager_t *p,uint32_t virtual_page_address,uint32_t physical_page_address);
void open_page_mode(page_manager_t *p);
void close_page_mode();
void flush_table(page_manager_t *p);
#endif // PAGE_MANAGER_H