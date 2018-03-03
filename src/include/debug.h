#ifndef DEBUG_H
#define DEBUG_H
#include "console.h"
#include "varg.h"
#include "elf.h"
#define assert(x, info)	\
    do { \
        if (!(x)) {	\
            panic(info); \
        } \
    } while (0)
#define static_assert(x) \
	switch (x) { case 0: case x: ; }
void init_debug();
void panic(const char *msg);
void print_cur_status();
#endif // DEBUG_H