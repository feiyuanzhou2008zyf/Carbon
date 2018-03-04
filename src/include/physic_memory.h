#ifndef PHYSIC_MEMORY_H
#define PHYSIC_MEMORY_H
#include "multiboot.h"
#define STACK_SIZE 8192
#define PHYSIC_MEMORY_MAX_SIZE 0x20000000
#define PHYSIC_MEMORY_PAGE_SIZE 0x1000
#define PAGE_MAX_SIZE (PHYSIC_MEMORY_MAX_SIZE / PHYSIC_MEMORY_PAGE_SIZE)
#define PHYSIC_PAGE_MASK 0xFFFFF000
extern uint8_t kernel_start[];
extern uint8_t kernel_end[];
extern uint32_t physic_page_count;
void show_memory_map();
void init_physic_page();
uint32_t physic_alloc_page();
void physic_free_page(uint32_t p);
#endif // PHYSIC_MEMORY_H