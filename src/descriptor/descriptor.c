#include "descriptor.h"
inline void load_gdt(SEGMENT_DESCRIPTOR *ptr) { asm volatile ("lgdt %0"::"m"(ptr)); }
inline void load_idt(GATE_DESCRIPTOR *ptr) { asm volatile ("lidt %0"::"m"(ptr)); }
void set_segment(SEGMENT_DESCRIPTOR *segment, uint32_t limit, int base, int ar) {
	if (limit > 0xfffff) {
		ar |= 0x8000;
		limit /= 0x1000;
	}
	segment->limit_low = limit & 0xffff;
	segment->base_low = base & 0xffff;
	segment->base_middle = (base >> 16) & 0xff;
	segment->access_right = ar & 0xff;
	segment->limit_high = ((limit >> 16) & 0xff) | ((ar >> 8) & 0xf0);
	segment->base_high = (base >> 24) & 0xff;
	return;
}
void set_gate(GATE_DESCRIPTOR *gate, int offset, int selector, int ar) {
	gate->offset_low = offset & 0xffff;
	gate->selector = selector;
	gate->count = (ar >> 8) & 0xff;
	gate->access_right = ar & 0xff;
	gate->offset_high = (offset >> 16) & 0xffff;
	return;
}
void init_descriptor(void) {
	SEGMENT_DESCRIPTOR *gdt = (SEGMENT_DESCRIPTOR *)0x00270000;
	GATE_DESCRIPTOR *idt = (GATE_DESCRIPTOR *)0x0026f800;
	for (int i = 0; i < 8192; i++) { set_segment(gdt + i,0,0,0); }
	set_segment(gdt + 1, 0xffffffff, 0x00000000, 0x4092);
	set_segment(gdt + 2, 0x0007ffff, 0x00280000, 0x409a);
	load_gdt(gdt);
	for (int i = 0; i < 256; i++) { set_gate(idt + i, 0, 0, 0); }
	load_idt(idt);
	return;
}
