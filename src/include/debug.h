#ifndef DEBUG_H
#define DEBUG_H
#include "stdio.h"
#include "stddef.h"
#include "stdarg.h"
#include "stdelf.h"
#ifndef NDEBUG
	#define assert(expr) (void)((expr) || ((_assert(#expr,__FILE__,__LINE__),0)))
#else
	#define assert(expr) ((void)0)
#endif // NDEBUG
#ifndef static_assert
	#define static_assert(expr) ((void)sizeof(char[1 - 2 * !!!(expr)]))
#endif // static_assert
#ifndef offsetof
	#define offsetof(type,number) ((size_t) & ((type*)0 -> number))
#endif // offsetof
#ifndef container_of
	#define container_of(ptr,type,member) ((type *)((char *)(ptr) - offsetof(type,member)))
#endif // container_of
#ifndef array_size
	#define array_size(arr) (sizeof(arr) / sizeof((arr)[0]) + sizeof(typeof(int[1 - 2 * !!__builtin_types_compatible_p(typeof(arr),typeof(&arr[0]))])) * 0)
#endif // array_size
void _assert(void *exp, void *file, unsigned int line);
void init_debug();
void panic(const char *msg);
void print_stack_trace();
void print_cur_status();
#endif // DEBUG_H
