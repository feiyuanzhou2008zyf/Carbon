#ifndef IDT_H
#define IDT_H
struct idt_entry {
    unsigned short base_low;
    unsigned short selector;
    unsigned char always;
    unsigned char flags;
    unsigned short base_high;
}__attribute__((packed));
struct idt_ptr {
    unsigned short limit;
    unsigned short base;
}__attribute__((packed));
struct idt_entry idt[256];
struct idt_ptr iptr;
extern void idt_load();
void set_idt_gate(unsigned chat num,unsigned long base,unsigned short selector,unsigned char flags);
#endif // IDT_H
