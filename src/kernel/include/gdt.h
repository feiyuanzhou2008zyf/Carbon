#ifndef GDT_H
#define GDT_H
#include "type.h"
struct gdt_entry {
    ushort limit_low;
    ushort base_low;
    uchar base_middle;
    uchar access;
    uchar gran;
    uchar base_high;
}__attribute__((packed));
struct gdt_ptr {
    ushort limit;
    uint base;
}__attribute__((packed));
struct gdt_entry gdt[3];
struct gdt_ptr gptr;
extern void gdt_flush();
void init_gdt();
void set_gdt_gate(int num,ulong base,ulong limit,uchar access,uchar gran);
#endif // GDT_H
