#include "console.h"
#include "stdio.h"
#include "debug.h"
int kernel_main() {
	init_debug();
	console_clear();
	printk_color(black,white,"Hello World,Here Kernel\n");
	panic("test");
	return 0;
}
