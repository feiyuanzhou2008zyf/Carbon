#ifndef CARBON_ASM_H
#define CARBON_ASM_H
#include "stddef.h"
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
#endif // CARBON_ASM_H