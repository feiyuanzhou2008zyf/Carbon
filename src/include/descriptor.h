#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H
#define ADDR_IDT 0x0026f800
#define LIMIT_IDT 0x000007ff
#define ADDR_GDT 0x00270000
#define LIMIT_GDT 0x0000ffff
#define ADDR_SEGMENT 0x00280000
#define LIMIT_SEGMENT 0x0007ffff
#define AR_DATA32_RW 0x4092
#define AR_CODE32_ER 0x409a
#define AR_INTGATE32 0x008e
#include "stddef.h"
typedef struct segment {
	short limit_low, base_low;
	char base_middle, access_right, limit_high, base_high;
} SEGMENT_DESCRIPTOR;
typedef struct gate {
	short offset_low, selector, offset_high;
	char count, access_right;
} GATE_DESCRIPTOR;
void init_descriptor(void);
extern void load_gdt(SEGMENT_DESCRIPTOR *);
extern void load_idt(GATE_DESCRIPTOR *);
void set_segment(SEGMENT_DESCRIPTOR *, uint32_t limit, int base, int ar);
void set_gate(GATE_DESCRIPTOR *, int offset, int selector, int ar);
#endif // DESCRIPTOR_H