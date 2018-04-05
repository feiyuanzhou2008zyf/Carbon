#include "bit.h"
#include "boot.h"
#include "debug.h"
#include "global.h"
#include "stdarg.h"
#include "stddef.h"
#include "stdelf.h"
#include "stdio.h"
#include "string.h"
int memory_size;
void kernel_main();
extern multiboot_t *multiboot_ptr;
multiboot_t *global_multiboot_ptr;
extern uint8_t kernel_start[];
extern uint8_t kernel_end[];
__attribute__((section(".text"))) void kernel_entry() {
	global_multiboot_ptr = multiboot_ptr;
	memory_size = global_multiboot_ptr->mem_upper;
	kernel_main();
	asm volatile ("hlt");
}
void kernel_main() {
	init_debug();
	init_gdt();
	clear();
	printk("Hello World,Here Kernel\n");
	printk("kernel in memory start: 0x%08X\n", kernel_start);
	printk("kernel in memory end: 0x%08X\n", kernel_end);
	printk("kernel in memory used: %d KB\n\n", (kernel_end - kernel_start) / 1024);
}
