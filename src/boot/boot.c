#include "stddef.h"
#include "elf.h"
#include "multiboot.h"
#define MULTIBOOT_MAGIC 0x1BADB002
#define MULTIBOOT_PAGE_ALIGN (1 << 0)
#define MULTIBOOT_MEM_INFO (1 << 1)
#define MULTIBOOT_HEADER_FLAGS (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO)
#define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC + MULTIBOOT_HEADER_FLAGS)
// multi boot header
typedef struct multiboot_header {
	uint64_t magic;
	uint64_t flags;
	uint64_t checksum;
} multiboot_header_t;
uint64_t magic;
extern multiboot_t *global_multiboot_ptr;
extern multiboot_t *global_multiboot_ptr_tmp;
extern void kernel_entry();
multiboot_header_t mbr __attribute__((section(".text"))) = {
	.magic = MULTIBOOT_MAGIC,
	.flags = MULTIBOOT_HEADER_FLAGS,
	.checksum = MULTIBOOT_CHECKSUM
};
__attribute__((section(".init.text"))) void start() {
	asm volatile ("movl %%eax,%0" : "=m"(magic));
	if (magic != 0x2BADB002) {
		while (1) {}
	}
	asm volatile ("movl %%ebx,%0" : "=m"(global_multiboot_ptr));
	asm volatile ("cli");
	kernel_entry();
	while (1) {}
}
