ASM=nasm
ASMFLAGS=-f elf32
DEBUG_ASMFLAGS=-gstabs -f elf32
all:
	$(ASM) $(ASMFLAGS) boot.asm -o ../build/boot.o
.PHONY: debug
debug:
	$(ASM) $(DEBUG_ASMFLAGS) boot.asm -o ../build/boot.o
