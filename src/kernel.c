#include "console.h"
int kernel_main(multiboot_t *ptr) {
	console_clear();
	console_write("Hello World,Here Kernel");
}