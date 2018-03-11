#include "bitmap.h"
#include "string.h"
void create_bitmap(bitmap_t *bit,uint32_t map_address,uint32_t size) {
	bit -> address = (uint32_t)map_address;
	bit -> size = size;
	memset((void *)map_address,0,size / 8);
}
void set_bitmap(bitmap_t *bit,uint32_t index,uint8_t value) {
	uint32_t index_x,index_y;
	index_x = index / 8;
	index_y = index % 8;
	uint8_t tmp;
	uint8_t tmp_value;
	uint8_t tmp_test;
	tmp = (uint8_t *)bit -> address;
	tmp_value = tmp[index_x];
	if (value == 0) {
		tmp_test = 1 << index_y;
		tmp_test = tmp_test ^ 0xFF;
		tmp_value = tmp_value & tmp_test;
	}
	else {
		tmp_test = 1 << index_y;
		tmp_value = tmp_value | tmp_test;
	}
	tmp[index_x] = tmp_value;
}
uint8_t query_bitmap(bitmap_t *bit,uint32_t index) {
	uint32_t index_x,index_y;
	index_x = index / 8 ;
	index_y = index % 8 ;
	uint8_t value;
	uint8_t *tmp;
	tmp = (uint8_t *)bit -> address;
	value = tmp[index_x];
	value = (value & (1 << index_y)) >> index_y;
	return value;
}
