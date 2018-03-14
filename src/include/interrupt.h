#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "descriptor.h"
#include "init8259a.h"
#define PIC_M_CTRL 0x20
#define PIC_M_DATA 0x21
#define PIC_S_CTRL 0xa0
#define PIC_S_DATA 0xa1
#define IDT_DESC_CNT 0x22
#define	IDT_DESC_P 1
#define	IDT_DESC_DPL0 0
#define	IDT_DESC_DPL3 3
#define	IDT_DESC_32_TYPE 0xE
#define	IDT_DESC_16_TYPE 0x6   
#define	IDT_DESC_ATTR_DPL0 ((IDT_DESC_P << 7) + (IDT_DESC_DPL0 << 5) + IDT_DESC_32_TYPE)
#define	IDT_DESC_ATTR_DPL3 ((IDT_DESC_P << 7) + (IDT_DESC_DPL3 << 5) + IDT_DESC_32_TYPE)
#define INTERRUPT_GATE_COUNT 34
typedef struct interrupt_manager {
	Gate *g;
	int count;
} InterruptManager;
typedef struct IDT {
	Gate idt[INTERRUPT_GATE_COUNT];
} IDT;
typedef void*(interrupt_handler)();
void modify_gate(Gate *g,uint32_t offset,uint8_t selector,uint8_t dcount,uint8_t attr);
void set_idt(IDT *idt,int index,interrupt_handler function,uint16_t selector,uint8_t dcount,uint8_t attr);
void init_idt(IDT *idt);
extern void asm_inthandler33();
extern void asm_inthandler32();
extern void asm_inthandler31();
extern void asm_inthandler30();
extern void asm_inthandler29();
extern void asm_inthandler28();
extern void asm_inthandler27();
extern void asm_inthandler26();
extern void asm_inthandler25();
extern void asm_inthandler24();
extern void asm_inthandler23();
extern void asm_inthandler22();
extern void asm_inthandler21();
extern void asm_inthandler20();
extern void asm_inthandler19();
extern void asm_inthandler18();
extern void asm_inthandler17();
extern void asm_inthandler16();
extern void asm_inthandler15();
extern void asm_inthandler14();
extern void asm_inthandler13();
extern void asm_inthandler12();
extern void asm_inthandler11();
extern void asm_inthandler10();
extern void asm_inthandler9();
extern void asm_inthandler8();
extern void asm_inthandler7();
extern void asm_inthandler6();
extern void asm_inthandler5();
extern void asm_inthandler4();
extern void asm_inthandler3();
extern void asm_inthandler2();
extern void asm_inthandler1();
extern void asm_inthandler0();
#endif // INTERRUPT_H