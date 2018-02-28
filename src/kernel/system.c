#include "system.h"
#include "io.h"
#include "interrupt.h"
#include "global.h"
#include "isr.h"
#include "irq.h"
#include "timer.h"
#include "keyboard.h"
void init() {
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	keyboard_install();
}
void kernel_main() {
	init();
	char *hello = "Hello World,Here kernel!";
	video = (unsigned char *)VIDEO;
	clear();
	printf("%s\n",hello);
	return;
}
