#ifndef GLOBAL_H
#define GLOBAL_H
struct gdt_entry_struct {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char gran;
	unsigned char base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;
struct gdt_ptr_struct {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;
gdt_entry_t gdt[3];
gdt_ptr_t gdt_ptr;
extern void gdt_flush();
extern void gdt_install();
#endif // GLOBAL_H
