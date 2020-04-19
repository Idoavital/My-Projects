/*******************************************************************************/
#ifndef	__SORT_L_LIST_H__
#define	__SORT_L_LIST_H__
/*******************************************************************************/

#include <stddef.h>				/*	size_t	*/
#include "DLIter.h"

/*******************************************************************************/
/* Opaque sorted linked list structure                                         */
typedef struct SortL SORT_L;
/*******************************************************************************/
/* iterator for the sorted list                                                */
typedef struct
{
	DL_ITER_T dl_it;
}SORT_ITER_T;
/*******************************************************************************/
/* Boolean function prototype. Returns 1 if 'param1' should be inserted before 
  'param2' in the list. Returns 0 otherwise.                                   */
typedef int (*IsBefore_t) (const void *param1, const void *param2);
/*******************************************************************************/
/*******************************************************************************/
/* Matching (Boolean) function prototype. Compares 'data1' with 'data2' and
   returns 1 if they match and 0 otherwise. 'param' is an optional argument.   */
typedef int (*IsMatch_t) (const void *data1, const void *data2, void *param);
/*******************************************************************************/
/* Creates a sorted list. Returns NULL on failure.                             */
SORT_L *SortCreate(IsBefore_t func);
/*******************************************************************************/
/* Disposes of resources used by sl.                                           */
void SortDestroy(SORT_L *sl);
/*******************************************************************************/
/* Inserts a new element (containing 'data') in 'sl'. Returns an iterator
   pointing at this new element. Returns SortEnd on failure.                   */
SORT_ITER_T SortInsert(SORT_L *sl, void *data);
/*******************************************************************************/
/* Erases the element pointed to by iterator 'it' from list 'sl'.              */
SORT_ITER_T SortErase(SORT_L *sl, SORT_ITER_T it);
/*******************************************************************************/
/* Remove item from end of list                                                */
void SortPopBack(SORT_L *sl);
/*******************************************************************************/
/* Remove item from front of list                                              */
void SortPopFront(SORT_L *sl);
/*******************************************************************************/
/* Returns the number of items in the list.                                    */
size_t SortSize(const SORT_L *sl);
/*******************************************************************************/
/* Returns 1 if list is empty. Returns 0 otherwise.                            */
int SortIsEmpty(const SORT_L *sl);
/*******************************************************************************/
/* Returns data pointed to by iterator 'it'.                                   */
void *SortGetData(SORT_ITER_T it);
/*******************************************************************************/
/* Returns an iterator pointing to the begining of the list.                   */
SORT_ITER_T SortBegin(const SORT_L *sl);
/*******************************************************************************/
/* Returns an iterator pointing to the end of the list.                        */
SORT_ITER_T SortEnd(const SORT_L *sl);
/*******************************************************************************/
/* Traverses the iterator to the next item in the list.                        */
SORT_ITER_T SortNext(SORT_ITER_T it);
/*******************************************************************************/
/* Traverses the iterator to the previous item in the list.                    */
SORT_ITER_T SortPrev(SORT_ITER_T it);
/*******************************************************************************/
/* Returns 1 if iterators 'it1' and 'it2' are the same. Returns 0 otherwise.   */
int SortIsEqual(SORT_ITER_T it, SORT_ITER_T it2);
/*******************************************************************************/
/* Merges list 'src' into list 'dst'                                           */
SORT_ITER_T SortMerge(SORT_L *dst, SORT_L *src);
/*******************************************************************************/
/* Returns iterator pointing at first element, which matches 'data' according to
  'matchFunc'. The search starts from iterator 'it' (including 'it'). 'param' is
  an optional parameter, which is passed to 'matchFunc'.                       */
SORT_ITER_T SortFind(const SORT_L *sl, SORT_ITER_T it, IsMatch_t matchFunc, const void *data, void *param);
/*******************************************************************************/

#endif /* __SORT_L_LIST_H__ */
/*******************************************************************************/
