/*fsm structure*/
#include <assert.h>
#include <sys/types.h> /* ssize_t */

#include "fsm.h"


typedef struct block_head 
{
	ssize_t offset;
} BLOCK_HEAD_T;

struct fsm 
{
	
	size_t next_free;
	size_t counter;
};


/* return the suggested size of allocation in bytes, according to user demand */
size_t FSMSuggesteSize(size_t no_elem, size_t size_elem)
{
	size_t pool_size = 0;
	
				/* the sturct size   +  (block header + the aligned size of element +  the element  size* number of elements  */
	pool_size = (sizeof(FSM_T)) + no_elem * (sizeof(BLOCK_HEAD_T) +((size_elem + sizeof(size_t) - 1 )/sizeof(size_t)) * sizeof(size_t));
	return pool_size;
}


/* Initilize FSM data structe. returns 0 for success */ 
FSM_T * FSMInit(void *pool, size_t no_elem, size_t size_elem)
{
	size_t fix_size =0; /* the aligend size of element */
	int i = 0;
	FSM_T *fs ; /* for the struct manger*/
	BLOCK_HEAD_T *head_block = NULL;
	
	assert (NULL != pool );
	
	
	/* Initializing the struct manger*/
	fs = (FSM_T*) pool ;	
	fs->next_free = sizeof (FSM_T) ;
	fs->counter = no_elem ;
	
	if(no_elem == 0)
	{
		return pool;
	}
	 /* calculating the block size */
	fix_size = sizeof(BLOCK_HEAD_T)+((size_elem + sizeof(size_t) - 1 )/sizeof(size_t)) * sizeof(size_t); /* the size of block include the header*/

	head_block = (BLOCK_HEAD_T* ) (fs+ 1); /* for the first element*/
	
	for (i =1 ; i < no_elem ; i ++) /* loop for Initializing the block header*/
	{
		head_block->offset = i * fix_size + sizeof (FSM_T); /* offset for the next free element */
		head_block = head_block + fix_size/sizeof(size_t); /* proceed to next block */
	}
		head_block->offset = 0;
		
	return pool;
}

/* Allocate memory for element */ 
void *FSMAlloc(FSM_T *fsm)
{
	ssize_t temp = 0;
	
	/*  if there is no space for malloc*/
	if (0 >= fsm->counter)
	{
		return NULL;
	}
	
	temp = fsm->next_free;
	fsm->next_free = ((BLOCK_HEAD_T*)((char*)fsm + temp ))->offset;
	fsm->counter--;
	
	((BLOCK_HEAD_T*)((char*)fsm + temp ))->offset = -1 * temp;
	return (void*)((char*)fsm + temp +  sizeof(BLOCK_HEAD_T) );
}


/* Free element's memory allocation */ 
void FSMFree(void *elem)
{
	FSM_T *fs ; /* for the struct manger*/
	ssize_t temp_off = 0;
	BLOCK_HEAD_T* temp_header = (BLOCK_HEAD_T*)((char*)(elem) - sizeof(BLOCK_HEAD_T));
	
	if(temp_header->offset > 0) /* cheeck if the pointer is not free */
	{
		return;
	}
	temp_off = temp_header->offset;
	
	fs = (FSM_T*)((char*)temp_header +temp_off);
	
	temp_off = fs->next_free;
	temp_header->offset = temp_off;
	fs->next_free = -1 *  temp_off ;
	
	fs->counter++;
}

/* Returns the number of unused blocks of memory */ 
size_t FSMFreeCount (const FSM_T *fsm)
{
	return fsm->counter;
}
 

