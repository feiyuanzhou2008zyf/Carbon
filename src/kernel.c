#include "console.h"
#include "string.h"
#include "stdio.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "physic_memory.h"
#include "virtual_memory.h"
void kernel_main();
multiboot_t *global_multiboot_ptr;
char kernel_stack[STACK_SIZE];
__attribute__((section(".init.data"))) page_t *pgd_tmp = (page_t *)0x1000;
__attribute__((section(".init.data"))) page_t *pte_low = (page_t *)0x2000;
__attribute__((section(".init.data"))) page_t *pte_high = (page_t *)0x3000;
__attribute__((section(".init.text"))) void kernel_entry() {
	pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
    pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_high | PAGE_PRESENT | PAGE_WRITE;
    int i;
    for (i = 0; i < 1024; i++) { pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE; }
    for (i = 0; i < 1024; i++) { pte_high[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE; }
    asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));
    uint32_t cr0;
    asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000;
    asm volatile ("mov %0, %%cr0" : : "r" (cr0));
    uint32_t kernel_stack_top = ((uint32_t)kernel_stack + STACK_SIZE) & 0xFFFFFFF0;
    asm volatile ("mov %0, %%esp\n\t"
				  "xor %%ebp, %%ebp" : : "r" (kernel_stack_top));
    global_multiboot_ptr = global_multiboot_ptr_tmp + PAGE_OFFSET;
    kernel_main();
}
void kernel_main() {
	init_debug();
	init_gdt();
	init_idt();
	console_clear();
	printk("Hello World,Here Kernel\n");
	init_timer(200);
	printk("kernel in memory start: 0x%08X\n", kernel_start);
    printk("kernel in memory end:   0x%08X\n", kernel_end);
    printk("kernel in memory used:   %d KB\n\n", (kernel_end - kernel_start) / 1024);
	show_memory_map();
	init_physic_page();
	printk("\nThe Count of Physical Memory Page is: %u\n\n", physic_page_count);
    uint32_t alloc_addr = NULL;
    printk("Test Physical Memory Alloc :\n");
    alloc_addr = physic_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", alloc_addr);
    alloc_addr = physic_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", alloc_addr);
    alloc_addr = physic_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", alloc_addr);
    alloc_addr = physic_alloc_page();
    printk("Alloc Physical Addr: 0x%08X\n", alloc_addr);
	while (1) {
		asm volatile ("hlt");
	}
}