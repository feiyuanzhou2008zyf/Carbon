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
	printf("GDT installed\n");
	idt_install();
	printf("IDT installed\n");
	isrs_install();
	printf("ISR installed\n");
	irq_install();
	printf("IRQ installed\n");
	timer_install();
	printf("Timer PIT installed\n");
	keyboard_install();
	printf("Keyboard Interrupt installed\n");
}
void kernel_main() {
	char *hello = "Hello World,Here kernel!";
	video = (unsigned char *)VIDEO;
	clear();
	printf("%s\n",hello);
	init();
	return;
}
