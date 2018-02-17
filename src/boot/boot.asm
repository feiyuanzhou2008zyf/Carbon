bits 32
global start
extern kernel_main
start:
    mov esp,sys_stack
    jmp halt
align 4
multiboot:
    MULTIBOOT_PAGE_ALIGN equ 1 << 0
    MULTIBOOT_MEMORY_INFO equ 1 << 1
    MULTIBOOT_AOUT_KLUDGE equ 1 << 16
    MULTIBOOT_HEADER_MAGIC equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    extern code,bss,end
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd multiboot
    dd code
    dd bss
    dd end
    dd start
halt:
    call kernel_main
    jmp $
section .bss
    resb 8192
sys_stack:
    
global gdt_flush
extern gptr
gdt_flush:
    lgdt [gptr]
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    jmp 0x08:flush
flush:
    ret
global idt_load
extern iptr
idt_load:
    lidt [iptr]
    ret
