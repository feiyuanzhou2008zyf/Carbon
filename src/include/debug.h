#ifndef DEBUG_H
#define DEBUG_H
#include "stddef.h"
#include "varg.h"
#include "elf.h"
#include "stdio.h"
#ifndef NDEBUG
	#define assert(expr) (void)((expr) || ((_assert(#expr,__FILE__,__LINE__),0)))
#else
	#define assert(expr) ((void)0)
#endif // NDEBUG
void _assert(void *exp,void *file,unsigned int line);
void init_debug();
void panic(const char *msg);
void print_cur_status();
#endif // DEBUG_H
