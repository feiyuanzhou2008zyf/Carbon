#include "carbonio.h"
#include "system.h"
void init() {}
void kernel_main() {
	char *hello = "Hello World,Here kernel!";
	video = (unsigned char *)VIDEO;
	clear();
	printf("%s\n",hello);
	init();
	return;
}
static void clear(void) {
	for (int i = 0;i < COLUMNS * LINES * 2;i++)
		*(video + i) = 0xFF;
	x = 0;
	y = 0;
}
static void itoa(char *buffer,int base,int digit) {
	char *p = buffer;
	char *p1,*p2;
	unsigned long udigit = digit;
	int divisor = 10;
	if (base == 'd' && digit < 0) {
		*p++ = '-';
		buffer++;
		udigit = -digit;
	}
	else if (base = 'x')
		divisor = 16;
	do {
		int reminder = udigit % divisor;
		*p++ = (reminder < 10) ? reminder + '0' : reminder + 'a' - 10;
	} while (udigit /= divisor);
	*p = 0;
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}
static void putchar(char c) {
	if (c == '\n' || c == '\r') {
		newline:
		x = 0;
		y++;
		if (y >= LINES)
			y = 0;
		return;
	}
	*(video + (x + y * COLUMNS) * 2) = c;
	*(video + (x + y * COLUMNS) * 2 + 1) = ATTRIBUTE;
	x++;
	if (x >= COLUMNS)
		goto newline;
}
void printf(const char *format,...) {
	char **args = (char **)&format;
	int c;
	char buffer[20];
	args++;
	while ((c = *format++) != 0) {
		if (c != '%')
			putchar(c);
		else {
			char *p;
			c = *format++;
			switch (c) {
				case 'd':case 'u':case 'x':
					itoa(buffer,c,*((int *)args++));
					p = buffer;
					goto make_string;
					break;
				case 's':
					p = *args++;
					if (!p)
						p = "(null)";
					make_string:
					while (*p)
						putchar(*p++);
					break;
				default:
					putchar(*((int *)args++));
					break;
			}
		}
	}
}
