#ifndef GLOBAL_H
#define GLOBAL_H
#include "stddef.h"
typedef struct segment_descriptor {
	short limit_low;
	short base_low;
	char base_middle;
	char access;
	char limit_high;
	char base_high;
} segment;
typedef struct gate_descriptor {
	short offset_low;
	short selector;
	char count;
	char access;
	char offset_high;
} gate;
void set_segdesc(segment *s,uint32_t limit,int base,int ar);
void set_gatedesc(gate *g,int offset,int selector,int ar);
#endif // GLOBAL_H