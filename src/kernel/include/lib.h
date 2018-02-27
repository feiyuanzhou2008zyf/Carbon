#ifndef LIB_H
#define LIB_H
#include "types.h"
void *memcpy(void *dest,const void *src,size_t count);
void *memset(void *dest,char value,size_t count);
unsigned short *memsetw(unsigned short *dest,unsigned short value,size_t count);
size_t strlen(const char *string);
#endif // LIB_H
