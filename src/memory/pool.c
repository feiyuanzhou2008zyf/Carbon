#include "pool.h"
void create_memory_pool(memory_pool_t *pool,uint32_t bitmap_address,uint32_t begin_address,uint32_t size,uint32_t type) {
	create_bitmap(&(pool -> bitmap),bitmap_address,size);
	pool -> memory_begin_address = begin_address;
	pool -> type = type;
}
void show_use_memory(memory_pool_t *pool) {
	printk("Using memory:\n");
	uint32_t size = pool -> bitmap.size;	
	uint32_t begin_address,end_address;
	uint32_t x,y;
	int i;
	uint8_t value;
	for (i = 0;i < size;) {
 		value = query_bitmap(&pool -> bitmap,i);
		while (value == 0) {
			i++;
			if (i >= size) { return; }
			value = query_bitmap(&pool -> bitmap,i);
		}
		x = i;
		begin_address = (uint32_t)pool -> memory_begin_address + i * 4 * 1024;
		while (value == 1) {
			i++;
			if (i >= size) { break; }
			value = query_bitmap(&pool -> bitmap,i);
		}
		i--;
		y = i;
		end_address =(uint32_t)pool -> memory_begin_address + i * 4 * 1024 + 0xFFF;
		printk("%d-%d:\t%dK-%dK\n0x%08X-0x%08X\n",x,y,x * 4,y * 4,begin_address,end_address);
		i++;
		i++;
	}
}
void show_unuse_memory(memory_pool_t *pool) {
	printk("Free memory:\n");
	uint32_t size = pool->bitmap.size;	
	uint32_t begin_address,end_address;
	uint32_t x,y;
	int i;
	uint8_t value;
	for (i = 0;i < size;) {
 		value = query_bitmap(&pool -> bitmap,i);
		while (value == 1) {
			i++;
			if(i >= size) { return; }
			value = query_bitmap(&pool -> bitmap,i);
		}
		x = i;
		begin_address = (uint32_t)pool -> memory_begin_address + i * 4 * 1024;
		while (value == 0) {
			i++;
			if (i >= size) { break; }
			value = query_bitmap(&pool -> bitmap,i);
		}
		i--;
		y = i;
		end_address =(uint32_t)pool -> memory_begin_address + i * 4 * 1024 + 0xFFF;
		printk("%d-%d: %dK-%dK\n0x%08X-0x%08X\n",x,y,x * 4,y * 4,begin_address,end_address);
		i++;
	}
}
uint32_t query_unuse_memory_one(memory_pool_t *pool,uint32_t address) {
	uint32_t address_tmp;
	uint32_t size = pool -> bitmap.size;
	if ((uint32_t)address >= (uint32_t)pool -> memory_begin_address && (uint32_t)address <= ((uint32_t)pool -> memory_begin_address + pool -> bitmap.size * 4 * 1024)) {		
		int tmp;
		tmp = -1;
		uint32_t tmp_index = ((uint32_t)address - (uint32_t)pool -> memory_begin_address) / (4 * 1024);
		int i;
		for (i = tmp_index;i < size;) {
			uint8_t value = query_bitmap(&pool -> bitmap,i);
			if (value == 0) {
				tmp = i;
				break;
			}
			i++;
		}
		if (tmp==-1) {
			printk("Cannot find free memory!");
			return (uint32_t)address_tmp;
		}
		else { address_tmp =(uint32_t )((int)pool -> memory_begin_address + tmp * 4 * 1024); }
	}
	else { printk("Your Address is NOT in this pool,check code!"); }
	return (uint32_t)address_tmp;
}
uint32_t query_unuse_memory(memory_pool_t *pool,uint32_t address,uint32_t count) {
	uint32_t address_tmp;
	uint32_t size = pool -> bitmap.size;
	uint32_t i,j,index_tmp_1;
	uint8_t value_tmp;
	if ((uint32_t)address >= (uint32_t)pool -> memory_begin_address && (uint32_t)address <= ((uint32_t)pool -> memory_begin_address + pool -> bitmap.size * 4 * 1024)) {
		index_tmp_1 = ((uint32_t)address - (uint32_t)pool -> memory_begin_address) / (4 * 1024);
		for (i = index_tmp_1;i < size;i++) {
			if ((i + count) > size) {
				printk("QueryUnuse bad!");
				return (uint32_t)address_tmp;
			}
			value_tmp = 0;
			for (j = 0;j < count;j++) { value_tmp = value_tmp | query_bitmap(&pool -> bitmap,i + j); }
			if (value_tmp == 0) {
				address_tmp=(uint32_t)((uint32_t)pool -> memory_begin_address + i * 4 * 1024);
				break;
			}
		}	
	}
	else {
		printk("QueryAddress:0x%08X\n",address);
		printk("Your Address is NOT in this pool,check code!\n");
		while(1) {}
	}
	return (uint32_t)address_tmp;
}
void set_memory_pool_one(memory_pool_t *pool,uint32_t index,uint8_t value) {
	uint32_t pool_begin_address =(uint32_t)pool -> memory_begin_address;
	uint32_t pool_end_address =(uint32_t)(((int)pool -> memory_begin_address + pool -> bitmap.size * 4 * 1024));
	if (pool_end_address == 0) { pool_end_address = 0xFFFFFFFF; }
	if ((uint32_t)index >= pool_begin_address && (uint32_t)index <= pool_end_address) {
		uint32_t tmp = ((uint32_t)index - (uint32_t)pool -> memory_begin_address) / (4 * 1024);
		set_bitmap(&pool -> bitmap,tmp,value);
	}
	else {
		show_memory_pool_message(pool);
		printk("pool is in 0x%08X-0x%08X\n",pool_begin_address,pool_end_address);
		printk("SetAddress:0x%08X\n",index);
		printk("Your Address is NOT in this pool,check code!\n");
		while(1) {}
	}
}
void set_memory_pool(memory_pool_t *pool,uint32_t index,uint32_t count,uint8_t size) {
	for (int i = 0;i < count;i++) { set_memory_pool_one(pool,(uint32_t)((int)index + i * 4 * 1024),value); }
}
void show_memory_pool_message(memory_pool_t *pool) {
	printk("MapAddress:0x%08X\nMapSize:0x%08X\nBeginAddress:0x%08X\n",pool -> bitmap.address,pool -> bitmap.size,pool -> memory_begin_address);
	show_unuse_memory(pool);
	show_use_memory(pool);
}