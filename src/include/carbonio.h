#ifndef CARBONIO_H
#define CARBONIO_H
static int x,y;
static volatile unsigned char *video;
static void clear(void);
static void itoa(char *buffer,int base,int digit);
static void putchar(char c);
void printf(const char *format,...);
#endif // CARBONIO_H
