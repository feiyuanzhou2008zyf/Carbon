all:
	test -d build || mkdir build
	make -C boot
	make -C kernel
.PHONY: debug
debug:
	make -C boot debug
	make -C kernel debug
.PHONY: clean
clean:
	rm -rf build/*
.PHONY: run
run:
	qemu-system-i386 -kernel build/kernel.elf
.PHONY: debug-run
debug-run:
	qemu-system-i386 -s -S -kernel build/kernel-debug.elf
