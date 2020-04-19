#include <stddef.h>	 /*size_t*/


#ifndef	__VSM_H__
#define	__VSM_H__



/*fsm structure*/
typedef struct vsm VSM_T;

/* Initilize VSM data structe. returns 0 for success */ 
VSM_T* VSMInit(void* pool, size_t pool_size); 	

/* Allocate memory for element */ 
void *VSMAlloc(VSM_T *vsm, size_t size_elm);

/* Free element's memory allocation */ 
void VSMFree(void *elem);




/* Returns the number of unused blocks of memory */ 
size_t VSMFreeSpace (const VSM_T *vsm);
#ifdef ADVANCED

/* Returns the size of the large free blocks in memory */
size_t VSMLargeSpace (const VSM_T *vsm);

#endif

#endif 

