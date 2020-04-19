#ifndef __VECTOR_H__

#define __VECTOR_H__

#include <stddef.h> /*size_t*/

typedef struct Vector VECTOR;

/* crate a dynamic array */
/* return NULL on failure */
VECTOR* vCreate(size_t initialSize, size_t sizeOfElm);

/* returns size. returns zero on failure */
int vPush(VECTOR* v, void* object);

/* return NULL on overflow or let the user fail later ?*/
void* vGetAddress(VECTOR* v, size_t index);

/* returns address of item at index newSize - 1 or address of first item?. returns NULL on failure. */
size_t vResize(VECTOR* v, size_t newSize);

/* delete the last member in the array */
void vPop(VECTOR* v);

/*delete the vector and free the memory*/
void vDestroy(VECTOR* v);

/* return the capacity of the vector*/
size_t vCapacity(const VECTOR* v);

/* return the size of the array in the vector*/
size_t vSize(const VECTOR* v);

#endif /* __VECTOR_H__ */
