/*******************************************************************************/
#ifndef	__DLLIST_H__
#define	__DLLIST_H__
/*******************************************************************************/

#include <stddef.h>				/*	size_t	*/
#include "DLIter.h"

/*******************************************************************************/
/* Opaque doubly linked list structure*/
typedef struct DList DL_T;
/*******************************************************************************/
/* Remove item from end of list*/
void PopBack(DL_T* dl);
/*******************************************************************************/
/* Add item to end of list. Returns an iterator pointing to this item. */
DL_ITER_T PushBack(DL_T* dl, void *data);
/*******************************************************************************/
/* Remove item from front of list*/
void PopFront(DL_T* dl);
/*******************************************************************************/
/* Add item to front of list. Returns an iterator pointing to this item. */
DL_ITER_T PushFront(DL_T* dl, void *data);
/*******************************************************************************/
/* Creates a doubly linked list. Returns NULL on failure. */
DL_T* DLCreate(void);
/*******************************************************************************/
/* Disposes of resources used by DL. */
void DLDestroy(DL_T *dl);
/*******************************************************************************/
/* Returns the number of items in the list. */
size_t DLSize(const DL_T *dl);
/*******************************************************************************/
/* Returns 1 if list is empty. Returns 0 otherwise. */
int DLIsEmpty(const DL_T *dl);
/*******************************************************************************/
/* Returns data pointed to by iterator 'it'.*/
void* DLGetData(DL_ITER_T it);
/*******************************************************************************/
/* Returns an iterator pointing to the begining of the list. */
DL_ITER_T DLBegin(const DL_T *dl);
/*******************************************************************************/
/* Traverses the iterator to the next item in the list. */
DL_ITER_T DLNext(DL_ITER_T it);
/*******************************************************************************/
/* Traverses the iterator to the previous item in the list. */
DL_ITER_T DLPrev(DL_ITER_T it);
/*******************************************************************************/
/* Returns 1 if iterators 'it' and 'endIt' are the same. Returns 0 otherwise. */
int DLIsEqual(DL_ITER_T it, DL_ITER_T endIt);
/*******************************************************************************/
/* Returns an iterator pointing to the end of the list. */
DL_ITER_T DLEnd(const DL_T *dl);
/*******************************************************************************/
/* Inserts the items in source list (between srcBegin and srcEnd) before position
   pointed to by dst in destnation list.                                      */
void DLSplice(DL_ITER_T dst, DL_ITER_T srcBegin, DL_ITER_T srcEnd);
/*******************************************************************************/
/* Inserts a new element (containing 'data') in 'dl' before the element pointed
   to by iterator 'it'. Returns an iterator pointing at this new element. Returns
   DLEnd on failure. */
DL_ITER_T DLInsert(DL_T *dl, DL_ITER_T it, void *data);
/*******************************************************************************/
/* Erases the element pointed to by iterator 'it' from list 'dl'. */
DL_ITER_T DLErase(DL_T *dl, DL_ITER_T it);
/*******************************************************************************/

#endif /* __DLLIST_H__ */
/*******************************************************************************/
