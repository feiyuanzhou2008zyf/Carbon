OUTPUT_FORMAT("binary")
ENTRY(start)
physic=0x00100000;
SECTIONS
{
    .text physic : AT(physic) {
        code = .;
        *(.text)
        *(.rodata)
        . = ALIGN(4096);
    }
    .data : AT(physic + (data - code)) {
        data = .;
        *(.data)
        . = ALIGN(4096);
    }
    .bss : AT(physic + (bss - code)) {
        bss = .;
        *(.bss)
        . = ALIGN(4096);
    }
    end = .;
}
