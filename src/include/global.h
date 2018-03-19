#ifndef GLOBAL_H
#define GLOBAL_H
#define SEG_DESCTYPE(x) ((x) << 0x04)
#define SEG_PRES(x) ((x) << 0x07)
#define SEG_SAVL(x) ((x) << 0x0C)
#define SEG_LONG(x) ((x) << 0x0D)
#define SEG_SIZE(x) ((x) << 0x0E)
#define SEG_GRAN(x) ((x) << 0x0F)
#define SEG_PRIV(x) (((x) & 0x03) << 0x05)
#define SEG_DATA_RD 0x00
#define SEG_DATA_RDA 0x01
#define SEG_DATA_RDWR 0x02
#define SEG_DATA_RDWRA 0x03
#define SEG_DATA_RDEXPD 0x04
#define SEG_DATA_RDEXPDA 0x05
#define SEG_DATA_RDWREXPD 0x06
#define SEG_DATA_RDWREXPDA 0x07
#define SEG_CODE_EX 0x08
#define SEG_CODE_EXA 0x09
#define SEG_CODE_EXRD 0x0A
#define SEG_CODE_EXRDA 0x0B
#define SEG_CODE_EXC 0x0C
#define SEG_CODE_EXCA 0x0D
#define SEG_CODE_EXRDC 0x0E
#define SEG_CODE_EXRDCA 0x0F
#define GDT_CODE_PL0 (SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_CODE_EXRD)
#define GDT_DATA_PL0 (SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_DATA_RDWR)
#define GDT_CODE_PL3 (SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_CODE_EXRD)
#define GDT_DATA_PL3 (SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_DATA_RDWR)
#include "stddef.h"
struct gdt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;
typedef uint64_t gdt_entry_t;
void init_gdt();
void flush_gdt(gdt_entry_t ptr);
#endif // GLOBAL_H
