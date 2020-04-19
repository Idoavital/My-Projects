#ifndef __MT_SORT_H__
#define __MT_SORT_H__

#include <stddef.h>     /* size_t */

typedef int (*CMP_T)(const void *, const void *);

int MT_Sort(void* base, size_t num, size_t size, CMP_T cmp, size_t noOfThreads);

#endif /* __MT_SORT_H__ */
