all:
	nasm -f elf32 gdt/gdt.asm -o ../build/gdt_asm.o
	gcc -m32 -c kernel.c -o ../build/kernel.o -fno-builtin -fno-stack-protector -Iinclude/
	gcc -m32 -c gdt/gdt.c -o ../build/gdt.o -fno-builtin -fno-stack-protector -Iinclude/
	ld -m elf_i386 -T link.ld -o ../build/kernel.elf ../build/*.o
.PHONY: debug
debug:
	nasm -gstabs -f elf32 gdt/gdt.asm -o ../build/gdt_asm.o
	gcc -g -m32 -c kernel.c -o ../build/kernel.o -fno-builtin -fno-stack-protector -Iinclude/
	gcc -g -m32 -c gdt/gdt.c -o ../build/gdt.o -fno-builtin -fno-stack-protector -Iinclude/
	ld -m elf_i386 -T link.ld -o ../build/kernel-debug.elf ../build/*.o
