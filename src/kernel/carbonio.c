#include "carbonio.h"
#include "system.h"
static void clear(void) {
	for (int i = 0;i < COLUMNS * LINES * 2;i++)
		*(video + i) = 0xFF;
	x = 0;
	y = 0;
}
static void itoa(char *buffer,int base,int digit) {}
static void putchar(char c) {}
static void printf(const char *format) {}
