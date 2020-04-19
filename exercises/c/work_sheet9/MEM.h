#include <stdio.h>

#ifndef __MEM_H__
#define __MEM_H__

/* copy the charcter c to he first n characters of the string pionted  by argumrnt str*/
void *Memset(void *str, int c, size_t n) ;

/* copy n charcters from memory area src to memory dest*/
/* this is a fast copy , copy full word when it's possible */
void *Memcpy(void *dest, const void *src, size_t n) ;

/* copies n characters from src to dest, but for overlapping memory blocks, */
/* memmove() is a safer approach than memcpy()            					*/
void *Memmove(void *dest, const void *src, size_t n);


#endif
