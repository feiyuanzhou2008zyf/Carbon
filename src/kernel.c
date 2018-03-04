#include "console.h"
#include "stdio.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
int kernel_main() {
	init_debug();
	init_gdt();
	init_idt();
	console_clear();
	printk("Hello World,Here Kernel\n");
	init_timer(200);
	asm volatile ("sti");
	return 0;
}
