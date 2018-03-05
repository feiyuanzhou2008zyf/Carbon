#include "string.h"
void *memcpy(void *dest,const void *src,size_t count) {
	if (dest == NULL || src == NULL || count < 0)  
        return NULL;  
    char *tempDest = (char *)dest;  
    char *tempSrc = (char *)src;  
    while (count-- > 0)  
        *tempDest++ = *tempSrc++;  
    return dest;
}
void *memset(void *src,int chunk,size_t count) {
	if (src == NULL || count < 0)
		return NULL;
	char *tempSrc = (char *)src;
	while (count-- > 0)
		*tempSrc++ = chunk;
	return src;
}
void bzero(void *src,unsigned len) {
	register char *tempSrc = (char *)src;
	while (len != 0) {
		*tempSrc++ = 0;
		len--;
	}
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
