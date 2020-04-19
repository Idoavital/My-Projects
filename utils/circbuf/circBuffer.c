#include <stdlib.h> /* malloc */
#include <assert.h>
#include <string.h> /* memcopy */
#include <assert.h>
#include "circBuffer.h"

#define MIN(a,b) ((a) > (b) ? (a) : (b))
typedef enum { EMPTY , FULL} MODE;


struct Circ_B 
{
	MODE mode  ; /* use to sign if the circle is full or empty*/
	size_t buff_size; /* the size of */
	size_t head;	/* use to write */
	size_t tail;	/* use to read */	
	char data[1];
	
};


CIRC_B *cBufCreate(size_t size)
{
	
	 CIRC_B * circle;		
	 size = size==0 ? 1 : size ; /*  if the size if 0 insert 1*/

	assert (size != 0) ;

	circle = (CIRC_B *) malloc (size + offsetof(CIRC_B, data) );
	if (NULL == circle )
	{
		return NULL;
	}
	
	circle-> buff_size = size ;
	circle-> head = 0;
	circle-> tail = 0;
	circle-> mode  = EMPTY ;
	return circle ;
}

/* Return number of bytes written */
size_t cBufWrite(CIRC_B *cb, const void *buf, size_t size)
{
	size_t dis_head_to_end = cb-> buff_size - cb-> head;
	size_t end_copy_index = 0; /* last place of copy from */
		
	assert (cb != NULL && buf != NULL );
	
		/* check if there is a space to write to*/
	if ((cb->head==cb->tail && cb->mode == FULL) || size == 0)
		{
			Errno = __buffer_is_full;
			return 0;
		}
		
		/* check if the number of byts to copy is bigger than a free space */
	if ( size >  cBufFreeSpace (cb) )
		{
			Errno = __buffer_is_full;
			size = cBufFreeSpace (cb);				
		}		
		
	end_copy_index = (cb->head + size) % cb->buff_size ;
		
		/* check if the copy over the end of the circle */
	if (cb->head < end_copy_index)
	
		{
			memcpy (&cb->data + cb->head, buf, size);
		}
	
		
	else
		{
				/* first copy until the end of the circle */
			memcpy (&cb->data +cb-> head, buf, dis_head_to_end);
			
				/* second copy - the left of byts start copy from the start of the circle  */
			memcpy (&cb->data ,(char *)buf + dis_head_to_end , size - dis_head_to_end);				
		}
	
				/* update the place of head */
			cb->head =  end_copy_index ;
			
				/* update mode if needed*/
			if (cb->head == cb->tail)
			{
				cb-> mode = FULL;
			}
			
		
	return size;
}

/* Returns number of bytes read */
size_t cBufRead(CIRC_B *cb, void *buf, size_t size)
{
		
	size_t dis_tail_to_end = cb-> buff_size - cb-> tail;		
	size_t end_read_index = 0 ; /* last place of read from */
	
	assert (cb != NULL && buf != NULL );
	
	/* check if there is a space to read from*/
	if ((cb->head==cb->tail && cb->mode == EMPTY) || size == 0)
		{
			Errno = __no_data_to_read;
			return 0;
		}
		
		/* if the size is bigger then realy possible to read the size will be change */
	if ( size > cb->buff_size - cBufFreeSpace (cb) )
		{
			Errno = __no_data_to_read;
			size = cb->buff_size - cBufFreeSpace (cb);				
		}		
	

	end_read_index = (cb->tail + size) % cb->buff_size ;
		
	if (cb->tail < end_read_index)
	
		{
			memcpy ( buf, &cb->data + cb->tail, size);
		}
	
	else
		{
				/* first copy until the end of the circle */
			memcpy ( buf, &cb->data +cb->tail , dis_tail_to_end);
			
				/* second copy - the left of byts start copy from the start of the circle  */
			memcpy ((char *)buf + dis_tail_to_end , &cb->data , size - dis_tail_to_end);				
		}
		
		cb->tail = end_read_index ;
			/* update mode if needed*/
		if (cb->head == cb->tail)
		{
			cb->mode = EMPTY;
		}
		
	return size;
}

/* free the memory of pointer */
void cBufDestroy(CIRC_B *cb)
{
	assert (cb != NULL);
	
	if (NULL == cb )
	{
		return;
	}
	free(cb);
}

/* return the distance from the head to tail */
size_t cBufFreeSpace(CIRC_B *cb)
{
	size_t ret =0 ;
	
	assert (cb != NULL);
		/* in a case of a the tail and head are in same place */
	if (cb->head == cb->tail)
	{
		ret = (cb->mode == FULL ? 0 : cb->buff_size) ;
		return ret;
	}
	
	if (cb->head > cb->tail)
	{
			
		ret = (cb->buff_size - cb-> head) + cb->tail ;
		return ret;
	}
		
	ret = cb->tail - cb->head ;
	return ret;	
}
/*
void copy (void * dst1 void * dst2, void * buf1, void * buf2 ,size_t n_copy , size_t size)
{
	if ()
}
*/









