global asm_inthandler0
global asm_inthandler1
global asm_inthandler2
global asm_inthandler3
global asm_inthandler4
global asm_inthandler5
global asm_inthandler6
global asm_inthandler7
global asm_inthandler8
global asm_inthandler9
global asm_inthandler10
global asm_inthandler11
global asm_inthandler12
global asm_inthandler13
global asm_inthandler14
global asm_inthandler15
global asm_inthandler16
global asm_inthandler17
global asm_inthandler18
global asm_inthandler19
global asm_inthandler20
global asm_inthandler21
global asm_inthandler22
global asm_inthandler23
global asm_inthandler24
global asm_inthandler25
global asm_inthandler26
global asm_inthandler27
global asm_inthandler28
global asm_inthandler29
global asm_inthandler30
global asm_inthandler31
global asm_inthandler32
global asm_inthandler33
extern inthandler20
extern inthandler21
extern inthandler_other
[bits 32]
; Normal interrupt
asm_inthandler0:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler1:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler2:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler3:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler4:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler5:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler6:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler7:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler8:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler9:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler10:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler11:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler12:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler13:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler14:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler15:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler16:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler17:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler18:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler19:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler20:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler21:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler22:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler23:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler24:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler25:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler26:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler27:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler28:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler29:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler30:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
asm_inthandler31:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler_other
	pop eax
	popad
	pop ds
	pop es
	iret
; Timer interrupt
asm_inthandler32:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler20
	pop eax
	popad
	pop ds
	pop es
	iret
; Keyboard interrupt
asm_inthandlr33:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler21
	pop eax
	popad
	pop ds
	pop es
	iret