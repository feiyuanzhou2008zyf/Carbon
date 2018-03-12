#include "pagemanager.h"
void create_page_manager(page_manager_t *p,uint32_t kernel_begin_address,uint32_t kernel_size,uint32_t physical_memory_size,...) {
	uint32_t memory_page_count = compute_page(physical_memory_size);
	uint32_t memory_bitmap_size = memory_page_count / 8;
	printk("page count:%x",memory_bitmap_size);
	uint32_t address_begin = kernel_begin_address + kernel_size;
	
	if(address_begin / (4 * 1024) !=0 ) { address_begin = address_begin + (4 * 1024 - address_begin % (4 * 1024)); }
	
	memory_pool_t *ptr;
	ptr = &(p -> physical_memory_pool);
	create_memory_pool(ptr,address_begin,0,memory_bitmap_size,PHYSIC);
	set_memory_pool(ptr,kernel_begin_address,compute_page(kernel_size),1);
	set_memory_pool(ptr,address_begin,compute_page(memory_bitmap_size),1);
	uint32_t pbl = query_unuse_memory_one(ptr,0);
	set_memory_pool_one(ptr,pbl,1);
	p -> pbl_address = pbl;
	int i;
	for (i = 0;i < 128;i++){ p -> bitmap[i]=0; }
	p -> pbl_bitmap.address = (uint32_t)(&(p -> bitmap));
	p -> pbl_bitmap.size = 1024;
	for(i = kernel_begin_address;i < kernel_size + memory_bitmap_size;i=i + 4096) { set_page(p,i,i); }
	printk("        -----1-----  \n");
	va_list args;
	va_start(args,physical_memory_size);
	uint32_t *tmp1,*tmp2;
	for(	tmp1 = (uint32_t*)args,va_arg(args,uint32_t),tmp2 =(uint32_t*)args;
			*tmp1 != 0 && *tmp2!=0;
			va_arg(args,uint32_t),tmp1 = (uint32_t*)args,va_arg(args,uint32_t),tmp2 =(uint32_t*)args) {
				int count = (*tmp2 - *tmp1) /(4*1024);
		set_memory_pool(ptr,*tmp1,count,1);
		for(i = *tmp1;i < *tmp2;i=i + 4096) { set_page(p,i,i); }
	}
	va_end(args);

	set_page(p,p -> pbl_address,p -> pbl_address);
}
void set_page(page_manager_t *p,uint32_t virtual_page_address,uint32_t physical_page_address) {
	int pbl_index,ptl_index;
	pbl_index = (virtual_page_address & 0xFFFFF000) / (4 * 1024 * 1024);
	ptl_index = (virtual_page_address & 0x003FFFFF) / (4 * 1024);
	uint32_t ptl_address;
	memory_pool_t *ptr = &(p -> physical_memory_pool);
	if (query_bitmap(&(p -> pbl_bitmap),pbl_index) == 0) {
		set_bitmap(&(p -> pbl_bitmap),pbl_index,1);
		uint32_t tmp = query_unuse_memory_one(ptr,0);
		set_memory_pool_one(ptr,tmp,1);
		alloc_page_table(p -> pbl_address,pbl_index,tmp,PAGE_IN_MEMORY | PAGE_WRITE_READ);
		set_page(p,tmp,tmp);
	}
	uint32_t *pbl_address_tmp = (uint32_t *)(p -> pbl_address);
	ptl_address = pbl_address_tmp[pbl_index];
	alloc_page(ptl_address,ptl_index,physical_page_address,PAGE_IN_MEMORY | PAGE_WRITE_READ);
}
void open_page_mode(page_manager_t *p) { page_running((uint32_t)p -> pbl_address); }
void close_page_mode() { page_end(); }
void flush_table(page_manager_t *p) {
	page_end();
	page_running((uint32_t)p -> pbl_address);
}