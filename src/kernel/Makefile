OUT=../build
all:
	$(ASM) $(ASMFLAGS) $(OUT)/global_asm.o global/global.asm
	$(ASM) $(ASMFLAGS) $(OUT)/interrupt_asm.o interrupt/interrupt.asm
	$(CC) $(CFLAGS) $(OUT)/global.o global/global.c
	$(CC) $(CFLAGS) $(OUT)/interrupt.o interrupt/interrupt.c
	$(CC) $(CFLAGS) $(OUT)/lib.o lib.c
	$(CC) $(CFLAGS) $(OUT)/system.o system.c
.PHONY: debug
debug:
	$(ASM) $(ASM_DEBUG) $(OUT)/global_asm_debug.o global/global.asm
	$(ASM) $(ASM_DEBUG) $(OUT)/interrupt_asm_debug.o interrupt/interrupt.asm
	$(CC) $(C_DEBUG) $(OUT)/global_debug.o global/global.c
	$(CC) $(C_DEBUG) $(OUT)/interrupt_debug.o interrupt/interrupt.c
	$(CC) $(C_DEBUG) $(OUT)/system_debug.o system.c
	$(CC) $(C_DEBUG) $(OUT)/lib_debug.o lib.c
