#include <stddef.h> /* for size_t*/
#include "MEM.h"

#define W_SIZE	sizeof(size_t)

static unsigned long int buildWordOfChar (int c) ;

void *Memset(void *str, int c, size_t n)

{
	char * temp_str = (char *) str;  /* for copy byte*/
	int reminder = 0 ;		/* offset  */
	size_t i = 0 ;
	size_t word = 0 ;
		
	
	reminder = checkAligned ( str);
			 
	word = buildWordOfChar ( c );
	
	while	( i < (W_SIZE -reminder) && 0 != reminder)  /* set one byte by byte to the begin of the align */
	{
		*(temp_str+i) = c ;		
		i++;
	}
	
	while ( i <= ( n -(8 - reminder))	)  /* set word */
	{
		*(size_t *) (temp_str+i) = word;
		i += W_SIZE;
	}
	
	while ( i < n)  /* set one byte byte to the end  after  align */
	{
		*(temp_str+i) = c ;		
		i++;
	}
	
	return str;
}

/* check if the adress is aligned , and return the offset from align*/
 int checkAligned (void const *str) 
{
	int ret =0 ;
	ret = (unsigned long int ) str & (W_SIZE - 1) ;

	return ret;
}

/* build a word from a char*/
 unsigned long int buildWordOfChar (int c)
{
	int i = 0;
	unsigned long  ret = 0; /* word of char c  */

	for ( ; i < W_SIZE ; i ++ )
	{
		ret <<= 8 ;
		ret |= c ;		
	}		
	
	return ret ;
}

