#include "gdt.h"
#include "string.h"
#define GDT_LENGTH 5
gdt_entry_t gdt_entry[GDT_LENGTH];
gdt_ptr_t gdt_ptr;
static void set_gdt_gate(int32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran);
extern uint32_t stack;
void init_gdt() {
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
    gdt_ptr.base = (uint32_t)&gdt_entry;
    set_gdt_gate(0, 0, 0, 0, 0);
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    flush_gdt((uint32_t)&gdt_ptr);
}
static void set_gdt_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entry[num].base_low = (base & 0xFFFF);
    gdt_entry[num].base_middle = (base >> 16) & 0xFF;
    gdt_entry[num].base_high = (base >> 24) & 0xFF;
    gdt_entry[num].limit_low = (limit & 0xFFFF);
    gdt_entry[num].granularity = (limit >> 16) & 0x0F;
    gdt_entry[num].granularity |= gran & 0xF0;
    gdt_entry[num].access = access;
}
