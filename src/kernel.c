#include "kernel.h"
int memory_size;
void kernel_main();
extern multiboot_t *global_multiboot_ptr_tmp;
multiboot_t *global_multiboot_ptr;
extern uint8_t kernel_start[];
extern uint8_t kernel_end[];
__attribute__((section(".init.text"))) void kernel_entry() {
	global_multiboot_ptr = global_multiboot_ptr_tmp;
	memory_size = global_multiboot_ptr->mem_upper;
	kernel_main();
	while(1){}
}
void kernel_main() {
	init_debug();
	init_gdt();
	init_idt();
	console_clear();
	init_timer(200);
	printk("Hello World,Here Kernel\n");
	uint32_t address = global_multiboot_ptr->mmap_addr;
	uint32_t length = global_multiboot_ptr->mmap_length;
	printk("kernel in memory start: 0x%08X\n", kernel_start);
    printk("kernel in memory end:   0x%08X\n", kernel_end);
    printk("kernel in memory used:   %d KB\n\n", (kernel_end - kernel_start) / 1024);
	init_memory_manager(address,length,kernel_start,kernel_end);
}
