#ifndef PAGE_H
#define PAGE_H
#include "stddef.h"
#include "common.h"
#include "stdio.h"
#define PAGE_OFFSET 0xC0000000
#define PAGE_IN_MEMORY 0x1
#define PAGE_WRITE_READ 0x2
#define PAGE_IS_USER 0x4
#define PAGE_IS_THROUGH 0x8
#define PAGE_IS_NOBUFFER 0x10
#define PAGE_IS_ACCESS 0x20
#define PAGE_IS_WRITE 0x40
#define PAGE_IS_4K 0x0
#define PAGE_IS_GLOBAL 0x100
#define PAGE_NOT_IN_MEMORY 0x0
#define PAGE_IS_READ 0x0
#define PAGE_IS_SYSTEM 0x0
#define PAGE_IS_BACK 0x0
#define PAGE_IS_BUFFER 0x0
#define PAGE_IS_NOT_ACCESS 0x0
#define PAGE_IS_NOT_WRITE 0x0
#define PAGE_IS_NOT_4K 0x80
#define PAGE_IS_NOT_GLOBAL 0x0
void alloc_page_table(const uint32_t page_dir_base,int index,uint32_t page_tpl_base,int attr);
void alloc_page(const uint32_t page_tpl_base,int index,uint32_t page_address,int attr);
void page_running(const uint32_t page_dir_base);
void page_end();
uint32_t compute_page(uint32_t memory_size);
#endif // PAGE_H