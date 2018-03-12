#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include "pagemanager.h"
#include "stdio.h"
#include "stddef.h"
void set_page_on_paging(uint32_t virtual_page_address,uint32_t physical_page_address);
//修改过的函数
void init_memory_manager(uint32_t mmap_addr,uint32_t mmap_length,uint32_t kernel_entry,uint32_t kernel_end);
void *kmalloc(int size);
void free(void *ptr,int size);
void *merge(int * sizesum,const void *ptr1,int size1,const void *ptr2,int size2);
void print_info();
void release(uint32_t virtual_page_address);
void release_page(uint32_t virtual_page_address,int32_t count);
uint32_t query_virtual_address(uint32_t physical_page_address);
uint32_t query_physical_address(uint32_t virtual_page_address);
#endif // MEMORY_MANAGER_H