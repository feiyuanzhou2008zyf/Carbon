#include "bio.h"
unsigned char inb(unsigned short port) {
	unsigned char return_value;
    asm volatile("inb %1, %0" : "=a" (return_value) : "dN" (port));
    return return_value;
}
void outb(unsigned short port,unsigned char data) {
	asm volatile("outb %1, %0" : : "dN" (port), "a" (data));
}