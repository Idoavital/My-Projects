#include "MEM.h"

#define WORD_SIZE  8

void *MemcpyRevers(void *dest, const void *src, size_t n);


void *Memmove(void *dest, const void *src, size_t n)
{

	if ( (char*)src < (char *)dest)
	{
		MemcpyRevers(dest , src , n);
	}
	else 
	{
	Memcpy(dest , src , n);
	}
	return 0;
}


void *MemcpyRevers(void *dest, const void *src, size_t n)
{
	char * ch_dest = (char *) dest +n - 1;  /* pointer to copy byte evrey time*/
	char * ch_src = (char *) src + n -1;	 /* pointer to copy byte evrey time*/
	
	int offset_dest =0;
	int how_many_words = 0;
	int end_copies = 0;

	/*check the offsets*/
	offset_dest =  (size_t)ch_dest & (sizeof(size_t)-1);
	
	how_many_words = (n-offset_dest) / (sizeof(size_t));

	/* the number of copies after the words aligned */
	end_copies = (n-offset_dest) & (sizeof(size_t)-1);

	/* copy the first byte*/
	while (offset_dest--)
	{
		ch_dest--;
		ch_src--;
		*ch_dest = *ch_src ;
		
	}
		
	/*	copy words */
	while ( how_many_words--)
	{	
		ch_dest -= (sizeof(size_t));
		ch_src -= (sizeof(size_t));
		*(size_t*)ch_dest = *(size_t*)ch_src;
	}

	while (end_copies--)
	{
		ch_dest--;
		ch_src--;
		*ch_dest = *ch_src ;
		
	}
		
	return dest;
}

