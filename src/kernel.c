#include "console.h"
#include "stdio.h"
#include "debug.h"
#include "gdt.h"
#include idt.h
int kernel_main() {
	init_debug();
	init_gdt();
	init_idt();
	console_clear();
	printk("Hello World,Here Kernel\n");
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
	return 0;
}
