#include <sys/types.h> /* ssize */
#include <assert.h> /* assert*/
#include <stdlib.h> /* abs */
#include "vsm.h"



#define MAGIC_N 0xffffcccc

/*vsm structure*/
 struct vsm
 {
 	
 	size_t pool_size;
 } ;
 
typedef struct header
{
#ifndef NDEBUG
	size_t magic;
#endif
	ssize_t size_block;
}HEADER_T;

typedef  HEADER_T * (*FUNC_T)( HEADER_T *header, size_t *param);


/************************* static functions ******************************************/

/*the function make the the best allocte and build new header if necessary*/
static HEADER_T *allocte ( HEADER_T *curr_head, size_t size_elem);

/* activate founction that pointed  for each free block */
static  HEADER_T *forEach( const VSM_T *vsm , FUNC_T fun , size_t * param);

/*count the free block*/
static  HEADER_T * freeSpace ( HEADER_T *header, size_t *param);

/*count the max free block*/
static  HEADER_T * maxLarge( HEADER_T *header, size_t *param); 

/* calculate the the size of real size that need to use for the allocation */ 
/* include the header and the aligend byte */
static size_t fixSize (size_t size_elm);

/* make Defragmentation to the current block if it's possible*/
static  HEADER_T *Defragmentation (const VSM_T *vsm , HEADER_T *curr_head );
/* Initilize VSM data structe. returns 0 for success */ 


/******************************************************************************/
VSM_T* VSMInit(void* pool, size_t pool_size)
{
	VSM_T * vsm;
	HEADER_T *head;
	
	assert (NULL != pool);
	
	if (pool_size < sizeof (VSM_T))
	{
		return NULL;
	}
	vsm =  pool;
	vsm->pool_size = pool_size;
	
	/*first header */
	head =( HEADER_T *)(vsm + 1);
	head->size_block = pool_size - sizeof (VSM_T) - sizeof(HEADER_T) ;
#ifndef NDEBUG
	head->magic = MAGIC_N ;
#endif
	
	return vsm;
	
}	

/* Allocate memory for element */ 
void *VSMAlloc(VSM_T *vsm, size_t size_elm)
{

	HEADER_T *curr_head;
	
	assert (NULL != vsm);
	
	size_elm = fixSize ( size_elm); /* calculate the the size of real size that need to use for the allocation */ 
	
	curr_head =(HEADER_T*) ((char*)vsm + sizeof (VSM_T)); /* first header */
	
	while ((size_t)vsm + vsm->pool_size - sizeof(HEADER_T) >= (size_t)curr_head )
	{
		
		if (curr_head->size_block >= 0 )
		{
			/* make Defragmentation to the current block if it's possible*/			
			curr_head = Defragmentation (vsm ,curr_head ); 		
			if (curr_head->size_block >= size_elm)
			{
				return (allocte (curr_head, size_elm));
			}
			
		}	
		/* get the next block */
		curr_head = (HEADER_T*)((char*)curr_head + abs(curr_head->size_block)+sizeof(HEADER_T)  );	
	}
	
	return NULL ;
}




/* Free element's memory allocation */ 
void VSMFree(void *elem)
{

	HEADER_T *t_head;
	 
	assert (NULL != elem); 
	
	t_head =( HEADER_T *) ((char*)elem - sizeof(HEADER_T));
	
	assert (0 > t_head->size_block && " the pointer is allredy free ");
	#ifndef NDEBUG
		assert (MAGIC_N == t_head->magic );
	#endif
	t_head->size_block *= -1; /* chenge the size to minus */
	
}

/* calculate the the size of real size that need to use for the allocation */ 
/* include the header and the aligend byte */
static size_t fixSize (size_t size_elm)
{
	size_t fix_size = ((size_elm + sizeof(size_t) - 1 )/sizeof(size_t) ) * sizeof(size_t) ;
	return fix_size;
}




/* Returns the number of unused blocks of memory */ 
#ifdef ADVANCED
size_t VSMFreeSpace (const VSM_T *vsm)
{
	size_t sum_free = 0;

	forEach( vsm ,&freeSpace  , &sum_free);


	return sum_free;

}

/* Returns the size of the large free blocks in memory */
size_t VSMLargeSpace (const VSM_T *vsm)
{
	size_t big_size = 0;

	forEach( vsm ,&maxLarge  , &big_size);

	return big_size;
}
#endif

/**********************************************************************/
	/*  Defragmentation with the next block*/
static  HEADER_T *Defragmentation (const VSM_T *vsm , HEADER_T *curr_head )
{
	HEADER_T *temp_head;
	
	temp_head = (HEADER_T*)((char*)curr_head + curr_head->size_block+sizeof(HEADER_T)); /*  Defragmentation with the next block*/
	/* check if come to the end of the pool */
	if ((char*)vsm + vsm->pool_size <= (char*)temp_head)
		{
			return curr_head;
		}
		
	while (temp_head->size_block >= 0 )
	{
		
		if (temp_head->size_block >= 0 ) 
		{
			curr_head->size_block += temp_head->size_block + sizeof(HEADER_T) ;
		}
		temp_head = (HEADER_T*)((char*)curr_head + curr_head->size_block+sizeof(HEADER_T)); /*  Defragmentation with the next block*/
		/* check if come to the end of the pool */
		if ((char*)vsm + vsm->pool_size <= (char*)temp_head)
		{
			return curr_head;
		}
	}
	return curr_head;
	
}

/**********************************************************************************/
static HEADER_T * forEach( const VSM_T *vsm , FUNC_T func , size_t * param)
{
	HEADER_T *curr_head;

	curr_head =(HEADER_T*) ((char*)vsm + sizeof (VSM_T)); /* first header */
	
	while ((size_t)vsm + vsm->pool_size - sizeof(HEADER_T) >= (size_t)curr_head)	
	{
		if (curr_head->size_block >= 0) /* if the block is free */
		{
			curr_head = Defragmentation (vsm , curr_head ); /*Defragmentation with the next block*/
			func (curr_head , param);
		
		}

		curr_head = (HEADER_T*)((char*)curr_head + abs(curr_head->size_block)+sizeof(HEADER_T));
	}
	return curr_head;
}

/*****************************************************************************/
static  HEADER_T * maxLarge( HEADER_T *header, size_t *param)
{
	if (header->size_block > *param )
	{
		*param = header->size_block;
	}

	return header;
}

/*****************************************************************************/
static  HEADER_T * freeSpace ( HEADER_T *header, size_t *param)
{
	
		*param += header->size_block;

	return header;
}

/*****************************************************************************/
static HEADER_T *allocte ( HEADER_T *curr_head, size_t size_elm)
{

	HEADER_T *temp_head;
	if (curr_head->size_block >= (size_elm + sizeof(HEADER_T))) /* check if there is space for the element and for the header*/
	{
		temp_head = (HEADER_T*)((char*)curr_head + size_elm + sizeof(HEADER_T)); /*build new header */
		temp_head->size_block = curr_head->size_block - (size_elm + sizeof(HEADER_T)); /* initialzing the next size block */
		curr_head->size_block = size_elm;
		#ifndef NDEBUG
			curr_head->magic = MAGIC_N ;
		#endif					
	}	
						
	curr_head->size_block *= -1 ; /* set the sign to : not free */  
	return (curr_head+1); /* return pointer to user after the header */
}









