#include "keyboard.h"
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b',
    '\t',
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/',0,
    '*',
    0,
    ' ',0,0,
    0,0,0,
	0,0,0,
	0,0,0,
    0,0,0,
    0,0,'-',
    0,0,0,
    '+',0,0,
    0,0,0,
    0,0,0,
    0,0,0,
};
void keyboard_handler(Registers *r) {
    unsigned char scancode;
    scancode = inb(0x60);
    if (scancode & 0x80) {}
    else { putchar(kbdus[scancode]); }
}
void keyboard_install() { irq_install_handler(1, keyboard_handler); }