#include "memorymanager.h"
page_manager_t pg;
memory_pool_t virtual_memory_pool;
uint32_t physicalmemoryaddress;
uint32_t virtualmemoryaddress;
void set_page_on_paging(uint32_t virtual_page_address,uint32_t physical_page_address) {
	int pblindex,ptlindex;
	pblindex = (virtual_page_address & 0xFFFFF000) / (4 * 1024 * 1024);
	ptlindex = (virtual_page_address & 0x003FFFFF) / (4 * 1024);
	uint32_t pbl_address;
	memory_pool_t *ptr = &(pg.physical_memory_pool);
	pbl_address = pg.pbl_address;
	if (query_bitmap(&(pg.pbl_bitmap),pblindex) == 0) {
		set_bitmap(&(pg.pbl_bitmap),pblindex,1);
		uint32_t tmp =  query_unuse_memory_one(ptr,0);
		set_memory_pool_one(ptr,tmp,1);
		uint32_t tmpvitrl = query_unuse_memory_one(&virtual_memory_pool,0);
		set_memory_pool_one(&virtual_memory_pool,tmpvitrl,1);
		set_page_on_paging(tmpvitrl,tmp);
		alloc_page_table(pg.pbl_address,pblindex,tmp,PAGE_IN_MEMORY | PAGE_WRITE_READ);
		alloc_page(tmpvitrl,ptlindex,physical_page_address,PAGE_IN_MEMORY | PAGE_WRITE_READ);
		set_memory_pool_one(ptr,physical_page_address,1);
		set_memory_pool_one(&virtual_memory_pool,virtual_page_address,1);
	}
	else {
		uint32_t * tmppbladdress = (uint32_t*)pbl_address;
		uint32_t virtual_address = query_virtual_address(tmppbladdress[pblindex] & 0xFFFFF000);
		alloc_page(virtual_address,ptlindex,physical_page_address,PAGE_IN_MEMORY | PAGE_WRITE_READ);
		set_memory_pool_one(ptr,physical_page_address,1);
		set_memory_pool_one(&virtual_memory_pool,virtual_page_address,1);
	}
}
void init_memory_manager(int physical_memory_size,void *kernel_address,int kernel_size) {
	create_page_manager(&pg,0,0xFFFFF+0x20000,physical_memory_size,0x4FC000,0x4FD000,0x4FE000,0x4FF000,0x500000,0x501000,0);
	create_memory_pool(&virtual_memory_pool,0x100000,0,1024*1024,VIRTUAL);
	set_memory_pool(&virtual_memory_pool,0,compute_page(0xFFFFF+0x20000),1);
	set_memory_pool_one(&virtual_memory_pool,0x4FE000,1);
	set_memory_pool_one(&virtual_memory_pool,0x4FF000,1);
	set_memory_pool_one(&virtual_memory_pool,0x500000,1);
	set_memory_pool_one(&virtual_memory_pool,0x501000,1);
	set_memory_pool_one(&virtual_memory_pool,0x120000,1);
	set_memory_pool_one(&virtual_memory_pool,0x121000,1);
	set_memory_pool_one(&virtual_memory_pool,0x122000,1);
	set_memory_pool_one(&virtual_memory_pool,0x123000,1);
}
void *kmalloc(int size) {
	uint32_t tmp = query_unuse_memory(&virtual_memory_pool,0,size);
	for (int i = 0;i < size;i++) {
		uint32_t pytmp = query_unuse_memory_one(&(pg.physical_memory_pool),0);
		set_page_on_paging(tmp + i * 4 * 1024,pytmp);
	}
	return (void *)tmp;
}
void free(void *ptr,int size) {
	if(((uint32_t)ptr & 0xFFFFF000) == 0) { printk("your address is worng,please check it! ptr = %x\n",ptr); }
	else {
		uint32_t address = (uint32_t)ptr;
		release_page(address,size);
	}
}
void *merge(int * sizesum,const void *ptr1,int size1,const void *ptr2,int size2) {
	uint32_t tmp = query_unuse_memory(&virtual_memory_pool,0,size1 + size2);
	uint32_t tmp_add = tmp;
	uint32_t tmp_ptr;
	int i;
	tmp_ptr = (uint32_t)ptr1;
	for(i = 0;i < size1;i++) {}
	tmp_add = tmp + size1;
	for (i = 0;i < size2;i++) {}
	return (void *)tmp;
}
void print_info() {
	printk("physical memory pool info:\n");
	show_memory_pool_message(&(pg.physical_memory_pool));
	printk("virtual memory pool info:\n");
	show_memory_pool_message(&virtual_memory_pool);
}
void release(uint32_t virtual_page_address) {
	int pblindex,ptlindex;
	pblindex =  (virtual_page_address & 0xFFFFF000) / (4 * 1024 * 1024);
	ptlindex = (virtual_page_address & 0x003FFFFF) / (4 * 1024);
	uint32_t *address_pbl =  (uint32_t *)pg.pbl_address;
	uint32_t vitrual_address = query_virtual_address(address_pbl[pblindex] & 0xFFFFF000);
	uint32_t tmpaddress = ((uint32_t *)vitrual_address)[ptlindex] & 0xFFFFF000;
	alloc_page(vitrual_address,ptlindex,0,0);
	memory_pool_t *physicalpool = &(pg.physical_memory_pool);
	set_memory_pool_one(physicalpool,tmpaddress,0);
	set_memory_pool_one(&virtual_memory_pool,virtual_page_address,0);
	for (int i = 0;i < 1024;i++) {
		int test = 0;
		uint32_t * ptl_address_tmp = (uint32_t *)(address_pbl[i] & 0xFFFFF000);
		int j;
		for (j = 0;j < 1024;j++) {
			if ((ptl_address_tmp[j] & 0xFFFFF000) != 0) {
				test = 1;
				break;
			}
		}
		if ((test == 0)&& !query_bitmap(&pg.pbl_bitmap,i)) {
			uint32_t *tmp = (uint32_t *)(pg.pbl_address);
			if ((tmp[i] & 0xFFFFF000) != 0) {
				release(tmp[i] & 0xFFFFF000);
				set_bitmap(&pg.pbl_bitmap,i,0);
				alloc_page_table(pg.pbl_address,i,0,0);
			}
		}
	}
}
void release_page(uint32_t virtual_page_address,int32_t count) {
	uint32_t tmp = virtual_page_address;
	for(int i = 0;i < count;i++) { release(tmp + i * 4096); }
}
uint32_t query_virtual_address(uint32_t physical_page_address) {
	if(physical_page_address==0) {
		printk("your physical page address=%d is error!",physical_page_address);
		return 0;
	}
	else {
		int pblindex = 0,ptlindex = 0;
		uint32_t pbl_address,ptl_address;
		bitmap_t *ptr = &(pg.pbl_bitmap);
		pbl_address = pg.pbl_address;
		uint32_t * tmppbl = (uint32_t *)(pbl_address & 0xFFFFF000);
		for (int i = 0;i < 1024;i++) {
			if (query_bitmap(ptr,i) == 0) { continue; }
			ptl_address = tmppbl[i] & 0xFFFFF000;
			uint32_t * tmpptl = (uint32_t*)ptl_address;
			for (int j = 0;j < 1024;j++) {
				if ((tmpptl[j] & 0xFFFFF000) == physical_page_address) {
					pblindex = i;
					ptlindex = j;
					break;
				}
			}
		}
		return pblindex * 1048576 * 4 + ptlindex * 1024 * 4;
	}
}
uint32_t query_physical_address(uint32_t virtual_page_address) {
	int pblindex,ptlindex;
	pblindex = (virtual_page_address & 0xFFFFF000) / (4 * 1024 * 1024);
	ptlindex = (virtual_page_address & 0x003FFFFF) / (4 * 1024);
	printk("pblindex: %d, ptlindex: %d  ",pblindex,ptlindex);
	uint32_t pbl_address,ptl_address;
	pbl_address = pg.pbl_address;
	printk("pbl address:  0x%08X\n",pbl_address);
	if (query_bitmap(&(pg.pbl_bitmap),pblindex) == 0) {
		printk("the virtual page address is not allocation!");
		return 0;
	}
	else {
		uint32_t *tmp =(uint32_t *)pbl_address;
		ptl_address = tmp[pblindex] & 0xFFFFF000;
		printk("the pagetable address is: 0x%08X\n",ptl_address);
		tmp = (uint32_t *)ptl_address;
		return tmp[ptlindex] & 0xFFFFF000;
	}
}
