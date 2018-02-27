#ifndef SYSTEM_H
#define SYSTEM_H
#define CHECK_FLAG(flags,bit) ((flags) & (1 << (bit)))
#define COLUMNS 80
#define LINES 24
#define ATTRIBUTE 0xF0
#define VIDEO 0xB8000
extern void init();
#endif // SYSTEM_H
