#include "string.h"
inline void memcpy(uint8_t *dest,const uint8_t *src,uint32_t len) {
    for (;len != 0;len--)
        *dest++ = *src++;
}
inline void memset(void *dest,uint8_t val,uint32_t len) {
    uint8_t *dst = (uint8_t *)dest;
    for (;len != 0;len--)
        *dst++ = val;
}
inline void bzero(void *dest,uint32_t len) { memset(dest,0,len); }
int strcmp(const char *str1, const char *str2) {
	while ((*str1 || *str2) && *str1 == *str2)
		*str1++,*str2++;
	if (*str1 < *str2)
		return -1;
	return *a > *b;
}
char *strcpy(char *dest, const char *src) {
	char *p = dest;
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return dest;
}
char *strcat(char *dest, const char *src) {
	char *dest_ptr = NULL;
	const char *src_ptr = NULL;
	int dest_len = 0;
	if (dest == NULL || src == NULL)
		return NULL;
	dest_len = strlen(dest);
	dest_ptr = dest;
	src_ptr = src;
	dest_ptr += dest_len;
	while (*src_ptr != '\0') {
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src_ptr++;
	}
	*dest_ptr = '\0';
	return dest;
}
int strlen(const char *src) {
	if (src == NULL)
		return NULL;
	return ('\0' != *src) ? (1 + strlen(++src)) : 0;
}