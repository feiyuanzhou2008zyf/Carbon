#include "bit.h"
#include "stdio.h"
#include "stddef.h"
#include "interrupt_routine.h"
isr_t interrupt_handlers[256];
void register_interrupt_handler(uint8_t n, isr_t handler) {
	interrupt_handlers[n] = handler;
}
void isr_handler(registers_t regs) {
	if (interrupt_handlers[regs.int_no] != 0) {
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
	else {
		printk("Unhandled interrupt: %d\n", regs.int_no);
	}
}
void irq_handler(registers_t regs) {
	if (regs.int_no >= 40) {
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);
	if (interrupt_handlers[regs.int_no] != 0) {
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}