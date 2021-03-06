C_SOURCE=$(shell find . -name "*.c")
C_OBJECT=$(patsubst %.c,%.o,$(C_SOURCE))
S_SOURCE=$(shell find . -name "*.s")
S_OBJECT=$(patsubst %.s,%.o,$(S_SOURCE))
CC=gcc
LD=ld
ASM=nasm
CFLAGS=-c -Wall -m32 -ggdb -gstabs+ -std=gnu11 -nostdinc -fno-builtin -fno-stack-protector -Iinclude
LDFLAGS=-T script/link.ld -m elf_i386 -nostdlib
ASMFLAGS=-f elf -g -F stabs
all: $(S_OBJECT) $(C_OBJECT) link update
.c.o:
	@echo "Compiling the source..."
	$(CC) $(CFLAGS) $< -o $@
.s.o:
	@echo "Assembling the source..."
	$(ASM) $(ASMFLAGS) $<
link:
	@echo "Linking kernel..."
	$(LD) $(LDFLAGS) $(S_OBJECT) $(C_OBJECT) -o kernel.elf
	$(LD) $(LDFLAGS) $(S_OBJECT) $(C_OBJECT) -o recovery.elf
	$(LD) $(LDFLAGS) $(S_OBJECT) $(C_OBJECT) -o live.elf
.PHONY: clean
clean:
	$(RM) $(S_OBJECT) $(C_OBJECT) *.elf Carbon.img
.PHONY: update
update:
	test -d /mnt/Carbon || sudo mkdir -p /mnt/Carbon
	cp grub.img Carbon.img
	sudo mount Carbon.img /mnt/Carbon
	sudo cp kernel.elf recovery.elf live.elf /mnt/Carbon/kernel/
	sudo umount /mnt/Carbon
.PHONY: mount_image
mount_image:
	sudo mount Carbon.img /mnt/Carbon
.PHONY: umount_image
umount_image:
	sudo umount /mnt/Carbon
.PHONY: delete_mountpoint
delete_mountpoint:
	sudo rm -rf /mnt/Carbon
.PHONY: qemu
qemu:
	qemu-system-i386 -fda Carbon.img -boot a
.PHONY: bochsgdb
bochsgdb:
	bochsgdb -f tool/bochsrc-gdb.txt
.PHONY: bochsdbg
bochsdbg:
	bochsdbg -f tool/bochsrc.txt
.PHONY: debug
debug:
	qemu-system-i386 -s -S -fda Carbon.img -boot a
