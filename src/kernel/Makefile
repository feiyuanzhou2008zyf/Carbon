CC=gcc
ASM=nasm
LD=ld
CFLAGS=-Wall -O -m32 -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -fno-stack-protector -nostdinc -Iinclude/ -c -o
ASMFLAGS=-f elf32 -o
LDFLAGS=-T link.ld -o ../build/kernel.elf
DEBUG_CFLAGS=-g -Wall -O -m32 -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-builtin -fno-stack-protector -nostdinc -Iinclude/ -c -o
DEBUG_ASMFLAGS=-gstabs -f elf32 -o
all:
	$(CC) $(CFLAGS) ../build/main.o main.c
	$(CC) $(CFLAGS) ../build/gdt.o gdt/gdt.c
	$(LD) $(LDFLAGS) ../build/*.o
.PHONY: debug
debug:
	$(CC) $(DEBUG_CFLAGS) ../build/main.o main.c
	$(CC) $(DEBUG_CFLAGS) ../build/gdt.o gdt.c
	$(LD) $(LDFLAGS) ../build/*.o
