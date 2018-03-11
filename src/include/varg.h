#ifndef VARG_H
#define VARG_H
#include "stddef.h"
#define va_list char *
#define va_start(p,first) (p = (va_list)&first + sizeof(first))
#define va_arg(p,next) (*(next *)((p += sizeof(next)) - sizeof(next)))
#define va_end(p) (p = (va_list)NULL)
#endif // VARG_H
