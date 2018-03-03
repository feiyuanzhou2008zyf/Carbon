#ifndef STDIO_H
#define STDIO_H
#include "console.h"
#include "varg.h"
void printk(const char *format,...);
void printk_color(real_color_t back,real_color_t front,const char *format,...);
#endif // STDIO_H