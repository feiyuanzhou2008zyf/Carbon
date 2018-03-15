; Constant value
CODE_SELECTOR equ 0x8
DATA_SECECTOR equ 0x10
; Using 4 bit align
align 4
; Global function and extern pointer
global flush_gdt
global load_idt
extern gdt_pointer
extern idt_pointer
; void flush_gdt(uint32_t)
flush_gdt:
	lgdt [gdt_pointer]
	mov ax,DATA_SECECTOR
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	jmp CODE_SELECTOR:flush
; Subroutine for flush_gdt
flush:
	ret
; Load interrupt pointer
load_idt:
	lidt [idt_pointer]
	ret
; Interrupt service routines
; Exception 0 to 31 definition
%macro interrupt_fault 1
; Declare interrupt handler,call from C code
global interrupt_handler%1
interrupt_handler%1:
	cli
	%if %1 != 17 && %1 != 30 && (%1 < 8 || %1 > 14)
		push 0
	%endif
	push %1
	jmp _isr_stub
%endmacro
; Declare function
%assign i 0
%rep 32
	interrupt_fault i
	%assign i i + 1
%endrep
; Interrupt request: 32 to 47
%macro interrupt_request 1
; Declare interrupt request,call from C code
global interrupt_requests%1
interrupt_requests%1:
	cli
	push 0
	push %1 + 32
	jmp _isr_stub
%endmacro
; Declare request
%assign i 0
%rep 16
	interrupt_request i
	%assign i i + 1
%endrep
; System call
; Declare function
global sys_call
sys_call:
	push 0
	push 0x80
	jmp _isr_stub
; if interrupt is unknown
global isr_unknown
isr_unknown:
	cli
	push 0
	push 255
	jmp _isr_stub
; Interrupt handler function
global isr_stub_ret
extern isr_stub
_isr_stub:
	pusha
    push ds
    push es
    push fs
    push gs
    mov ax,DATA_SECECTOR
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    mov eax,esp
    push eax
    mov eax,isr_stub
    call eax
    pop eax
; Recover context
_isr_stub_ret:
	pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp,8
    iret