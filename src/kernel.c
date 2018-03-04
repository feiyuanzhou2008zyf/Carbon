#include "console.h"
#include "stdio.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "physic_memory.h"
int kernel_main() {
	init_debug();
	init_gdt();
	init_idt();
	console_clear();
	printk("Hello World,Here Kernel\n");
	init_timer(200);
	printk("kernel in memory start: 0x%08X\n", kernel_start);
    printk("kernel in memory end:   0x%08X\n", kernel_end);
    printk("kernel in memory used:   %d KB\n\n", (kernel_end - kernel_start + 1023) / 1024);
	show_memory_map();
	return 0;
}