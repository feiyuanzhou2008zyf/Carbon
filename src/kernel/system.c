#include "system.h"
#include "io.h"
#include "global.h"
void init() {
	gdt_install();
	idt_install();
}
void kernel_main() {
	char *hello = "Hello World,Here kernel!";
	video = (unsigned char *)VIDEO;
	clear();
	printf("%s\n",hello);
	init();
	return;
}
