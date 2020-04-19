#include <stdlib.h> /* malloc */
#include <assert.h>

#include "pQueue.h" 
#include "sortL.h"


struct PQueue
{
	SORT_L *sl;
};
/*******************************************************************************/
/* Creates a Pri Queue. Returns NULL on failure.                             */
PQUEUE *pQCreate(PQIsBefore_t isBef)
{
	PQUEUE *pq = (PQUEUE *) malloc (sizeof (PQUEUE));
	if ( pq == NULL )
	{
		return NULL;
	}
	pq->sl = SortCreate (isBef);
	
	if (NULL ==pq->sl)
	{
		free(pq->sl);
		return NULL;	
	}	
	return pq;
}

/*******************************************************************************/
/* Disposes of resources used by PQueue.                                           */
void pQDestroy(PQUEUE *PQueue)
{
	assert (NULL != PQueue);
	
	SortDestroy(PQueue->sl);
	free (PQueue);
}
/*******************************************************************************/
/* insert data to the list , returns 0- success, nonZero- failed                */
int pQEnqueue(PQUEUE *PQueue , void *data)
{
	int ret = 0;
	
	assert (NULL != PQueue);
		
	/* check the insert success */
	/* Compare the iterators after insert to the end of list */
	ret = SortIsEqual( SortInsert(PQueue->sl,data), SortEnd(PQueue->sl)) ?  1: 0;
	return ret;
} 
/*******************************************************************************/
/* Remove item from front of the queue, returns pointer to the data that removed*/
void *pQDequeue(PQUEUE *PQueue)
{
	void *data =NULL;
	assert (NULL != PQueue);
	
	data =  SortGetData( SortBegin(PQueue->sl) );
	SortPopBack(PQueue->sl);

	return data;
}

/*******************************************************************************/
/* return pointer to the data in the front of the queueu without remove it    */
void *pQPeek(const PQUEUE *PQueue)
{
	assert (NULL != PQueue);
	
	return SortGetData( SortBegin(PQueue->sl) );
}

/*******************************************************************************/
/* Returns 1 if queue is empty. Returns 0 otherwise.                            */
int pQIsEmpty(const PQUEUE *PQueue)
{
	assert (NULL != PQueue);
	
	return (SortIsEmpty(PQueue->sl));
}
/*******************************************************************************/
/* return the number of elements in the queue                                   */
size_t pQSize(const PQUEUE *PQueue)
{
	assert (NULL != PQueue);
	
	return SortSize(PQueue->sl);
}
/*******************************************************************************/
/* clear all the elements in the queue                  */
void pQClear (PQUEUE *PQueue)
{
	assert (NULL != PQueue);
	
	while (1 != pQIsEmpty(PQueue))
	{
		pQDequeue(PQueue);
	}
}

/*******************************************************************************/
/* the function erase the member with the data that been given in the functoin 
	and return pointer to the data 	*/
void *pQErase (PQUEUE *PQueue , PQIsMatch_t match, const void *data, void *param)
{
	void *temp_data = NULL;
	SORT_ITER_T it;
	
	assert (NULL != PQueue);
	
	/* use the finction SortFind to find the member that need to be eraesed*/
	it = SortFind(PQueue->sl, SortBegin(PQueue->sl) , match, data, param);
	
	/* check if the member was found in the list */
	if (1 == SortIsEqual( it, SortEnd(PQueue->sl)))
	{
		return NULL;
	}
	
	temp_data = SortGetData (it);
	SortErase(PQueue->sl , it);
	
	return temp_data;
}














