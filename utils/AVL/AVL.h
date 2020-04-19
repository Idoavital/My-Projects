#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

#include "AVL.h"

/* Opaque AVL tree structure */
typedef struct avl AVL_T;

/* Comparison function: Returns a positive integer if data1 > data2,
   a negative integer if data1 < data2 and 0 if data1 == data2.
   'param' is an optional argument. */
typedef int (*COMP_T) (const void *data1, const void *data2);

/* Action function, which receives an element in an AVL tree and returns 0 for success and
   non-zero otherwise. */
typedef int (*ACTION_T)(void *data, void *param);

/* Creates an AVL tree */
AVL_T *AVLCreate(COMP_T cmp);

/* Disposes of the resources used by 'avl' */
void AVLDestroy(AVL_T *avl);

/* Inserts 'data' into the AVL. Returns 0 if successful.
   Returns non-zero otherwise. */
int AVLInsert(AVL_T *avl, const void *data);

/* Removes 'data' from 'avl'. Returns 0 if 'data' was found in 'avl'.
   Returns non-zero otherwise. */
int AVLRemove(AVL_T *avl, const void *data);

/* Returns the height of 'avl' */
size_t AVLHeight(const AVL_T *avl);

/* Returns the number of items in the AVL (in O(n) time)*/
size_t AVLSize(const AVL_T *avl);

/* Returns 1 if 'AVL' is empty, 0 otherwise (in O(1) time)*/
int IsEmpty(const AVL_T *avl);

/* Executes function 'action' on each element in 'AVL' (as long as 'action' returns success).
   Returns 0 for success, non-zero otherwise. 'param' is an optional parameter passed into 'action'.
   Traverses the tree IN ORDER. */
int AVLForEach(AVL_T * avl ,  ACTION_T action, void *param);

void print_n(AVL_T *avl);

/* return pointer to data of the node , return null if not found*/
void *AVLFind( AVL_T *avl, const void *data);

#endif /* __AVL_H__ */
