#ifndef INIT8259A_H
#define INIT8259A_H
#define PIC_M_CTRL 0x20
#define PIC_M_DATA 0x21
#define PIC_S_CTRL 0xa0
#define PIC_S_DATA 0xa1
void init_pic();
#endif // INIT8259A_H