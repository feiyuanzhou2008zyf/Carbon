#ifndef SYSTEM_H
#define SYSTEM_H
struct registers {
    unsigned int gs,fs,es,ds;
    unsigned int esi,edi,esp,ebp,edx,ecx,ebx,eax;
    unsigned int interrupt_no,error_code;
    unsigned int eip,cs,eflags,useresp,ss;
};
extern unsigned char *memcpy(unsigned char *dest,const unsigned char *src,int count);
extern unsigned char *memset(unsigned char *dest,unsigned char value,int count);
extern unsigned short *memsetw(unsigned short *dest,unsigned short value,int count);
extern int strlen(const char *string);
extern unsigned char inb(unsigned short port);
extern void outb(unsigned short port,unsigned char data);
extern void clear();
extern void putchar(unsigned char c);
extern void puts(unsigned char *text);
extern void setTextColor(unsigned char fontColor,unsigned char backColor);
extern void init_video();
#endif // SYSTEM_H
