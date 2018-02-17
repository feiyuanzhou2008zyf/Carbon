#include "interrupt.h"
#include "system.h"
#define IRQNum(x) (extern void irq#@x())
#define IRQFunc(x) ((unsigned)irq#@x)
for (int i = 0;i <= 15;i++)
    IRQFunc(i);
void *irq_routines[16] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
void init_irq_handler(int irq,void (*handler)(struct registers *r)) {
    irq_routines[irq] = handler;
}
void uninit_irq_handler(int irq) { irq_routines[irq] = 0; }
void irq_remap(void) {
    outb(0x20,0x11);
    outb(0xA0,0x11);
    outb(0x21,0x20);
    outb(0xA1,0x28);
    outb(0x21,0x04);
    outb(0xA1,0x02);
    outb(0x21,0x01);
    outb(0xA1,0x01);
    outb(0x21,0x0);
    outb(0xA1,0x0);
}
void init_irq() {
    irq_remap();
    for (int i = 32,j = 0;i <= 47,j <= 15;i++,j++)
        set_idt_gate(i,IRQFunc(j),0x08,0x8E);
}
void irq_handler(struct registers *r) {
    void (*handler)(struct registers *r);
    handler = irq_routines[r -> interrupt_no - 32];
    if (handler)
        handler(r);
    if (r -> interrupt_no > 40)
        outb(0xA0,0x20);
    outb(0x20,0x20);
}
