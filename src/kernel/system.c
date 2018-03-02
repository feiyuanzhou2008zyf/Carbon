#include "system.h"
#include "io.h"
#include "interrupt.h"
#include "global.h"
#include "isr.h"
#include "irq.h"
#include "timer.h"
#include "keyboard.h"
void kernel_main() {
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	keyboard_install();
	video = (unsigned char *)VIDEO;
	clear();
	return;
}
