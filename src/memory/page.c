#include "page.h"
void alloc_page_table(const uint32_t page_dir_base,int index,uint32_t page_tpl_base,int attr) {
	uint32_t *p = (uint32_t *)(page_dir_base & 0xFFFFF000);
	p[index] = (uint32_t)((page_tpl_base & 0xFFFFF000) + attr);
}
void alloc_page(const uint32_t page_tpl_base,int index,uint32_t page_address,int attr) {
	uint32_t *p = (uint32_t *)(page_tpl_base & 0xFFFFF000);
	p[index] = (uint32_t)((page_address & 0xFFFFF000) + attr);
}
void page_running(const uint32_t page_dir_base) {
	uint32_t page_dir;
	page_dir = (uint32_t)((uint32_t)page_dir_base & 0xFFFFF000);
	asm volatile ("pusha");
	asm volatile ("movl %0,%%eax"::"d"(page_dir));
	asm volatile ("movl %eax,%cr3");
	asm volatile ("movl %cr0,%eax");
	asm volatile ("orl $0x80000000,%eax");
	asm volatile ("movl %eax,%cr0");
	asm volatile ("nop");
	asm volatile ("popa");
}
void page_end() {
	asm volatile ("pusha");
	asm volatile ("movl %cr0,%eax");
	asm volatile ("andl $0x7FFFFFFF,%eax");
	asm volatile ("movl %eax,%cr0");
	asm volatile ("nop");
	asm volatile ("popa");
}
uint32_t compute_page(uint32_t memory_size) {
	if(memory_size % ( 4 * 1024) == 0)
		return memory_size / (4 * 1024);
	else
		return memory_size / (4 * 1024) + 1;
}