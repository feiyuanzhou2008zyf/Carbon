#include "global.h"
#include "string.h"
#include "stddef.h"
#define GDT_LENGTH 5
gdt_entry_t gdt_entries[GDT_LENGTH];
gdt_ptr_t gdt_ptr;
extern uint32_t stack;
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
<<<<<<< HEAD
// inline void flush_gdt(uint32_t ptr) { asm volatile ("lgdt %%eax" :: "a"(&ptr)); }
=======
inline void flush_gdt(uint32_t ptr) { asm volatile ("lgdt %%eax" :: "a"(ptr)); }
>>>>>>> 4f9fb947860bcbbd5b72e25e7b58bb9cdf38c588
void init_gdt() {
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	flush_gdt((uint32_t)&gdt_ptr);
}
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;
	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access = access;
}
