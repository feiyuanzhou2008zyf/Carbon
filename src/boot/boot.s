MULTIBOOT_MAGIC equ 0x1BADB002
MULTIBOOT_PAGE_ALIGN equ 1 << 0
MULTIBOOT_MEM_INFO equ 1 << 1
MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_HEADER_FLAGS)
[bits 32]
[section .init.text]
dd MULTIBOOT_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd MULTIBOOT_CHECKSUM
[global start]
[global global_multiboot_ptr_tmp]
[extern kernel_entry]
start:
	cli
	mov [global_multiboot_ptr_tmp],ebx
	mov esp,STACK_TOP
	and esp,0FFFFFFF0H
	mov ebp,0
	call kernel_entry
[section .init.data]
stack:
	times 1024 db 0
STACK_TOP equ $ - stack - 1
global_multiboot_ptr_tmp:
	dd 0