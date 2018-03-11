#include "kernel.h"
int memory_size;
void kernel_main();
/*
multiboot_t *global_multiboot_ptr;
char kernel_stack[STACK_SIZE];
__attribute__((section(".init.data"))) page_t *pgd_tmp = (page_t *)0x1000;
__attribute__((section(".init.data"))) page_t *pte_low = (page_t *)0x2000;
__attribute__((section(".init.data"))) page_t *pte_high = (page_t *)0x3000;
__attribute__((section(".init.text"))) void kernel_entry() {
	pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
    pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_high | PAGE_PRESENT | PAGE_WRITE;
    int i;
    for (i = 0; i < 1024; i++) { pte_low[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE; }
    for (i = 0; i < 1024; i++) { pte_high[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE; }
    asm volatile ("mov %0, %%cr3" : : "r" (pgd_tmp));
    uint32_t cr0;
    asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000;
    asm volatile ("mov %0, %%cr0" : : "r" (cr0));
    uint32_t kernel_stack_top = ((uint32_t)kernel_stack + STACK_SIZE) & 0xFFFFFFF0;
    asm volatile ("mov %0, %%esp\n\t"
				  "xor %%ebp, %%ebp" : : "r" (kernel_stack_top));
    global_multiboot_ptr = global_multiboot_ptr_tmp + PAGE_OFFSET;
    kernel_main();
}
*/
__attribute__((section(".init.text"))) void kernel_entry() {
	asm("movw $0x30,%ax");
	asm("movw %ax,%ss");
	asm("movl $0x500000,%esp");
	asm("movl %esp,%ebp");
	memory_size = *((int *)0x8000);
	kernel_main();
}
void kernel_main() {
	init_debug();
	init_gdt();
	init_idt();
	console_clear();
	printk("Hello World,Here Kernel\n");
	init_timer(200);
	init_memory_manager(memory_size,0,0xFFFFF);
}
