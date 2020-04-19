#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

/* Opaque Binary Search Tree structure */
typedef struct bst_t BST_T;

/* Opaque Binary Search Tree iterator */
typedef void *BST_ITER;

/* Comparison function: Returns a positive integer if data1 > data2, 
   a negative integer if data1 < data2 and 0 if data1 == data2.
   'param' is an optional argument. */
typedef int (*COMP_T) (const void *data1, const void *data2, void *param);

/* Action function, which receives an element in a BST and returns 0 for success and
   non-zero otherwise. */
typedef int (*ACTION_T)(void *data, void *param);


/* Creates a Binary Sorted Tree */
BST_T *BSTCreate(COMP_T cmp, void *param);		/**/

/* Disposes of the resources used by a Binary Search Tree */
void BSTDestroy(BST_T *bst);

/* Returns the number of items in the BST (in O(n) time)*/		/**/
size_t BSTCount(const BST_T *bst);

/* Returns 1 if 'bst' is empty, 0 otherwise (in O(1) time)*/ /**/
int IsEmpty(const BST_T *bst);

/* Returns the data in the element pointed to by iterator 'it'*/  /**/ 
void *BSTGetData(BST_ITER it);

/* Inserts 'data' into the BST. Returns an iterator representing the element. 
   Returns BSTEnd() if unsuccessful */  									/**/
BST_ITER BSTInsert(BST_T *bst, void *data);

/* Removes element pointed to by iterator 'it' from the BST. 
   Returns the data in the element. */									/**/
void *BSTRemove(BST_ITER it);

/* Returns an iterator pointing to the first element in 'bst' */		/**/
BST_ITER BSTBegin(const BST_T *bst);

/* Returns an iterator representing the end of 'bst' */				/**/
BST_ITER BSTEnd(const BST_T *bst);

/* Traverses the iterator to the next element in the BST. */			/**/
BST_ITER BSTNext(BST_ITER it);

/* Traverses the iterator to the previous element in the BST. */		/**/
BST_ITER BSTPrev(BST_ITER it);

/* Returns 1 if 'it1' is the same as 'it2'. Returns 0 otherwise. */		/**/
int BSTIsSameIter(BST_ITER it1, BST_ITER it2);

/* Returns 1 if 'it' is an invalid iterator. Returns 0 otherwise. */	/**/
int BSTIsBadIter(BST_ITER it);

/* Returns iterator pointing at first element, which matches 'data'.	
   If the element is not found, returns BSTEnd(). */
BST_ITER BSTFind(const BST_T *bst, const void *data);				/**/

/* Executes function 'action' on each element in 'bst' (as long as 'action' returns success).
   Returns 0 for success, non-zero otherwise. 'param' is an optional parameter passed into 'action'. */   /**/
int BSTForEach(BST_ITER from, BST_ITER to, ACTION_T action, void *param);
 

#endif /* __BST_H__ */
