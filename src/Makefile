ASM=nasm
ASMFLAGS=-f elf -o
ASM_DEBUG=-gstabs -f elf -o
CC=gcc
CFLAGS=-m32 -fno-builtin -fno-stack-protector -fnostdlib -Iinclude/ -c -o
C_DEBUG=-g -m32 -fno-builtin -fno-stack-protector -fnostdlib -Iinclude/ -c -o
LD=ld
LDFLAGS=-m elf_i386 -T link.ld -o
OUT=build
INCLUDE=include/
export ASM ASMFLAGS CC CFLAGS C_DEBUG ASM_DEBUG INCLUDE
all:
	@echo "Compiling the kernel source..."
	test -d $(OUT) || mkdir $(OUT)
	make -C boot
	# $(LD) $(LDFLAGS) $(OUT)/kernel $(OUT)/*.o
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
	qemu-system-i386 -s -S -fda $(OUT)/Carbon.img -boot a
.PHONY: run
run:
	qemu-system-i386 -fda $(OUT)/Carbon.img -boot a
.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	rm -rf $(OUT)/*
