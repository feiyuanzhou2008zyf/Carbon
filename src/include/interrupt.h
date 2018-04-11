#ifndef INTERRUPT_H
#define INTERRUPT_H
void divide_error();
void single_step_exception();
void nmi();
void breakpoint_exception();
void overflow();
void bounds_check();
void inval_opcode();
void copr_not_available();
void double_fault();
void copr_seg_overrun();
void inval_tss();
void segment_not_present();
void stack_exception();
void general_protection();
void page_fault();
void copr_error();
void interrupt_handler();
void keyboard_interrupt(int irq);
void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags);
void spurious_irq(int irq);
void interrupt_request00();
void interrupt_request01();
void interrupt_request02();
void interrupt_request03();
void interrupt_request04();
void interrupt_request05();
void interrupt_request06();
void interrupt_request07();
void interrupt_request08();
void interrupt_request09();
void interrupt_request10();
void interrupt_request11();
void interrupt_request12();
void interrupt_request13();
void interrupt_request14();
void interrupt_request15();
#endif // INTERRUPT_H