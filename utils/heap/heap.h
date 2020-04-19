#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>		/*	size_t	*/

/*	Comparison function: Returns a positive integer if data1 > data2,
	a negative integer if data1 < data2 and 0 if data1 == data2. */
typedef int (* COMP_F) (const void *data1, const void *data2);

/* Returns 1 if 'data1' and 'data2' match. Return 0 otherwise.
   'param' is an optional parameter. */
typedef int (*HEAP_IS_MATCH_F)(const void *data1, const void *data2 , void *param);

/*	Opaque Heap structure	*/
typedef struct heap HEAP_T;

/*	Creates a heap */
HEAP_T *HeapCreate(COMP_F cmp);

/*	Disposes of the resources used by 'heap' */
void HeapDestroy(HEAP_T *heap);

/*	Pushes 'data' into 'heap'. Returns 0 if successful.
	Returns non-zero otherwise. */
int HeapPush(HEAP_T *heap, const void *data);

/*	Pops the last element in 'heap'. If 'heap' is empty,
    then this call has no effect. */
void HeapPop(HEAP_T *heap);

/*	Returns a pointer to the data at the beginning of 'heap'.
    Returns NULL if 'heap' is empty. */
void *HeapPeek(const HEAP_T *heap);

/*	Returns the number of items in 'heap' */
size_t HeapSize(const HEAP_T *heap);

/*	Returns 1 if 'heap' is empty, 0 otherwise. */
int HeapIsEmpty(const HEAP_T *heap);

/* Finds an element in 'heap', which matches 'data', according to 'IsMatch', and removes it.
   Returns 0 on success. Returns non-zero otherwise (e.g. element is not found).
   IMPORTANT: In the function 'IsMatch', the 1st parameter ('data1') passed will come from 'heap'
   and the 2nd parameter ('data2') passed will be the user supplied 'data'.
   'parameter' is an optional parameter passed into 'IsMatch'. */
void* HeapRemove(HEAP_T *heap, HEAP_IS_MATCH_F IsMatch, const void *data, void *param);

#ifndef NDEBUG

typedef void (*HEAP_P)(void * data);
void  HeapPrint (HEAP_T *heap ,HEAP_P func_p );

#endif

#endif /* __HEAP_H__ */
