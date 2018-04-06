#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H
#include "stddef.h"
typedef struct segment {
	short limit_low,base_low;
	char base_middle, access_right, limit_high, base_high;
} SEGMENT_DESCRIPTOR;
typedef struct gate {
	short offset_low, selector, offset_high;
	char count, access_right;
} GATE_DESCRIPTOR;
void init_descriptor(void);
extern void load_gdt(SEGMENT_DESCRIPTOR *);
extern void load_idt(GATE_DESCRIPTOR *);
void set_segment(SEGMENT_DESCRIPTOR *,uint32_t limit,int base,int ar);
void set_gate(GATE_DESCRIPTOR *,int offset,int selector,int ar);
#endif // DESCRIPTOR_H