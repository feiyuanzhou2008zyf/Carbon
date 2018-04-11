#include "interrupt.h"
#include "stdio.h"
#include "asm.h"
#include "stddef.h"
#define irq(x) ({ \
	asm volatile ("movl %ebp,%esp"); \
	asm volatile ("popl %ebp"); \
	asm volatile (x); \
	asm volatile ("call spurious_irq"); \
	asm volatile ("addl %esp,4"); \
	asm volatile ("hlt"); \
})
#define exception(x,y) ({ \
	asm volatile ("movl %ebp,%esp"); \
	asm volatile ("popl %ebp"); \
	asm volatile (x); \
	asm volatile (y); \
	asm volatile ("call exception_handler"); \
	asm volatile ("addl $8,%esp"); \
	asm volatile ("hlt"); \
})
#define error(x) ({ \
	asm volatile ("movl %ebp,%esp"); \
	asm volatile ("popl %ebp"); \
	asm volatile (x); \
	asm volatile ("call exception_handler"); \
	asm volatile ("addl $8,%esp"); \
	asm volatile ("hlt"); \
})
void divide_error() { exception("pushl $0xFFFFFFFF", "pushl $0"); }
void single_step_exception() { exception("pushl $0xFFFFFFFF", "pushl $1"); }
void nmi() { exception("pushl $0xFFFFFFFF", "pushl $2"); }
void breakpoint_exception() { exception("pushl $0xFFFFFFFF", "pushl $3"); }
void overflow() { exception("pushl $0xFFFFFFFF", "pushl $4"); }
void bounds_check() { exception("pushl $0xFFFFFFFF", "pushl $5"); }
void inval_opcode() { exception("pushl $0xFFFFFFFF", "pushl $6"); }
void copr_not_available() { exception("pushl $0xFFFFFFFF", "pushl $7"); }
void copr_seg_overrun() { exception("pushl $0xFFFFFFFF", "pushl $9"); }
void copr_error() { exception("pushl $0xFFFFFFFF", "pushl $16"); }
void double_fault() { error("pushl $8"); }
void inval_tss() { error("pushl $10"); }
void segment_not_present() { error("pushl $11"); }
void stack_exception() { error("pushl $12"); }
void general_protection() { error("pushl $13"); }
void page_fault() { error("pushl $14"); }
void spurious_irq(int irq) { printk("Spurious interrupt request: %X", irq); }
void keyboard_interrupt(int irq) {
	uint8_t scan_code = inb(0x60);
	printk("%X ", scan_code);
}
void interrupt_handler() {
	keyboard_interrupt(1);
	outb(0x20, 0x61);
	asm volatile ("movl %ebp,%esp;leave;iret");
}
void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags) {
	char *err_msg[] = {
		"#DE Divide Error",
		"#DB RESERVED",
		"¡ª  NMI Interrupt",
		"#BP Breakpoint",
		"#OF Overflow",
		"#BR BOUND Range Exceeded",
		"#UD Invalid Opcode (Undefined Opcode)",
		"#NM Device Not Available (No Math Coprocessor)",
		"#DF Double Fault",
		"    Coprocessor Segment Overrun (reserved)",
		"#TS Invalid TSS",
		"#NP Segment Not Present",
		"#SS Stack-Segment Fault",
		"#GP General Protection",
		"#PF Page Fault",
		"¡ª  (Intel reserved. Do not use.)",
		"#MF x87 FPU Floating-Point Error (Math Fault)",
		"#AC Alignment Check",
		"#MC Machine Check",
		"#XF SIMD Floating-Point Exception"
	};
	printk("Exception! --> %s\nEflags: 0x%X\nCS: 0x%X,EIP: 0x%X\n", err_msg[err_code], eflags, cs, eip);
	if (err_code != 0xFFFFFFFF) { printk("Error code: 0x%X", err_code); }
}
void interrupt_request00() {
	asm volatile ("movl %ebp,%esp");
	asm volatile ("popl %ebp");
	asm volatile ("movb $0x20,%al");
	asm volatile ("outb %al,$0xa0");
	asm volatile ("outb %al,$0x20");
	asm volatile ("iret");
}
void interrupt_request01() { irq("pushl $1"); }
void interrupt_request02() { irq("pushl $2"); }
void interrupt_request03() { irq("pushl $3"); }
void interrupt_request04() { irq("pushl $4"); }
void interrupt_request05() { irq("pushl $5"); }
void interrupt_request06() { irq("pushl $6"); }
void interrupt_request07() { irq("pushl $7"); }
void interrupt_request08() { irq("pushl $8"); }
void interrupt_request09() { irq("pushl $9"); }
void interrupt_request10() { irq("pushl $10"); }
void interrupt_request11() { irq("pushl $11"); }
void interrupt_request12() { irq("pushl $12"); }
void interrupt_request13() { irq("pushl $13"); }
void interrupt_request14() { irq("pushl $14"); }
void interrupt_request15() { irq("pushl $15"); }