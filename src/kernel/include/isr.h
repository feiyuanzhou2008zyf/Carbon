#ifndef ISR_H
#define ISR_H
struct registers {
	unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};
typedef struct registers Registers;
extern void isrs_install();
#endif // ISR_H