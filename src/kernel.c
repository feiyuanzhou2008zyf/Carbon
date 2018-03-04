#include "console.h"
#include "stdio.h"
#include "debug.h"
#include "gdt.h"
int kernel_main() {
	init_debug();
	init_gdt();
	console_clear();
	printk("Hello World,Here Kernel\n");
	return 0;
}
