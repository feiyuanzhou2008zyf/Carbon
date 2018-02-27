#ifndef INTERRUPT_H
#define INTERRUPT_H
struct idt_entry_struct {
	unsigned short base_low;
	unsigned short selector;
	unsigned char always;
	unsigned char flags;
	unsigned char base_high;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;
struct idt_ptr_struct {
	unsigned short limit;
	unsigned short base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;
idt_entry_t idt[256];
idt_ptr_t idt_ptr;
extern void idt_load();
extern void idt_install();
#endif // INTERRUPT_H
