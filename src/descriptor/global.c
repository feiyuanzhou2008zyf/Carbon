#include "global.h"
gdt_entry_t entrys[5];
gdt_ptr_t gdt_pointer;
static gdt_entry_t create_gdt(uint32_t base, uint32_t limit, uint16_t flag);
static gdt_entry_t create_gdt(uint32_t base, uint32_t limit, uint16_t flag) {
	uint64_t entry;
	entry = limit & 0x000F0000;
	entry |= (flag << 8) & 0x00F0FF00;
	entry |= (base >> 16) & 0x000000FF;
	entry |= base & 0xFF000000;
	entry <<= 32;
	entry |= base << 16;
	entry |= limit & 0x0000FFFF;
	return entry;
}
void init_gdt() {
	gdt_pointer.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_pointer.base = (uint32_t)entrys;
	entrys[0] = create_gdt(0, 0, 0);
	entrys[1] = create_gdt(0, 0x000FFFFF, (GDT_CODE_PL0));
	entrys[2] = create_gdt(0, 0x000FFFFF, (GDT_DATA_PL0));
	entrys[3] = create_gdt(0, 0x000FFFFF, (GDT_CODE_PL3));
	entrys[4] = create_gdt(0, 0x000FFFFF, (GDT_DATA_PL3));
	flush_gdt((uint32_t)&gdt_pointer);
}
void flush_gdt(gdt_entry_t ptr) {
	asm volatile ("lgdt %0" : : "m"(ptr));
}
