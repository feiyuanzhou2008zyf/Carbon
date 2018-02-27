#include "interrupt.h"
#include "lib.h"
void set_idt_gate(unsigned char num,unsigned long base,unsigned short selector,unsigned char flags) {}
void idt_install() {
	idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
	idt_ptr.base = &idt;
	memset(&idt,0,sizeof(idt_entry_t) * 256);
	idt_load();
}
