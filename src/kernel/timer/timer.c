#include "timer.h"
#include "irq.h"
#include "isr.h"
#include "io.h"
int timer_ticks = 0;
void timer_handler(Registers *r) {
	timer_ticks++;
	if (timer_ticks % 18 == 0)
		printf("One second passed\n");
}
void timer_install() { irq_install_handler(0,timer_handler); }
void timer_wait(int ticks) {
	unsigned long eticks;
	eticks = timer_ticks + ticks;
	while (timer_ticks < eticks);
}
