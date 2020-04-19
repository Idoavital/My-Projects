/* DLIter.h - contains a definition for the iterator used in the doubly linked
   list implementation.*/

/*******************************************************************************/
#ifndef	__DL_ITER_H__
#define	__DL_ITER_H__

typedef struct Node_dl_t DL_NODE_T;

/* Opaque iterator for DL */
#ifdef XOR

typedef struct 
{
	DL_NODE_T *adj;
	DL_NODE_T *curr;

} DL_ITER_T;

#else
typedef DL_NODE_T* DL_ITER_T;
#endif

#endif /* __DL_ITER_H__ */
