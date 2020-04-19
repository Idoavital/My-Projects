#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <stdio.h>
#include <math.h> /* log */ /* Square*/

#include "sort.h"

#define DIGIT_MASK 255
#define DIGIT_NUM 8

typedef struct array_ptr_t
{
	size_t  *ptr ;
	 size_t key ;
  }
ARRAY_PTR_T ;

/*	swap btween two data 	*/
static void swap (void* data_1, void* data_2, size_t elm_size, void *temp  );
/*order the data array  according to the pointers in the sort array */
static void PtrKeyToData(void *data, ARRAY_PTR_T *sort , size_t num, size_t size);
/*return value of  the digit index (param) or bitis indexes(param) in the number*/
static size_t  numToDigit (const void *data, const void *param);
/* the functoin build a pointer array of struct that include key and ptr */
static void dataToPtrKey(void *base, size_t num_elem, size_t size_elem ,ARRAY_PTR_T * ptrArray, ELM_TO_NUM_T elm_to_num, const void *param );

static void CountingS (void * unsort , void * sort , size_t * LUT ,  ELM_TO_NUM_T elm_to_num , size_t range , size_t num ,size_t size, const void *param );

static void mergeSortHelper(void* arr_1, void *arr_2 , int begin , int end , size_t size_elem, CMP_T cmp);

static void merge (char* arr_1, char *arr_2 , int begin ,int middle, int end , size_t size_elem, CMP_T cmp);

static void myQuickSortHelper(void* base, int low, int high , size_t size_elem , CMP_T cmp , void * temp);

static void heapifyHelper (char* base, int begin , int end , size_t size_elem , CMP_T cmp, void * temp);

static int partition(void* base, int low, int high , size_t size_elem , CMP_T cmp , void * temp);

/****************************************************************************/
/*Bubble sort using qsort() signature*/
void BubbleSort(void* base, size_t num, size_t size, CMP_T cmp)
{
	int i = 0; /* first  loop */
	int k = 0; /* second loop*/
	int run_flag = 1; /* flag for check if the array is sorted befor the end of the loop*/
	char *data_1 = NULL;
	char *data_2 = NULL;
	void *temp = NULL;
	temp = malloc (size);

	for (i = 0 ; i < num - 1 && run_flag == 1; i++)
	{
		run_flag = 0;

		for (k = 0; k < num -1 - i ; k++)
		{
			data_1 = ((char*)base)+ (k*size);
			data_2 = ((char*)base)+ ((k+1) *size);
			if (cmp( (data_1 ) ,( data_2) ) > 0 )
			{
				swap ( data_1,data_2, size , temp );
				run_flag = 1;
			}
		}
	}

	free (temp);
	temp = NULL;
}

/****************************************************************************/
/*Selection sort using qsort() signature*/
void SelectionSort(void* base, size_t num, size_t size, CMP_T cmp)
{
	int i = 0; /* first  loop */
	int k = 0; /* second loop*/
	int min = 0;

	void *temp = NULL;
	temp = malloc (size);

	for (i = 0 ; i< num - 1 ; i++ )
	{
		min= i;
		for (k =i+1; k < num ; k++)
		{
			if (cmp(( ((char*)base)+ (min*size) ) ,( ((char*)base)+ (k *size)) ) > 0 )/* find the minum number */
			{
				min = k ; /* replace the minum number */
			}
		}

		if (i != min)
		{
			swap ( ((char*)base)+ (i*size), ((char*)base)+ (min *size), size  , temp);
		}

	}

	free (temp);
	temp = NULL;
}
/****************************************************************************/
/*Insertion sort using qsort() signature*/
void InsertionSort(void* base, size_t num, size_t size, CMP_T cmp)
{
	int i = 0; /* first  loop */
	int k = 0; /* second loop*/
	void *key = NULL;

	int count = 0;


	key = malloc (size);
	for (i = 1 ; i < num ; i ++)
	{
		count = 0;
		memmove (key,( (char*)base)+ ((i) * size), size);

		for (k = i-1 ; k >=0 && (cmp (( (char*)base)+ ((i) * size), ((char*)base)+ ((k) * size)) < 0 ) ;k-- )
		{
			count++; /* count the size of the block */
		}
		 /* copy the block , and after place the key in */
		memmove (( ((char*)base)+ ((k+2) * size))   , ( ((char*)base)+ ((k+1) * size) ), count* size  );
		memmove (( ((char*)base)+ ((k+1) * size)),  key , size  );
	}

	free(key);
	key = NULL;
}
/******************************************counting sort O(n) ***************************************************/
int CountingSort(void *base, size_t num, size_t size, ELM_TO_NUM_T elm_to_num, void *param, size_t range)
{
	size_t *LUT = NULL;

	void *temp_base = NULL;

	range++;
	LUT = (size_t *) calloc (range , sizeof(size_t));
	temp_base = malloc (num * size);

	if (NULL == temp_base)
	{
		return 1;
	}

	if (NULL == LUT)
	{
		free (temp_base);
		return 1;
	}

	CountingS (base , temp_base , LUT ,  elm_to_num ,range ,  num , size, param );

	memmove (base, (char *)temp_base , size*num);
	free(temp_base);
	free(LUT);

	return 0;
}

/******************************************radix  sort O(n) ***************************************************/
int radixSort (void *base, size_t num, size_t size, ELM_TO_NUM_T elm_to_num, void *param, size_t range)
{
	size_t i = 0 ;
	ARRAY_PTR_T *ptr_key_1 = NULL; /* struct of pointer and key of the base */
	ARRAY_PTR_T *ptr_key_2 = NULL;/* struct of pointer and key of the base	*/
	int flag = 0;
	void *lut = NULL; /* for the LUT of the counting sort function */
	size_t key_range = DIGIT_MASK+1;
	int num_of_iter = 0;


	ptr_key_1 = malloc (sizeof(ARRAY_PTR_T) * num) ;
	if (ptr_key_1 == NULL)
	{
		return 1;
	}

	ptr_key_2 = malloc (sizeof(ARRAY_PTR_T) * num) ;
	if (ptr_key_2 == NULL)
	{
		free (ptr_key_1);
		return 1;
	}


	lut = calloc (sizeof(size_t) , key_range+1) ;
	if (lut == NULL)
	{
		free (ptr_key_1);
		free (ptr_key_2);
		return 1;
	}

	dataToPtrKey(base, num , size  , ptr_key_1, elm_to_num ,param );


	/* number of iteratoin*/
	num_of_iter = ceil (log(range) / log (DIGIT_MASK+1));

	/*sort unsorted into sorted*/
	for ( i =0 ; i< num_of_iter ; i++ )
	{
		flag = i&1l ;
		if ( flag )
			CountingS (ptr_key_2 , ptr_key_1 , lut ,  numToDigit , key_range+1 ,  num , sizeof(ARRAY_PTR_T) , &i );
		else
			CountingS (ptr_key_1 , ptr_key_2 , lut ,  numToDigit , key_range+1 ,  num , sizeof(ARRAY_PTR_T) , &i );

		memset (lut, 0, ((key_range+1)  * sizeof(size_t))); /* set to zero the LUT */
	}

	if (flag)
		PtrKeyToData(base , ptr_key_2,  num,  size);
	else
		PtrKeyToData(base , ptr_key_1,  num,  size);

	free (ptr_key_1);
	free (ptr_key_2);
	free (lut);
	return 0;

}
/******************************************mergeSort  sort O(log-n) ***************************************************/

 int mergeSort(void* base, size_t num_elem, size_t size_elem, CMP_T cmp)
{

     void * temp_arr = calloc(1, size_elem * num_elem);

     if (temp_arr == NULL)
     {
         return 1;
     }
     memmove(temp_arr, base , num_elem* size_elem);
     mergeSortHelper( temp_arr, base ,0 , num_elem , size_elem, cmp);

     free(temp_arr);
        return 0;
}

void myQuickSort(void* base, size_t num_elem, size_t size_elem , CMP_T cmp)
{
    void * temp = NULL;
    temp = malloc(size_elem);
    myQuickSortHelper(base ,0  , num_elem-1, size_elem, cmp, temp);
}

/******************************************heapifySort  sort O(log-n) ***************************************************/
void heapifySort(void * base, size_t num_elem, size_t size_elem , CMP_T cmp)
{
    int i = 0;
    void * temp = NULL;
    temp = malloc(size_elem);

    for ( i = (num_elem/2 -1); i>=0 ; i -- )
    {
        heapifyHelper( base, num_elem , i ,size_elem ,cmp ,temp);
    }

    for (i = (num_elem-1) ; i>=0; i--)
    {
        swap(base , (char*)base+ i*size_elem, size_elem, temp );
        heapifyHelper( base, i , 0 , size_elem ,cmp , temp);
    }
}


/*******************************************static functoins *********************************************************/


static void heapifyHelper (char* base, int num_elem , int begin , size_t size_elem , CMP_T cmp, void * temp)
{
    int largest = begin;
    int left = 0;
    int right = 0;

		left = 2*begin + 1;
		right = 2*begin + 2;
    /* If left child is larger than root */
    if (left < num_elem && cmp (base + left*size_elem ,base + largest*size_elem ) > 0 )
        largest = left;

    /* If right child is larger than largest so far */
    if (right < num_elem &&cmp (base + right*size_elem ,base + largest*size_elem ) > 0)
        largest = right;

    /*  If largest is not root */
    if (largest != begin)
    {
        swap(base+ begin*size_elem, base+ largest*size_elem , size_elem, temp);

        /* Recursively heapify the affected sub-tree */
        heapifyHelper(base ,num_elem, largest ,size_elem ,cmp , temp) ;
    }

}

static void myQuickSortHelper(void* base, int low, int high , size_t size_elem , CMP_T cmp , void * temp)
{
    int part = 0;
    if (low < high)
    {
        part = partition(base, low,  high ,  size_elem ,  cmp , temp);

        myQuickSortHelper(base ,low,part-1 ,size_elem , cmp , temp);
        myQuickSortHelper(base ,part +1 , high, size_elem, cmp, temp );
    }

}

static int partition(void* base, int low, int high , size_t size_elem , CMP_T cmp ,void * temp)
{
    void* pivot = NULL;
    int i = low-1;
    int j = 0;

    pivot = (char*)base +high * size_elem; /* pivot  */


    for (j = low; j <= high- 1; j++)
    {
        /* If current element is smaller than or
         equal to pivot */
        if (cmp(pivot , ((char*)base + j*size_elem) ) >0 )/*arr[j] <= pivot)*/
        {
            i++;    /* increment index of smaller element */
            swap((char*)base + i*size_elem , (char*)base + j*size_elem, size_elem , temp );
        }
    }
    swap((char*)base + (i+1)*size_elem, (char*)base + high *size_elem,size_elem , temp);
    return (i + 1);
}



static void swap (void* data_1, void* data_2, size_t elm_size, void *temp  )
{
	memcpy (temp , data_1 ,elm_size );
	memcpy (data_1 , data_2 ,elm_size );
	memcpy (data_2 , temp ,elm_size );
}

static void PtrKeyToData(void *data, ARRAY_PTR_T *sort , size_t num, size_t size)
{
	size_t i = 0;
	void *sorted_data = NULL;

	sorted_data = malloc(size * num);

	for (i = 0; i < num; i++)
	{
		memcpy((void *)((char *)sorted_data + i *size), sort[i].ptr , size);
	}

	memcpy(data , sorted_data , num * size);

	free(sorted_data);
}


static void dataToPtrKey(void *base, size_t num_elem, size_t size, ARRAY_PTR_T * ptrArray, ELM_TO_NUM_T elm_to_num, const void *param )
{
	int i =0 ;
	for ( i = 0 ; i < num_elem ;i++ )
	{
		ptrArray[i].ptr = (size_t *)((char*)base + i * size);
		ptrArray[i].key = elm_to_num((char*)base + i * size, param);
	}
}

static size_t  numToDigit (const void *data, const void *param)
{
	size_t ret = 0;
	size_t temp_data = ((ARRAY_PTR_T *)data)->key;
	size_t num =  *(size_t*)param;


	temp_data = temp_data>>((DIGIT_NUM) * num);
	ret = temp_data  &  DIGIT_MASK;

	return ret;
}

/*
static size_t  numToDigit (const void *data, const void *param)
{
	size_t ret = 0;
	size_t temp_data = ((ARRAY_PTR_T *)data)->key;
	size_t num =  *(size_t*)param;


	temp_data = ( num == 0 ? temp_data : temp_data/(10 * num ));
	ret = temp_data % 10;

	return ret;
}*/

static void CountingS (void * unsort , void * sort , size_t * LUT ,  ELM_TO_NUM_T elm_to_num , size_t range , size_t num ,size_t size, const void *param )
{
	int i =0;
	void *data = NULL;

	/*set LUT*/
	for (i = 0; i < num; i++)
	{
		LUT[elm_to_num(((char *)unsort + (i * size)), param)]++;
	}

	/*set OffSet*/
	for (i = 1; i < range; LUT[i] += LUT[i - 1], i++);

	/*sort base into temp_base*/
	for (i = num ; i != 0 ; i--)
	{


		data = (void *)((char *)unsort + (i - 1) * size);
		memcpy (((void *)((char *)sort + (size * (LUT[elm_to_num(data, param )]-1)))), data , size);
		LUT[elm_to_num(data, param)]--;
	}

}



static void mergeSortHelper(void* arr_2, void *arr_1 , int begin , int end , size_t size_elem, CMP_T cmp)
{
    int middle = 0 ;
    if (end-begin < 2) /* if no more sub array*/
    {
        return ;
    }

    /*split the array  longer than 1 item into halves */
    middle = (end + begin) / 2;

    mergeSortHelper(arr_1, arr_2 , begin,  middle, size_elem , cmp);  /* sort the left  array */
    mergeSortHelper(arr_1, arr_2 , middle, end,  size_elem , cmp);  /* sort the right run */

    /* merge the resulting array from array */
    merge(arr_2, arr_1 ,begin, middle, end, size_elem , cmp);
}

static void merge (char* arr_1, char *arr_2 , int begin ,int middle, int end , size_t size_elem, CMP_T cmp)
{
    int i = begin ;
    int j = middle ;
    int k = 0 ;

    for ( k = begin ; k< end ; k++)
    {
        if (i < middle && ( j >= end || 0 >= cmp((arr_1+size_elem*i) ,(arr_1+size_elem*j ))))
        {
            memmove(arr_2+ (k*size_elem), (arr_1+ size_elem*i), size_elem );
            i++;
        }
        else
        {
            memmove(arr_2 +(k*size_elem), (arr_1+ size_elem*j), size_elem);
            j++;
        }
    }

}
