ASM=nasm
ASMFLAGS=-f elf -o
ASM_DEBUG=-gstabs -f elf -o
CC=gcc
CFLAGS=-m32 -fno-builtin -fno-stack-protector -nostdlib -c -o
C_DEBUG=-g -m32 -fno-builtin -fno-stack-protector -nostdlib -c -o
LD=ld
LDFLAGS=-m elf_i386 -T scripts/link.ld -o
OUT=build
export ASM ASMFLAGS CC CFLAGS C_DEBUG ASM_DEBUG
all:
	@echo "Compiling the kernel source..."
	test -d $(OUT) || mkdir $(OUT)
	make -C boot
	make -C kernel
	$(LD) $(LDFLAGS) $(OUT)/kernel $(OUT)/*.o
	make update
.PHONY: update
update:
	@echo "Creating mount point"
	test -d /mnt/Carbon || sudo mkdir -p /mnt/Carbon
	@echo "Updating kernel image"
	cp boot.img $(OUT)
	sudo mount $(OUT)/boot.img /mnt/Carbon
	sudo cp $(OUT)/kernel /mnt/Carbon
	sudo umount /mnt/Carbon
	mv $(OUT)/boot.img $(OUT)/Carbon.img
	@echo "Recover environment"
	sudo rm -rf /mnt/Carbon
.PHONY: debug
debug:
	make -C boot debug
	make -C kernel debug
	$(LD) $(LDFLAGS) $(OUT)/kernel $(OUT)/*.o
	make update
	bochsgdb -f bochsrc-debug.bxrc
.PHONY: run
run:
	bochsdbg -f bochsrc.bxrc
.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	rm -rf $(OUT)/*
