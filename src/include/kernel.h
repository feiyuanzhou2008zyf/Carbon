#ifndef KERNEL_H
#define KERNEL_H
#include "common.h"
#include "debug.h"
#include "elf.h"
#include "multiboot.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"
#include "varg.h"
#include "init8259a.h"
#include "global.h"
void kernel_entry();
void kernel_main();
#endif // KERNEL_H
