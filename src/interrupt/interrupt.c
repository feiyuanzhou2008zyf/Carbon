#include "interrupt.h"
#include "stdio.h"
void modify_gate(Gate *g,uint32_t offset,uint8_t selector,uint8_t dcount,uint8_t attr) {
	g -> offset_low  = offset & 0xFFFF;
	g -> selector = selector;	
	g -> attr = (dcount & 0x1F) | ((attr << 8) & 0xFF00);	
	g -> offset_high  = (offset >> 16) & 0xFFFF;
}
void set_idt(IDT *idt,int index,interrupt_handler function,uint16_t selector,uint8_t dcount,uint8_t attr) {
	Gate *tmp;
	tmp = (Gate *)idt;
	tmp = tmp + index;
	modify_gate(tmp,(uint32_t)function,selector,dcount,attr);
}
void init_idt(IDT *idt) {
	init_pic();
	set_idt(idt,0,asm_inthandler0,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,1,asm_inthandler1,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,2,asm_inthandler2,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,3,asm_inthandler3,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,4,asm_inthandler4,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,5,asm_inthandler5,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,6,asm_inthandler6,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,7,asm_inthandler7,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,8,asm_inthandler8,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,9,asm_inthandler9,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,10,asm_inthandler10,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,11,asm_inthandler11,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,12,asm_inthandler12,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,13,asm_inthandler13,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,14,asm_inthandler14,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,15,asm_inthandler15,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,16,asm_inthandler16,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,17,asm_inthandler17,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,18,asm_inthandler18,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,19,asm_inthandler19,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,20,asm_inthandler20,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,21,asm_inthandler21,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,22,asm_inthandler22,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,23,asm_inthandler23,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,24,asm_inthandler24,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,25,asm_inthandler25,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,26,asm_inthandler26,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,27,asm_inthandler27,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,28,asm_inthandler28,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,29,asm_inthandler29,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,30,asm_inthandler30,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,31,asm_inthandler31,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,32,asm_inthandler32,0x0010,0,IDT_DESC_ATTR_DPL0);
	set_idt(idt,33,asm_inthandler33,0x0010,0,IDT_DESC_ATTR_DPL0);
	uint64_t idt_operand = ((sizeof(IDT) - 1) | ((uint64_t)((uint32_t)idt << 16)));
	asm volatile ("lidt %0"::"m"(idt_operand));
}