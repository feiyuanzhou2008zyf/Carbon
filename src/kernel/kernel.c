#include "gdt.h"
#define CHECK_FLAG(flags,bit) ((flags) & (1 << (bit)))
#define COLUMNS 80
#define LINES 24
#define ATTRIBUTE 0xF4
#define VIDEO 0xB8000
static int xpos,ypos;
static volatile unsigned char *video;
static void clear(void);
static void itoa(char *buffer,int base,int d);
static void putchar(char c);
void printf(const char *format,...);
void init() {
    init_gdt();
}
void kernel_main(void) {
    char *string = "Here is multiboot kernel";
    char *gdt_done = "GDT is loaded";
    video = (unsigned char *)VIDEO;
    clear();
    printf("%s\n",string);
    init();
    printf("%s\n",gdt_done);
    return;
}
static void clear(void) {
    int i;
    for (i = 0;i < COLUMNS * LINES * 2;i++)
        *(video + i) = 0xFF;
    xpos = 0;
    ypos = 0;
}
static void itoa(char *buffer,int base,int d) {
    char *p = buffer;
    char *p1,*p2;
    unsigned long ud = d;
    int divisor = 10;
    if (base == 'd' && d < 0) {
        *p++ = '-';
        buffer++;
        ud = -d;
    }
    else if (base == 'x')
        divisor = 16;
    do {
        int reminder = ud % divisor;
        *p++ = (reminder < 10) ? reminder + '0' : reminder + 'a' - 10;
    } while (ud /= divisor);
    *p = 0;
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}
static void putchar(char c) {
    if (c == '\n' || c == '\r') {
        newline:
        xpos = 0;
        ypos++;
        if (ypos >= LINES)
            ypos = 0;
        return;
    }
    *(video + (xpos + ypos * COLUMNS) * 2) = c;
    *(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;
    xpos++;
    if (xpos >= COLUMNS)
        goto newline;
}
void printf(const char *format,...) {
    char **arg = (char **)&format;
    int c;
    char buffer[20];
    arg++;
    while ((c = *format++) != 0) {
        if (c != '%')
            putchar(c);
        else {
            char *p;
            c = *format++;
            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    itoa(buffer,c,*((int *)arg++));
                    p = buffer;
                    goto make_string;
                    break;
                case 's':
                    p = *arg++;
                    if (!p)
                        p = "(null)";
                    make_string:
                    while (*p)
                        putchar(*p++);
                    break;
                default:
                    putchar(*((int *)arg++));
                    break;
            }
        }
    }
}
