#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "io.h"
#include "bio.h"
#include "irq.h"
extern void keyboard_handler(Registers *r);
extern void keyboard_install();
#endif // KEYBOARD_H