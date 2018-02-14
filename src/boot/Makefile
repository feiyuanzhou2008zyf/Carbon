all:
	nasm -f elf32 bootstrap.asm -o ../build/bootstrap.o
.PHONY: debug
debug:
	nasm -gstabs -f elf32 bootstrap.asm -o ../build/bootstrap.o
