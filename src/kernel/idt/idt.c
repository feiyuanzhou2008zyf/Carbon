#include "idt.h"
#include "system.h"
void set_idt_gate(unsigned char num,unsigned long base,unsigned short selector,unsigned char flags) {}
void init_idt() {
    iptr.limit = (sizeof(struct idt_entry) * 256) - 1;
    iptr.base = &idt;
    memset(&idt,0,sizeof(struct idt_entry) * 256);
    idt_load();
}
