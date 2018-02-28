#ifndef IRQ_H
#define IRQ_H
extern void irq_uninstall_handler(int irq);
extern void irq_remap(void);
extern void irq_install();
#endif // IRQ_H