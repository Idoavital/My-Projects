
#ifndef	__FSM_H__
#define	__FSM_H__


#include <stddef.h>	 /*size_t*/

/*fsm structure*/
typedef struct fsm FSM_T;

/* return the suggested size of allocation in bytes, according to user demand */
size_t FSMSuggesteSize(size_t no_elem, size_t size_elem);

/* Initilize FSM data structe. returns 0 for success */ 
FSM_T * FSMInit(void *pool, size_t no_elem, size_t size_elem);

/* Allocate memory for element */ 
void *FSMAlloc(FSM_T *fsm);

/* Free element's memory allocation */ 
void FSMFree(void *elem);

/* Returns the number of unused blocks of memory */ 
size_t FSMFreeCount (const FSM_T *fsm);

#endif /*FSM*/

