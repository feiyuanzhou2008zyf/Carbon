#ifndef DEBUG_H
#define DEBUG_H
#include "console.h"
#include "varg.h"
#include "elf.h"
#include "stdio.h"
#define PANIC(...) panic(__FILE__,__LINE__,__FUNC__,__VA_ARGS__)
#define static_assert(x) switch (x) { case 0: case x: ; }
#ifdef NDEBUG
	#define assert(CONDITION) ((void)0)
#else
	#define assert(CONDITION) if (CONDITION) {} else { PANIC(CONDITION); }
#endif // NDEBUG
void init_debug();
void panic(const char *msg);
void print_cur_status();
void panic(char *filename,int line,const char *func,const char *condition) {
	printk("\n\n\nError!\n");
	printk("Filename: %s\n,Line: %d\n,Function: %s\n,Condition: %s\n",filename,line,(char *)func,(char *)condition);
	while (1) { asm volatile ("hlt"); }
}
#endif // DEBUG_H