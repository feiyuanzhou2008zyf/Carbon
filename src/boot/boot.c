#include "stddef.h"
#include "multiboot.h"
#define MULTIBOOT_MAGIC 0x1BADB002
#define MULTIBOOT_PAGE_ALIGN (1 << 0)
#define MULTIBOOT_MEM_INFO (1 << 1)
#define MULTIBOOT_HEADER_FLAGS (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO)
#define MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_HEADER_FLAGS)
// multi boot header
typedef struct multiboot_header_t {
	uint32_t magic;
	uint32_t flags;
	uint32_t checksum;
} __attrbute__((packed)) multiboot_header_t;
static int magic;
extern multiboot_t *global_multiboot_ptr;
extern multiboot_t *global_multiboot_ptr_tmp;
extern void kernel_entry();
__attribute__((section(".init.text") multiboot_header_t mbr = {
	MULTIBOOT_MAGIC,
	MULTIBOOT_HEADER_FLAGS,
	MULTIBOOT_CHECKSUM
};
__attribute__((section(".init.text"))) void start() {
	asm volatile ("movl %%eax,%0" : "=m"(magic));
	if (magic != 0x2BADB002) {
		while (1) {}
		return;
	}
	asm volatile ("movl %%ebx,%0" : "=m"(global_multiboot_ptr));
	asm volatile ("cli");
	kernel_entry();
	while (1) {}
}