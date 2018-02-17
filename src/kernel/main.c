#include "system.h"
unsigned char *memcpy(unsigned char *dest,unsigned char *src,int count) {}
unsigned char *memset(unsigned char *dest,unsigned char value,int count) {}
unsigned short *memsetw(unsigned short *dest,unsigned short value,int count) {}
int strlen(const char *string) {}
unsigned char inb(unsigned short port) {
    unsigned char rv;
    asm volatile ("inb %1,%0" : "=a"(rv) : "dN"(port));
    return rv;
}
void outb(unsigned short port,unsigned char data) { asm volatile ("outb %1,%0" : : "dN"(port),"a"(data)); }
void kernel_main() { for (;;); }
