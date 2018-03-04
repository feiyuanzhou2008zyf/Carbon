#ifndef PHYSIC_MEMORY_H
#define PHYSIC_MEMORY_H
#include "multiboot.h"
extern uint8_t kernel_start[];
extern uint8_t kernel_end[];
void show_memory_map();
#endif // PHYSIC_MEMORY_H