#include <assert.h> /* assert*/
#include <stdlib.h> /* malloc*/


#include "heap.h"
#include "vector.h"

/*	Opaque Heap structure	*/
struct heap
{
    VECTOR * vector;
    COMP_F cmp;
} ;


/*swap between pointers*/
static void swap (HEAP_T *heap ,int index_child ,int index_parent);
/* sort the way up to the root - after push*/
static void heapifyUp(HEAP_T *heap , int index ,int flag);
/* sort the sub tree - after remove */
static void heapifyDown(HEAP_T *heap , int index , int num_elem);


/*************************************************/

/*	Creates a heap */
HEAP_T *HeapCreate(COMP_F cmp)
{
    HEAP_T *heap_p =NULL;
    /* assert for cmp */

    heap_p = malloc(sizeof(*heap_p));
    /*check if alloc success*/
    if (NULL == heap_p)
    {
        return NULL;
    }

    heap_p->vector = vCreate(4,sizeof(void*));
    /*check if alloc success*/
    if (NULL == heap_p->vector)
    {
        free (heap_p);
        return NULL;
    }
    heap_p->cmp = cmp;
    return heap_p;
}

/*	Pushes 'data' into 'heap'. Returns 0 if successful.
	Returns non-zero otherwise. */
int HeapPush(HEAP_T *heap, const void *data)
{

    int index = 0; /*the index of the vector*/
    /* assert for heap */
    assert(heap != NULL);
    index =  vPush(heap->vector,&data);

    if (index == -1)
    {
        return -1; /* error */
    }
    heapifyUp(heap ,index , 0);

    return 0;
}

/* Finds an element in 'heap', which matches 'data', according to 'IsMatch', and removes it.
   Returns 0 on success. Returns non-zero otherwise (e.g. element is not found).
   IMPORTANT: In the function 'IsMatch', the 1st parameter ('data1') passed will come from 'heap'
   and the 2nd parameter ('data2') passed will be the user supplied 'data'.
   'parameter' is an optional parameter passed into 'IsMatch'. */
   /*************CHANGE TO RETURN VOID********************/
void* HeapRemove(HEAP_T *heap, HEAP_IS_MATCH_F IsMatch, const void *data, void *param)
{
    void *temp;
    int i = 0 ;
    int size = 0;

    assert(heap != NULL);

    size = vSize(heap->vector);
    /*if the array size is null */
    if (HeapIsEmpty(heap))
    {
        return NULL;
    }

    /* find the data index in the vector */
    for (i=0; i< size ; i++)
    {
        if (1 == IsMatch(*(void**)vGetAddress(heap->vector , i), data , param))
        {
            temp = *(void**)vGetAddress(heap->vector , i);
            /* pop the array after get the data */
            heapifyUp(heap , i, 1);
            HeapPop(heap);
            return temp;
        }
    }

    return NULL;
}

/*	Pops the first element in 'heap'. If 'heap' is empty,
    then this call has no effect. */
void HeapPop(HEAP_T *heap)
{
    void** data = NULL;
    int size = 0;

    assert(heap != NULL);

    size = vSize(heap->vector);
    if (size == 0)
    {
        return;
    }

    if (size != 1)
    {
        data =(void**)vGetAddress(heap->vector,0); /*swap data of the root with the last element */
        *data = *(void**)vGetAddress(heap->vector,(size-1));
        heapifyDown(heap ,0 , size-1);
    }

    vPop(heap->vector);
}

/*	Returns a pointer to the data at the beginning of 'heap'.
    Returns NULL if 'heap' is empty. */
void *HeapPeek(const HEAP_T *heap)
{
    assert(heap != NULL);

    return (*(void**)vGetAddress(heap->vector,0));
}

/*	Returns the number of items in 'heap' */
size_t HeapSize(const HEAP_T *heap)
{
    assert(heap != NULL);
    return (vSize(heap->vector));
}

/*	Returns 1 if 'heap' is empty, 0 otherwise. */
int HeapIsEmpty(const HEAP_T *heap)
{
    assert(heap != NULL);

   return (!vSize(heap->vector));
}

/*Disposes of the resources used by 'heap' */
void HeapDestroy(HEAP_T *heap)
{
    vDestroy(heap->vector);
    free(heap);
}

/*************************static functoin **********************/

static void heapifyDown(HEAP_T *heap , int index , int num_elem)
{

    int largest = index;
    int left = 0;
    int right = 0;

    num_elem = vSize(heap->vector);

		left = 2*index + 1;
		right = 2*index + 2;
    /* If left child is larger than root */
    if (left < num_elem && heap->cmp( *(void**)vGetAddress(heap->vector,left), *(void**)vGetAddress(heap->vector,largest)) > 0 )
        largest = left;

    /* If right child is larger than largest so far */
    if (right < num_elem &&heap->cmp( *(void**)vGetAddress(heap->vector,right), *(void**)vGetAddress(heap->vector,largest)) > 0)
        largest = right;

    /*  If largest is not root */
    if (largest != index)
    {
        /*swap between pointers*/
        swap (heap ,index ,largest);

        /* Recursively heapify the affected sub-tree */
        heapifyDown(heap , largest ,num_elem) ;
    }

}
static void heapifyUp(HEAP_T *heap , int index ,int flag)
{

    void *data = NULL; /* the new data element*/
    int parent_index= 0;
    assert(NULL != heap);
    /* get the data of the new element  */
    data = *(void**)vGetAddress(heap->vector,index);

    parent_index = (index -1)/2;
   /*while the data is bigger then the parent data*/
    while (index>0 && (heap->cmp(*(void**)vGetAddress(heap->vector, parent_index ) ,data) < 0 || flag == 1))
    {
        /*place the new data in the right place*/
        swap (heap, index , (index -1)/2 );
        index = parent_index; /* get the index of the parent*/
        parent_index = (index -1)/2;
    }
}

/*swap between pointers*/
static void swap (HEAP_T *heap ,int index_child ,int index_parent)
{

    void ** parent_data = NULL;
    void ** current_data = NULL;
    void *temp = NULL;

    assert(NULL != heap);

    current_data = vGetAddress(heap->vector,index_child);
    parent_data = vGetAddress(heap->vector ,index_parent); /*get the parent data pointer*/

    /* swap */
    temp = *current_data;
    *current_data = *parent_data;
    *parent_data = temp;

}
#ifndef NDEBUG
void  HeapPrint (HEAP_T *heap ,HEAP_P func_p )
{
    int i = 0 ;

    for (i=0; i<vSize(heap->vector); i++)
    {
        func_p(*(void**)vGetAddress(heap->vector , i));
    }

}
#endif








