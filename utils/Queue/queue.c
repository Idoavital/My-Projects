#include <stddef.h> /* size_t*/
#include <stdlib.h> /*malloc free */
#include <assert.h> /* assert */

#include "queue.h"
#include "SList.h"

struct Queue 
{	
	Node_t *head;
	Node_t *tail;
	
};

/*******************************************************************************/
/*
 * creating a new queue
 * return the queue pointer, fail-NULL
 */

QUEUE *qCreate (void)
{
	QUEUE *queue =(QUEUE *) malloc(sizeof(QUEUE));

	queue->tail = SListCreate(NULL); /* craete a dummy node */
	queue->head = SListCreate(NULL); /* craete a dummy node */
	
	queue->head->next = queue->tail;
	
	return queue;
}
/*******************************************************************************/
/* Inserts the specified element into this queue
 * parameter: Queue to do this operation
 * parameter: const pointer to element to enqueue
 * return success-0 fail non-zero
 */
int qEnqueue (QUEUE *queue, const void *element)
{
	Node_t *temp_n = NULL;
	
	assert (NULL != queue);
	
	temp_n = SListCreate((void *)element);
	
	if (NULL == temp_n)
	{
		return -1;
	}
	
	SListInsert(queue->tail, temp_n); /* insert the new node */
	queue->tail = temp_n; /*update the tail*/

	return 0;
}


/*******************************************************************************/
/* Retrieves and removes the head of this queue
 * parameter: Queue to do this operation
 * return pointer to the element that removed, empty queue-NULL
 */
void* qDequeue (QUEUE *queue)
{
	void * return_data = NULL;
	Node_t *temp_node ;
	
	assert (NULL != queue);
	
	temp_node = SListRemoveAfter(queue->head);
	return_data = temp_node->data;
	
	free(temp_node);
	
return return_data;

}


/*******************************************************************************/
/* Retrieves, but does not remove, the head of this queue, or returns null if
 * this queue is empty
 * parameter: const Queue to do this operation
 * return pointer to the element, empty queue-NULL
 */
void *qPeek (const QUEUE *queue)
{
	assert (NULL != queue);
	
	return queue->head->next->data;
}

/*******************************************************************************/
/*
 * parameter: const queue pointer
 * return 1 if queue is empty
 */
int qIsEmpty (const QUEUE *queue)
{
	assert (NULL != queue);

	if (queue->tail == queue->head->next)
	{
		return 1;
	}
	
	return 0;
}
/*******************************************************************************/
/*
 * destroy the queue
 * parameter: queue
 * return success-0, fail- non-zero
 */
int qDestroy (QUEUE *queue)
{
	assert (NULL != queue);
	
	while (1 != qIsEmpty(queue))
	{
		qDequeue(queue);
	}
	free(queue->tail);
	queue->tail = NULL;
	free(queue->head);
	queue->head = NULL;
	free(queue);
	
	return 0;
}
