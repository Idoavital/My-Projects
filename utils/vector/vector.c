#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy*/

#include "vector.h"

struct Vector
{
	size_t sizeOfElm; /* size of one element in the array*/
	size_t capacity; /* the memory size of the array (in index) */
	size_t top;		/*the size of the */
	char * dataArr;

};

/* crate a dynamic array */
/* return NULL on failure */
VECTOR * vCreate(size_t initialSize, size_t sizeOfElm)
{

	VECTOR *v = (VECTOR*) calloc(1,sizeof(VECTOR));
	if (NULL == v)
	{
		return NULL;
	}
	v -> dataArr = (char*) calloc (1,sizeOfElm * initialSize) ;
	if (NULL == v->dataArr )
	{
		free (v);
		return NULL;
	}

	v-> sizeOfElm = sizeOfElm;
	v-> top = 0;
	v-> capacity = initialSize;

	return v;
}

/* insert a object to the top of the array*/
/* returns size. returns -1 on failure */

int vPush (VECTOR* v, void* object)
{
	char * temp;

	assert(v != NULL && "v can't be null");

	if (v->top == v->capacity) /* check if the top of array come to the limit of the memory*/
	{							/* if the array come to the limit , then we realloc */

		v->capacity == 0 ?  v->capacity = 2 :  (v->capacity *= 2 ); /* in a case capacity is 0*/
		temp = (char*) realloc (v->dataArr, v->sizeOfElm * v->capacity);
		if (NULL == v->dataArr )
		{
			v->capacity /= 2;
			return -1;
		}

		v->dataArr = temp ;

	}
	memcpy (v->dataArr+(v->sizeOfElm * v->top), object , v-> sizeOfElm);
	v->top++;

	return v->top-1;
}

/* delete the last member in the array */
void vPop(VECTOR* v)
{
	char * temp;
	assert(v != NULL && "v can't be null");


	if (0 == v->top )
	{
		return;
	}
	v->top--;
	if (v->top <= (v->capacity / 4) ) /* check if there is more then 75% un use memory */
	{
		temp = (char*)realloc(v->dataArr,(v->capacity*v->sizeOfElm )/ 2);
		if (NULL != temp)
		{
			v->capacity /= 2;
			v->dataArr = temp;
		}

	}

}

/* returns address of item at index newSize - 1 or address of first item?. returns NULL on failure. */
size_t vResize(VECTOR* v, size_t newSize)
{
	char * temp = v->dataArr;

	assert(v != NULL && "v can't be null");
	if (newSize >= v->capacity) /* if the new size is out of memory then realloc */
	{
		temp = (char*) realloc (v->dataArr, 2 * v->sizeOfElm * newSize);
		if (NULL == temp)
		{
			return -1;
		}
		v->capacity = 2 * newSize ;
	}

	else if ( newSize < (v->capacity /4) ) /* if there is more then 75% un use memory then realloc */
	{
		temp = (char*)realloc(v->dataArr,(v->capacity* v->sizeOfElm)/ 2);
		if (NULL == temp)
		{
			return -1;
		}
		v->capacity /= 2;
	}

	v->dataArr = temp;
	v->top = newSize;

	return v->top;
}



/* return NULL on overflow or let the user fail later ?*/
void* vGetAddress(VECTOR* v, size_t index)
{
	assert(v != NULL && "v can't be null");

	if( index > v->capacity)
	{
		return NULL;
	}
	return (v->dataArr + index * v->sizeOfElm);
}

/*delete the vector and free the memory*/
void vDestroy(VECTOR* v)
{
	assert(v != NULL && "v can't be null");
	free (v->dataArr);
	v->dataArr = NULL;
	free (v);
}

/* return the capacity of the vector*/
size_t vCapacity(const VECTOR* v)
{
	assert(v != NULL && "v can't be null");

	return v->capacity;
}

/* return the size of the array in the vector*/
size_t vSize(const VECTOR* v)
{
	assert (v != NULL && " V can't be null %d");
	return v->top;
}























