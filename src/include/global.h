#ifndef GLOBAL_H
#define GLOBAL_H
#include "stddef.h"
#define GDT_NUM 256
/*
typedef struct gdt_entry_t {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;
typedef struct gdt_ptr_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;
void init_gdt();
extern void flush_gdt(uint32_t);
enum RPL {
	SYSTEM = 0,
	USER = 3
};
enum SEGMENT_TYPE {
	DATA_READ = 0b0000,
	DATA_READ_WRITE = 0b0010,
	CODE_READ = 0b1000,
	CODE_READ_WRITE = 0b1010
};
struct segment_descriptor {
	uint32_t segment_0_15 : 16;
	uint32_t base_addr_0_23 : 24;
	enum SEGMENT_TYPE seg_type : 4;
	enum S {
		SYSTEM = 0,
		CODE_DATA = 1
	} s : 1;
	RPL rpl : 2;
	int present : 1;
	uint32_t segment_16_19 : 4;
	uint32_t AVL : 1;
	uint32_t zero : 1;
	enum D {
		BIT_32 = 1,
		BIT_16 = 0
	} d : 1;
	enum G {
		UNIT_BYTE = 0,
		UNIT_4K = 1
	} g : 1;
	uint32_t base_addr_24_31 : 8;
};
typedef struct gdt_descriptor {
	uint32_t size;
	void *addr;
} __attribute__((packed)) gdt_descriptor_t;
typedef struct segment_descriptor segment;
typedef struct segment_descriptor global_descriptor;
typedef struct segment_descriptor local_descriptor;
void set_gdt_gate(uint8_t index,global_descriptor desc);
int init_gdt();
*/
extern void flush_gdt(uint32_t);
#endif // GLOBAL_H
