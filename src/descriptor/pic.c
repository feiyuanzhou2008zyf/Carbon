#include "pic.h"
#include "asm.h"
void init_pic(void) {
	outb(PIC0_IMR, 0xff);
	outb(PIC1_IMR, 0xff);
	outb(PIC0_ICW1, 0x11);
	outb(PIC0_ICW2, 0x20);
	outb(PIC0_ICW3, 1 << 2);
	outb(PIC0_ICW4, 0x01);
	outb(PIC1_ICW1, 0x11);
	outb(PIC1_ICW2, 0x28);
	outb(PIC1_ICW3, 2);
	outb(PIC1_ICW4, 0x01);
	outb(PIC0_IMR, 0xfb);
	outb(PIC1_IMR, 0xff);
	return;
}