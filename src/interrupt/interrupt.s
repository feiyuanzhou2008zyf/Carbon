[bits 32]
; if click exception,the cpu push the error code,do nothing
%define ERROR_CODE nop
; else push 0
%define ZERO push 0
; Exception handler function table
extern idt_handler_table
[section .data]
; Interrupt entry function table
global interrupt_entry_table
interrupt_entry_table:
; define a macro,register the handler function table
%macro VECTOR 2
interrupt_handler_%1_entry:
	%2
	push ds
	push es
	push fs
	push gs
	pushad
	mov al,0x20
	out 0xa0,al
	out 0x20,al
	push %1
	call [idt_handler_table + %1 * 4]
	jmp interrupt_handler_entry_end
[section .data]
	dd interrupt_handler_%1_entry
%endmacro
; recover context
[section .text]
global interrupt_handler_entry_end
interrupt_handler_entry_end:
	add esp,4
	popad
	pop gs
	pop fs
	pop es
	pop ds
	add esp,4
	iretd
; interrupt vector
VECTOR 0x00,ZERO
VECTOR 0x01,ZERO
VECTOR 0x02,ZERO
VECTOR 0x03,ZERO 
VECTOR 0x04,ZERO
VECTOR 0x05,ZERO
VECTOR 0x06,ZERO
VECTOR 0x07,ZERO 
VECTOR 0x08,ERROR_CODE
VECTOR 0x09,ZERO
VECTOR 0x0a,ERROR_CODE
VECTOR 0x0b,ERROR_CODE 
VECTOR 0x0c,ZERO
VECTOR 0x0d,ERROR_CODE
VECTOR 0x0e,ERROR_CODE
VECTOR 0x0f,ZERO 
VECTOR 0x10,ZERO
VECTOR 0x11,ERROR_CODE
VECTOR 0x12,ZERO
VECTOR 0x13,ZERO 
VECTOR 0x14,ZERO
VECTOR 0x15,ZERO
VECTOR 0x16,ZERO
VECTOR 0x17,ZERO 
VECTOR 0x18,ERROR_CODE
VECTOR 0x19,ZERO
VECTOR 0x1a,ERROR_CODE
VECTOR 0x1b,ERROR_CODE 
VECTOR 0x1c,ZERO
VECTOR 0x1d,ERROR_CODE
VECTOR 0x1e,ERROR_CODE
VECTOR 0x1f,ZERO 
VECTOR 0x20,ZERO ; Timer
VECTOR 0x21,ZERO ; Keyboard
VECTOR 0x22,ZERO ; cascade
VECTOR 0x23,ZERO ; serial 2 entry
VECTOR 0x24,ZERO ; serial 1 entry
VECTOR 0x25,ZERO ; parallel 2 entry
VECTOR 0x26,ZERO ; floppy entry
VECTOR 0x27,ZERO ; parallel 1 entry
VECTOR 0x28,ZERO ; 
VECTOR 0x29,ZERO ; redirect
VECTOR 0x2a,ZERO ; keep
VECTOR 0x2b,ZERO ; keep
VECTOR 0x2c,ZERO ; PS/2 mouse
VECTOR 0x2d,ZERO ; FPU exception
VECTOR 0x2e,ZERO ; Hard disk
VECTOR 0x2f,ZERO ; keep
; 0x80 Exception,for system call using
[bits 32]
extern syscall_table
[section .text]
global syscall_handler
syscall_handler:
	push 0
	push ds
	push es
	push fs
	push gs
	pushad
	push 0x80
	push edx
	push ecx
	push ebx
	call [syscall_table + eax * 4]
	add esp,12
	mov [esp + 8 * 4],eax
	jmp interrupt_handler_entry_end