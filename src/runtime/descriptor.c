#include "global.h"
void set_segdesc(Segment *s,uint32_t limit,int base,int ar) {
	if (limit > 0xffffff) {
		ar |= 0x8000;
		limit /= 0x1000;
	}
	s -> limit_low = limit & 0xffff;
	s -> base_low = base & 0xffff;
	s -> base_middle = (base >> 16) & 0xff;
	s -> access = ar & 0xff;
	s -> limit_high = ((limit >> 16) & 0xff) | ((ar >> 8) & 0xf0);
	s -> base_high = (base >> 24) & 0xff;
	return;
}
void set_gatedesc(Gate *g,int offset,int selector,int ar) {
	g -> offset_low = offset & 0xffff;
	g -> selector = selector;
	g -> count = (ar >> 8) & 0xff;
	g -> access = ar & 0xff;
	g -> offset_high = (offset >> 16) & 0xffff;
	return;
}