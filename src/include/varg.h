#ifndef VARG_H
#define VARG_H
typedef __builtin_va_list va_list;
#define va_start(ap,last) (__builtin_va_list(ap,last))
#define va_arg(ap,type) (__builtin_va_list(ap,type))
#define va_end(ap)
#endif // VARG_H