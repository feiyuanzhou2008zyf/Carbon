#include "idt.h"
#include "system.h"
#define ISRFunc(x) (extern void isr#@x())
#define ISRNumber(x) ((unsigned)isr#@x)
for (int i = 0;i <= 31;i++)
    ISRFunc(i);
void init_idt() {
    for (int i = 0;i <= 31;i++)
        set_idt_gate(i,ISRNumber(i),0x08,0x8E);
}
unsigned char *exception_message[] = {
    "Divide by zero",
    "Debug",
    "Non maskable interrupt",
    "Breakpoint",
    "Into detected overflow",
    "Out of bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
}
void fault_handler(struct registers *reg) {
    if (reg -> interrupt_no < 32) {
        puts(exception_message[reg -> interrupt_no]);
        puts(" exception,System halted\n");
        for (;;);
    }
}
