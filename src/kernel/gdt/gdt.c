#include "gdt.h"
void set_gdt_gate(int num,unsigned long base,unsigned long limit,unsigned char access,unsigned char gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].gran = ((limit >> 16) & 0xFF);
    gdt[num].gran |= (gran & 0xF0);
    gdt[num].access = access;
}
void init_gdt() {
    gptr.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gptr.base = &gdt;
    set_gdt_gate(0,0,0,0,0);
    set_gdt_gate(1,0,0xFFFFFFFF,0x9A,0xCF);
    set_gdt_gate(2,0,0xFFFFFFFF,0x92,0xCF);
    gdt_flush();
}
