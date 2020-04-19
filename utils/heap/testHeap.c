
#include <stdio.h>
#include <string.h>

#include "heap.h"

HEAP_T *heap;

typedef struct person
{
	char name[10] ;
	int age;
}
PERSON;

PERSON rd38[] = {
{"ido-1",35},
{"evgeni",34},
{"dani-1",2},
{"maayan",24},
{"guy-2",2},
{"beni",32},
{"eli",29},
{"moshe-2",36},
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

/*static int arr[10] = {2, 5, 4, 3, 9, 0, 0, 1, 4, 3};*/

int cmprAge (const void * data1, const void * data2);

int cmprName (const void * data_1, const void * data_2);

int match (const void *data1, const void *data2 , void *param);

static void testCreate ();

static void testHeapPush ();

static void testHeapRemove ();

void PrintHeapTest(void* data);


/************************************************/
int main(int argc, char *argv[])
{
    testCreate ();
    testHeapPush ();
    testHeapRemove ();
    HeapDestroy(heap);


    return 0;
}

static void testCreate ()
{
    heap = HeapCreate(cmprAge);
    if (heap== NULL)
    {
        printf( "faild to create()\n");
    }
      printf( "success to create()\n");


}

static void testHeapPush ()
{


    HeapPush(heap , &rd38[0]);
    HeapPush(heap , &rd38[1]);
    HeapPush(heap , &rd38[2]);
    HeapPush(heap , &rd38[3]);
    HeapPush(heap , &rd38[4]);
    HeapPush(heap , &rd38[5]);
    HeapPush(heap , &rd38[6]);
    HeapPush(heap , &rd38[7]);
    HeapPush(heap , &rd38[8]);
    printf ( "---- insert 9 preson element ----\n " );
#ifndef NDEBUG
    HeapPrint(heap, PrintHeapTest);
#endif
/************** test size  ***********/
    if (9 == HeapSize (heap))
    {
         printf( "\n size test is right ()\n");
    }
    else
       printf( "\n faild to get size()\n");



}

static void testHeapRemove ()
{

    printf ( "\n---- remove age - %d preson element ----\n ", rd38[5].age );
    HeapRemove(heap, match, &rd38[5], NULL);
    #ifndef NDEBUG
    HeapPrint(heap, PrintHeapTest);
    #endif

    printf ( "\n---- remove root : age - %d preson element ----\n ", rd38[7].age );
    HeapRemove(heap, match, &rd38[7], NULL);
    #ifndef NDEBUG
    HeapPrint(heap, PrintHeapTest);
    #endif

    printf ( "\n---- remove last : age - %d preson element ----\n ", rd38[8].age );
    HeapRemove(heap, match, &rd38[8], NULL);

    #ifndef NDEBUG
    HeapPrint(heap, PrintHeapTest);
    #endif
    /************ test size  ***********/
    if (6 == HeapSize (heap))
    {
         printf( "\n size test is right ()\n");
    }
    else
       printf( "\n faild to get size()\n");

    printf ( "\n---- try to remove element that not in the array  : age - %d preson element ----\n ", rd38[8].age );
    HeapRemove(heap, match, &rd38[8], NULL);

    /************ test size  ***********/
    if (6 == HeapSize (heap))
    {
         printf( "\n size test is right ()\n");
    }
    else
       printf( "\n faild to get size()\n");
}

/*****************cmp function *************************/

int cmprAge (const void * data1, const void * data2)
{
	 return (((PERSON*)data1)->age - ((PERSON*)data2)->age);
}

int cmprName (const void * data_1, const void * data_2)
{
		return strcmp(((PERSON*)data_1)->name,((PERSON*)data_2)->name );
}

void PrintHeapTest(void* data)

{
    printf("name - %s age - %d \n",((PERSON*)data)->name,((PERSON*)data)->age);
}

int match (const void *data1, const void *data2 , void *param)
{
    if (((PERSON*)data1)->age == ((PERSON*)data2)->age)
    {
        return 1;
    }

    return 0;
}








