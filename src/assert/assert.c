#include "assert.h"
#include "stdio.h"
static elf_t kernel_elf;
void init_debug() {
	kernel_elf = elf_from_multiboot(global_multiboot_ptr);
}
void print_cur_status() {
	static int round = 0;
	uint16_t reg1, reg2, reg3, reg4;
	asm volatile ("mov %%cs, %0;"
		"mov %%ds, %1;"
		"mov %%es, %2;"
		"mov %%ss, %3;" : "=m"(reg1), "=m"(reg2), "=m"(reg3), "=m"(reg4));
	printk("%d: @ring %d\n", round, reg1 & 0x3);
	printk("%d:  cs = %x\n", round, reg1);
	printk("%d:  ds = %x\n", round, reg2);
	printk("%d:  es = %x\n", round, reg3);
	printk("%d:  ss = %x\n", round, reg4);
	++round;
}
void panic(const char *msg) {
	printk("*** System panic: %s\n", msg);
	print_stack_trace();
	printk("*** System panic end ***\n");
	while (1);
}
void print_stack_trace() {
	uint32_t *ebp, *eip;
	asm volatile ("mov %%ebp, %0" : "=r" (ebp));
	while (ebp) {
		eip = ebp + 1;
		printk("   [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
		ebp = (uint32_t*)*ebp;
	}
}
void _assert(void *exp, void *file, uint32_t line) {
	printk("Assertion failed: %s,File: %s,Line: %d", exp, file, line);
	print_stack_trace();
	asm volatile ("hlt");
}
