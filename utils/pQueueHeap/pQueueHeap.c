#include <assert.h> /* assert*/
#include <stdlib.h> /* malloc*/

#include "pQueueHeap.h"
#include "heap.h"


struct PQueue
{
	HEAP_T *heap;
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
	pq->heap = HeapCreate(isBef);

	if (NULL ==pq->heap)
	{
		free(pq->heap);
		return NULL;
	}
	return pq;
}

/*******************************************************************************/
/* Disposes of resources used by PQueue.                                           */
void pQDestroy(PQUEUE *PQueue)
{
	assert (NULL != PQueue);

	HeapDestroy(PQueue->heap);
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
	ret = HeapPush(PQueue->heap,data);
	return ret;
}
/*******************************************************************************/
/* Remove item from front of the queue, returns pointer to the data that removed*/
void *pQDequeue(PQUEUE *PQueue)
{
	void *data =NULL;
	assert (NULL != PQueue);

	data = HeapPeek(PQueue->heap);
	HeapPop(PQueue->heap);

	return data;
}

/*******************************************************************************/
/* return pointer to the data in the front of the queueu without remove it    */
void *pQPeek(const PQUEUE *PQueue)
{
	assert (NULL != PQueue);

	return HeapPeek(PQueue->heap);
}

/*******************************************************************************/
/* Returns 1 if queue is empty. Returns 0 otherwise.                            */
int pQIsEmpty(const PQUEUE *PQueue)
{
	assert (NULL != PQueue);

	return (HeapIsEmpty(PQueue->heap));
}
/*******************************************************************************/
/* return the number of elements in the queue                                   */
size_t pQSize(const PQUEUE *PQueue)
{
	assert (NULL != PQueue);

	return HeapSize(PQueue->heap);
}
/*******************************************************************************/
/* clear all the elements in the queue                  */
void pQClear (PQUEUE *PQueue)
{
	assert (NULL != PQueue);

	while (1 != HeapIsEmpty(PQueue->heap))
	{
		pQDequeue(PQueue);
	}
}

/*******************************************************************************/
/* the function erase the member with the data that been given in the functoin
	and return pointer to the data 	*/
void* pQErase (PQUEUE *PQueue , PQIsMatch_t match, const void *data, void *param)
{
	assert (NULL != PQueue);

	return HeapRemove(PQueue->heap,match,data,param);
}






