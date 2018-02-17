global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
; for error code 0-7,9,15-31
%macro VECTOR_FIRST 1
isr%1:
    cli
    push 0
    push %1
    jmp isr_common_stub
%endmacro
; for error code 8,10-14
%macro VECTOR_SECOND 1
isr%1:
    cli
    push %1
    jmp isr_common_stub
%endmacro
VECTOR_FIRST 0
VECTOR_FIRST 1
VECTOR_FIRST 2
VECTOR_FIRST 3
VECTOR_FIRST 4
VECTOR_FIRST 5
VECTOR_FIRST 6
VECTOR_FIRST 7
VECTOR_FIRST 9
VECTOR_FIRST 15
VECTOR_FIRST 16
VECTOR_FIRST 17
VECTOR_FIRST 18
VECTOR_FIRST 19
VECTOR_FIRST 20
VECTOR_FIRST 21
VECTOR_FIRST 22
VECTOR_FIRST 23
VECTOR_FIRST 24
VECTOR_FIRST 25
VECTOR_FIRST 26
VECTOR_FIRST 27
VECTOR_FIRST 28
VECTOR_FIRST 29
VECTOR_FIRST 30
VECTOR_FIRST 31
VECTOR_SECOND 8
VECTOR_SECOND 10
VECTOR_SECOND 11
VECTOR_SECOND 12
VECTOR_SECOND 13
VECTOR_SECOND 14
extern fault_handler
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov eax,esp
    push eax
    mov eax,fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp,8
    iret
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
%macro IRQ 1
irq%1:
    cli
    push byte 0
    push byte 32 + %1
    jmp irq_common_stub
%endmacro
IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15
extern irq_handler
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov eax,esp
    push eax
    mov eax,irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp,8
    iret
