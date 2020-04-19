#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort.h"

#define SIZE 20000
#define RANGE 10000

typedef struct person
{
	char name[10] ;
	int age;
}
PERSON;

size_t ToInt(const void *data, const void *param);

static void randomArr1(char *arr, int size);

size_t prsomToNum(const void *data, const void *param) ;

static void testInsertionSort ();

static void testBubbleSort ();

static void testSelectionSort ();

static void testRadixSort();

static void sortComptaion ();

static void testMergeSort ();

static void testMyQuickSort ();

static void testheapifySort ();

int cmprchar (const void * data_1, const void * data_2);

static void randomArr(int *arr, int size);

int cmprAge (const void * data1, const void * dat2);

int cmprName (const void * data_1, const void * data_2);

int cmprInt (const void * data_1, const void * data_2);

PERSON rd38[] = {
{"ido-1",35},
{"evgeni",34},
{"dani-1",2},
{"maayan",24},
{"guy-2",2},
{"beni",32},
{"eli",29},
{"moshe-2",35},
	{"violet", 3},
	{"john", 400},
	{"alex", 1},
	{"gary", 12},
	{"samwise", 26},
	{"harry", 27},
	{"conway", 30},
	{"vlad", 45},
	{"jane", 77},
	{"golem", 555},
};

static int arr[10] = {2, 5, 4, 3, 9, 0, 0, 1, 4, 3};

int main (int argc, char *argv[])
{
	int i = 0;

	for (i = 0 ; i < 10 ; i++)
	{
		printf ("%d, ",arr[i]);
	}

	printf("\n");

	CountingSort(arr, 10, sizeof(int), ToInt, NULL, 9);

	for (i = 0 ; i < 10 ; i++)
	{
		printf ("%d, ",arr[i]);
	}

	printf("\n");

    testRadixSort();
    testMyQuickSort ();
	testheapifySort ();
	testBubbleSort ();
	testSelectionSort ();
	testInsertionSort ();
    testMergeSort ();

	sortComptaion ();




	return 0;
}



static void testRadixSort()
	{
	int i =0;
        printf ("************ test radixSort by age  ********* \n ");

        radixSort (rd38, 14,  sizeof(PERSON), prsomToNum, NULL , 556);

        for (i = 0; i < 14 ; i++)
        {
            printf ("name %s age %d \n", rd38[i].name , rd38[i].age );
        }
    }

static void testInsertionSort ()
{
	int i =0;


	printf ("************ test InsertionSort by age  ********* \n ");
	InsertionSort(&rd38[0], 18, sizeof(PERSON), cmprAge);
	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

	printf ("************ test InsertionSort by name  ********* \n ");
	InsertionSort(&rd38[0], 18, sizeof(PERSON), cmprName);
	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}


}
static void testSelectionSort ()
{
	int i =0;


	printf ("************ test testSelectionSort by age  ********* \n ");
	SelectionSort(&rd38[0], 18, sizeof(PERSON), cmprAge);
	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

	printf ("************ test testSelectionSort by name  ********* \n ");
	SelectionSort(&rd38[0], 18, sizeof(PERSON), cmprName);
	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

}

static void testBubbleSort ()
{
	int i =0;


	printf ("************ test testBubbleSort by age  ********* \n ");
	BubbleSort(&rd38[0], 18, sizeof(PERSON), cmprAge);
	for (i = 0 ; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

	printf ("************ test testBubbleSort by name  ********* \n ");
	BubbleSort(&rd38[0], 18, sizeof(PERSON), cmprName);

	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}



}

static void testMergeSort ()
{
	int i =0;


	printf ("************ test mergeSort by age  ********* \n ");
	mergeSort(&rd38[0], 18, sizeof(PERSON), cmprAge);
	for (i = 0; i < 18 ; i++)
	{

		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

	printf ("************ test mergeSort by name  ********* \n ");
	mergeSort(&rd38[0], 18, sizeof(PERSON), cmprName);
	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}


}

static void testMyQuickSort ()
{
	int i =0;


	printf ("************ test testMyQuickSort by age  ********* \n ");
	myQuickSort(&rd38[0], 18, sizeof(PERSON), cmprAge);
	for (i = 0; i < 18 ; i++)
	{

		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

	printf ("************ test testMyQuickSort by name  ********* \n ");
	myQuickSort(&rd38[0], 18, sizeof(PERSON), cmprName);
	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}


}

static void testheapifySort ()
{
	int i =0;

	printf ("************ test testheapifySort by age  ********* \n ");
	heapifySort(&rd38[0], 18, sizeof(PERSON), cmprAge);
	for (i = 0; i < 18 ; i++)
	{

		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

	printf ("************ test testheapifySort by name  ********* \n ");
	heapifySort(&rd38[0], 18, sizeof(PERSON), cmprName);
	for (i = 0; i < 18 ; i++)
	{
		printf (" name %s age %d \n", rd38[i].name , rd38[i].age );
	}

}

static void sortComptaion ()
{

	clock_t start;
	clock_t end;
	int arr[SIZE];
	char charArr[SIZE];

	printf ("***************** best sort of random arrray ********************\n");
	randomArr(arr, SIZE);
	start =  clock();
	BubbleSort(arr, SIZE, sizeof(int), cmprInt);
	end = clock();
	printf ("time BubbleSort %0.2f \n", (double)(end-start) );

	randomArr(arr, SIZE);
	start =  clock();
	SelectionSort(arr, SIZE, sizeof(int), cmprInt);
	end = clock();
	printf ("time SelectionSort %0.2f \n", (double)(end-start) );

	randomArr(arr, SIZE);
	start =  clock();
	InsertionSort(arr, SIZE, sizeof(int), cmprInt);
	end = clock();
	printf ("time InsertionSort %0.2f  \n", (double)(end-start) );

	randomArr(arr, SIZE);
	start =  clock();
	qsort(arr, SIZE, sizeof(int), cmprName);
	end = clock();
	printf ("time qsort %0.2f  \n", (double)(end-start) );

	randomArr(arr, SIZE);
	start =  clock();
	radixSort (arr, SIZE,  sizeof(int), ToInt, NULL , 	RANGE);
	end = clock();
	printf ("time radixSort %0.2f  \n", (double)(end-start) );


	randomArr(arr, SIZE);
	start =  clock();
	CountingSort(arr, SIZE, sizeof(int), ToInt, &arr , RANGE);
	end = clock();
	printf ("time CountingSort %0.2f  \n", (double)(end-start) );


	randomArr(arr, SIZE);
	start =  clock();
	mergeSort(arr, SIZE, sizeof(int), cmprInt);
	end = clock();
	printf ("time mergeSort %0.2f  \n", (double)(end-start) );

  randomArr(arr, SIZE);
	start =  clock();
	myQuickSort(arr, SIZE, sizeof(int), cmprInt);
	end = clock();
	printf ("time myQuickSort %0.2f  \n", (double)(end-start) );

	randomArr(arr, SIZE);
	start =  clock();
	heapifySort(arr, SIZE, sizeof(int), cmprInt);
	end = clock();
	printf ("time heapifySort %0.2f  \n", (double)(end-start) );

	printf ("***************** best sort of sorted arrray ********************\n");
	qsort(arr, SIZE, sizeof(int), cmprName);
	start =  clock();
	BubbleSort(arr, SIZE, sizeof(int), cmprName);
	end = clock();
	printf ("time BubbleSort %f \n", (double)(end-start) );

	qsort(arr, SIZE, sizeof(int), cmprName);
	start =  clock();
	SelectionSort(arr, SIZE, sizeof(int), cmprName);
	end = clock();
	printf ("time SelectionSort %f \n", (double)(end-start) );


	qsort(arr, SIZE, sizeof(int), cmprName);
	start =  clock();
	InsertionSort(arr, SIZE, sizeof(int), cmprName);
	end = clock();
	printf ("time InsertionSort %f \n", (double)(end-start) );

	qsort(arr, SIZE, sizeof(int), cmprName);
	start =  clock();
	myQuickSort(arr, SIZE, sizeof(int), cmprName);
	end = clock();
	printf ("time myQuickSort %f \n", (double)(end-start) );



	printf ("***************** best sort char of random arrray ********************\n");
	randomArr1(charArr, SIZE);
	start =  clock();
	BubbleSort(arr, SIZE, sizeof(char), cmprchar);
	end = clock();
	printf ("time BubbleSort %f \n", (double)(end-start) );



	randomArr1(charArr, SIZE);
	start =  clock();
	SelectionSort(charArr, SIZE, sizeof(char), cmprchar);
	end = clock();
	printf ("time SelectionSort %f \n", (double)(end-start) );




}

size_t ToInt(const void *data, const void *param)
{
	return (size_t)(*((int *)data));
}

static void randomArr(int *arr, int size)
{
	int i =0;
	srand (time(NULL));
	for ( i = 0 ; i<size ; i++)
	{
		arr[i] = rand()%RANGE;
	}
}

static void randomArr1(char *arr, int size)
{
	int i =0;
	srand (time(NULL));
	for ( i = 0 ; i<size ; i++)
	{
		arr[i] =(char) rand()%1000;
	}
}

int cmprAge (const void * data1, const void * data2)
{
	 return (((PERSON*)data1)->age - ((PERSON*)data2)->age);
}

int cmprName (const void * data_1, const void * data_2)
{
		return strcmp(((PERSON*)data_1)->name,((PERSON*)data_2)->name );
}

int cmprchar (const void * data_1, const void * data_2)
{
		return strcmp(((char*)data_1) , ((char*)data_2) );
}

int cmprInt (const void * data_1, const void * data_2)
{
		return ((*(int*)data_1) - (*(int*)data_2) );
}

size_t prsomToNum(const void *data, const void *param)
{
	return	(size_t)((PERSON*)data)->age;
}
