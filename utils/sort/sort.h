#ifndef	__SORT_H__
#define	__SORT_H__

#include <stddef.h>	 /*size_t*/


typedef int (* CMP_T)(const void *, const void *);

typedef size_t (* ELM_TO_NUM_T)(const void *data, const void *param);

/*Insertion sort using qsort() signature*/
void InsertionSort(void* base, size_t num, size_t size, CMP_T cmp);

/*Selection sort using qsort() signature*/
void SelectionSort(void* base, size_t num, size_t size, CMP_T cmp);

/*Bubble sort using qsort() signature*/
void BubbleSort(void* base, size_t num, size_t size, CMP_T cmp);

/* Counting sort */
int CountingSort(void *base, size_t num, size_t size, ELM_TO_NUM_T elm_to_num, void *param, size_t keyt_range);

int radixSort (void *base, size_t num, size_t size, ELM_TO_NUM_T elm_to_num, void *param, size_t range);

int mergeSort(void* base, size_t num_elem, size_t size_elem, CMP_T cmp);

void myQuickSort(void* base, size_t num_elem, size_t size_elem , CMP_T cmp);

void heapifySort(void* base, size_t num_elem, size_t size_elem , CMP_T cmp);



#endif /*__SORT_H__*/
