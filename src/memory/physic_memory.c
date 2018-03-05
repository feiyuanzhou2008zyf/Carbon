#include "physic_memory.h"
#include "common.h"
#include "stdio.h"
#include "debug.h"
#include "multiboot.h"
static uint32_t physic_memory_stack[PAGE_MAX_SIZE + 1];
static uint32_t physic_memory_stack_top;
uint32_t physic_page_count;
void show_memory_map() {
	uint32_t mmap_addr = global_multiboot_ptr -> mmap_addr;
    uint32_t mmap_length = global_multiboot_ptr -> mmap_length;
    printk("Memory map:\n");
    mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
    for (mmap = (mmap_entry_t *)mmap_addr; (uint32_t)mmap < mmap_addr + mmap_length; mmap++)
        printk("base_addr = 0x%X%08X, length = 0x%X%08X, type = 0x%X\n", (uint32_t)mmap -> base_addr_high, (uint32_t)mmap -> base_addr_low, (uint32_t)mmap -> length_high, (uint32_t)mmap -> length_low, (uint32_t)mmap -> type);
}
void init_physic_page() {
    mmap_entry_t *mmap_start_addr = (mmap_entry_t *)global_multiboot_ptr -> mmap_addr;
    mmap_entry_t *mmap_end_addr = (mmap_entry_t *)global_multiboot_ptr -> mmap_addr + global_multiboot_ptr -> mmap_length;
    mmap_entry_t *map_entry;
    for (map_entry = mmap_start_addr; map_entry < mmap_end_addr; map_entry++) {
        if (map_entry -> type == 1 && map_entry -> base_addr_low == 0x100000) {
            uint32_t page_addr = map_entry -> base_addr_low + (uint32_t)(kernel_end - kernel_start);
            uint32_t length = map_entry -> base_addr_low + map_entry -> length_low;
            while (page_addr < length && page_addr <= PHYSIC_MEMORY_MAX_SIZE) {
                physic_free_page(page_addr);
                page_addr += PHYSIC_MEMORY_PAGE_SIZE;
                physic_page_count++;
            }
        }
    }
}
uint32_t physic_alloc_page() {
    assert(physic_memory_stack_top != 0);
    uint32_t page = physic_memory_stack[physic_memory_stack_top--];
    return page;
}
void physic_free_page(uint32_t p) {
    assert(physic_memory_stack_top != PAGE_MAX_SIZE);
    physic_memory_stack[++physic_memory_stack_top] = p;
}
