MULTIBOOT_MAGIC equ 0x1BADB002
MULTIBOOT_PAGE_ALIGN equ 1 << 0
MULTIBOOT_MEM_INFO equ 1 << 1
MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_HEADER_FLAGS)
[bits 32]
[section .text]
dd MULTIBOOT_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd MULTIBOOT_CHECKSUM
[global start]
[global global_multiboot_ptr]
[extern kernel_main]
start:
	cli
	mov esp,STACK_TOP
	mov ebp,0
	and esp,0FFFFFFFH
	mov [global_multiboot_ptr],ebx
	call kernel_main
stop:
	hlt
	jmp stop
[section .bss]
stack:
	resb 32768
global_multiboot_ptr:
	resb 4
STACK_TOP equ $ - stack - 1