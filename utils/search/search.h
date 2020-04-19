#ifndef	__SORT_H__
#define	__SORT_H__

#include <stddef.h>	 /*size_t*/

typedef int (* CMP_T)(const void *, const void *);

void * binarySearch(void* base, size_t num_elem, size_t size_elem , CMP_T cmp ,const void * data);

void * binarySearchIterative(void* base, size_t num_elem, size_t size_elem , CMP_T cmp ,const void * data);

void * jumpSearch(void* base, size_t num_elem, size_t size_elem , CMP_T cmp ,const void * data);


#endif /*__SORT_H__*/
