#ifndef TIMER_H
#define TIMER_H
#include "bio.h"
#include "isr.h"
#include "io.h"
extern void timer_handler(Registers *r);
extern void timer_install();
extern void timer_wait(int ticks);
#endif // TIMER_H