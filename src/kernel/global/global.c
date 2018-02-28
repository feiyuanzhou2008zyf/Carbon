#include "global.h"
void set_gdt_gate(int num,unsigned long base,unsigned long limit,unsigned char access,unsigned long gran) {
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].gran = ((limit >> 16) & 0x0F);
	gdt[num].gran |= (gran & 0xF0);
	gdt[num].access = access;
}
void gdt_install() {
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
	gdt_ptr.base = (unsigned int)&gdt;
	set_gdt_gate(0,0,0,0,0);
	set_gdt_gate(1,0,0xFFFFFFFF,0x9A,0xCF);
	set_gdt_gate(2,0,0xFFFFFFFF,0x92,0xCF);
	gdt_flush();
}
