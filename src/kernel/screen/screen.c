#include "system.h"
unsigned short *textMemoryPointer;
int attribute = 0x0F;
int x = 0,y = 0;
void scroll(void) {
    unsigned blank,temp;
    blank = 0x20 | (attribute << 8);
    if (y >= 25) {
        temp = y - 25 + 1;
        memcpy(textMemoryPointer,textMemoryPointer + temp * 80,(25 - temp) * 80 * 2);
        memsetw(textMemoryPointer + (25 - temp) * 80,blank,80);
        y = 25 - 1;
    }
}
void move_cursor(void) {
    unsigned temp;
    temp = y * 80 + x;
    outb(0x3D4,14);
    outb(0x3D5,temp >> 8);
    outb(0x3D4,15);
    outb(0x3D5,temp);
}
void clear() {
    unsigned blank;
    int i;
    blank = 0x20 | (attribute << 8);
    for (i = 0;i < 25;i++)
        memsetw(textMemoryPointer + i * 80,blank,80);
    x = 0;
    y = 0;
    move_cursor();
}
void putchar(unsigned char c) {
    unsigned short *where;
    unsigned attr = attribute << 8;
    if (c == 0x08) {
        if (x != 0)
            x--;
    }
    else if (c == 0x09) {
        x = (x + 8) & ~(8 - 1);
    }
    else if (c == '\r') {
        x = 0;
    }
    else if (c == '\n') {
        x = 0;
        y++;
    }
    else if (c == ' ') {
        where = textMemoryPointer + (y * 80 + x);
        *where = c | attr;
        x++;
    }
    if (x >= 80) {
        x = 0;
        y++;
    }
    scroll();
    move_cursor();
}
void puts(unsigned char *text) {
    int i;
    for (i = 0;i < strlen(text);i++)
        putchar(text[i]);
}
void setTextColor(unsigned char fontColor,unsigned backColor) { attribute = (backColor << 4) | (fontColor & 0x0F); }
void init_video(void) {
    textMemoryPointer = (unsigned short )0xB8000;
    clear();
}
