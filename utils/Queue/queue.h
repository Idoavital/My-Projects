/*******************************************************************************/
#include<stddef.h>


#ifndef __QUEUE_H__
#define __QUEUE_H__

/*******************************************************************************/
/* encapsulating the queue */ 

typedef struct Queue QUEUE;


/*******************************************************************************/
/*
 * creating a new queue
 * return the queue pointer, fail-NULL
 */

QUEUE *qCreate (void);
/*******************************************************************************/
/* Inserts the specified element into this queue
 * parameter: Queue to do this operation
 * parameter: const pointer to element to enqueue
 * return success-0 fail non-zero
 */
int qEnqueue (QUEUE *queue, const void *element);

/*******************************************************************************/
/* Retrieves and removes the head of this queue
 * parameter: Queue to do this operation
 * return pointer to the element that removed, empty queue-NULL
 */
void* qDequeue (QUEUE *queue);

/*******************************************************************************/
/* Retrieves, but does not remove, the head of this queue, or returns null if
 * this queue is empty
 * parameter: const Queue to do this operation
 * return pointer to the element, empty queue-NULL
 */
void *qPeek (const QUEUE *queue);


/*******************************************************************************/
/*
 * destroy the queue
 * parameter: queue
 * return success-0, fail- non-zero
 */

int qDestroy (QUEUE *queue);

/*******************************************************************************/
/*
 * count the queue elements
 * parameter: const queue pointer
 * return the number of the queue elements
 */
int qIsEmpty (const QUEUE *queue);

/*******************************************************************************/

#endif

/*******************************************************************************/
