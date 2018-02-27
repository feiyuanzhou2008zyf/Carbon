#include "lib.h"
#include "types.h"
void *memcpy(void *dest,const void *src,size_t count) {
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for (;count != 0;count--)
		*dp++ = *sp++;
	return dest;
}
void *memset(void *dest,char value,size_t count) {
	char *temp = (char *)dest;
	for (;count != 0;count--)
		*temp++ = value;
	return dest;
}
unsigned short *memsetw(unsigned short *dest,unsigned short value,size_t count) {
	unsigned short *temp = (unsigned short *)dest;
	for (;count != 0;count--)
		*temp++ = value;
	return dest;
}
size_t strlen(const char *string) {
	size_t return_value;
	for (return_value = 0;*string != '\0';string++)
		return_value++;
	return return_value;
}
