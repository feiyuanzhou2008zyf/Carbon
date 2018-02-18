#ifndef CARBONIO_H
#define CARBONIO_H
extern static int x,y;
extern static volatile unsigned char *video;
extern static void clear(void);
extern static void itoa(char *buffer,int base,int digit);
extern static void putchar(char c);
extern void printf(const char *format,...);
#endif // CARBONIO_H
