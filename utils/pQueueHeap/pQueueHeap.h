/*******************************************************************************/
#ifndef	__PQUEUE_H__
#define	__PQUEUE_H__
/*******************************************************************************/

#include <stddef.h>	 /*	size_t	*/


/*******************************************************************************/
/* Pri Queue structure                                         */
typedef struct PQueue PQUEUE;
/*******************************************************************************/


/* Comparison function prototype. returns positive if 'param1' is greater then 'param2'
and zero otherwize                                                                       */

typedef int (*PQIsBefore_t) (const void *param1, const void *param2);


/* returns 1 if they match and 0 otherwize */
typedef int (*PQIsMatch_t)(const void *data1, const void *data2 ,  void *param);
/*******************************************************************************/
/* Creates a Pri Queue. Returns NULL on failure.                             */
PQUEUE *pQCreate(PQIsBefore_t isBef);
/*******************************************************************************/
/* Disposes of resources used by PQueue.                                           */
void pQDestroy(PQUEUE *PQueue);
/*******************************************************************************/
/* insert data to the list , returns 0- success, nonZero- failed                */
int pQEnqueue(PQUEUE *PQueue , void *data);
/*******************************************************************************/
/* Remove item from front of the queue, returns pointer to the data that removed*/
void *pQDequeue(PQUEUE *PQueue);
/*******************************************************************************/
/* return pointer to the data in the front of the queueu without remove it    */
void *pQPeek(const PQUEUE *PQueue);
/*******************************************************************************/
/* Returns 1 if queue is empty. Returns 0 otherwise.                            */
int pQIsEmpty(const PQUEUE *PQueue);
/*******************************************************************************/
/* return the number of elements in the queue                                   */
size_t pQSize(const PQUEUE *PQueue);
/*******************************************************************************/
/* clear all the elements in the queue                  */
void pQClear (PQUEUE *PQueue);

/*******************************************************************************/
/* erase specific node from the list */
void* pQErase (PQUEUE *PQueue , PQIsMatch_t match, const void *data, void *param);

#endif /* __PQUEUE__ */
/*******************************************************************************/
