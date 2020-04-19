
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "AVL.h"

#define SIZE 10
#define RANGE 100


static void TestAVLCreate(void);

static int comp (const void *data1, const void *data2);

static void randomArr(int *arr, int size);

static void AVLInsertTest(void);

static void AVLremoveTEST (void);

static int action(void *data, void *param);

 int test[20] = {50,40,30 , 60, 70, 45 , 10, 42, 46, 47  } ;

int arr[SIZE];


AVL_T *avl = NULL;

int main (int argc, char *argv[])
{
	TestAVLCreate();

	AVLInsertTest();

	print_n(avl);

    printf("\n");

    printf( "size of tree = %lu \n", AVLSize(avl) );

    AVLremoveTEST ();

    print_n(avl);

    printf("\n");

    printf( "size of tree = %lu \n", AVLSize(avl) );

    AVLDestroy( avl );


	return 0;
}



static void TestAVLCreate(void)
{

	avl = AVLCreate(comp);

	if (avl != NULL)
   	{
   		printf("TestBSTCreate suceedeed\n");

   	}
	else
	{

		printf("TestBSTCreate failed \n");
	}

}


static void AVLInsertTest(void)
{
	int i =0;

	int size = SIZE;
	randomArr(arr, size);

	/* LL */
    AVLInsert(avl , &test[0]);
    AVLInsert(avl , &test[1]);
    AVLInsert(avl , &test[2]);

     print_n(avl);
        printf("\n");
        printf( "size of tree = %lu \n", AVLSize(avl) );
      /* RR */
    AVLInsert(avl , &test[3]);
    AVLInsert(avl , &test[4]);
     print_n(avl);
        printf("\n");
        printf( "size of tree = %lu \n", AVLSize(avl) );
    /*  RL root */
    AVLInsert(avl , &test[5]);

      print_n(avl);
        printf("\n");
        printf( "size of tree = %lu \n", AVLSize(avl) );

    /*  LR root */
    AVLInsert(avl , &test[6]);
    AVLInsert(avl , &test[7]);
    AVLInsert(avl , &test[8]);
    AVLInsert(avl , &test[9]);

     print_n(avl);
        printf("\n");
        printf( "size of tree = %lu \n", AVLSize(avl) );

    AVLForEach(avl,action , NULL);

	for (i = 0 ;i< SIZE ; i++)
	{
		 AVLInsert(avl , &arr[i]);
	}



}

static void AVLremoveTEST (void)
{

        AVLRemove(avl,  &test[9] );
        AVLRemove(avl,  &test[8] );
        printf( " rempve %d  %d \n" ,test[9], test[8] );

        print_n(avl);
        printf("\n");
        printf( "size of tree = %lu \n", AVLSize(avl) );

        AVLRemove(avl,  &test[0] );
        AVLRemove(avl,  &test[4] );
         printf( " rempve %d  %d \n" ,test[0], test[4] );

        print_n(avl);
        printf("\n");
        printf( "size of tree = %lu ", AVLSize(avl) );

        AVLRemove(avl,  &test[3] );
        AVLRemove(avl,  &test[7] );

        printf( " rempve %d  %d \n" ,test[3], test[7] );
        print_n(avl);
        printf("\n");
        printf( "size of tree = %lu \n", AVLSize(avl) );

        AVLRemove(avl,  &test[5] );
        printf( " rempve %d  \n" ,test[5]);
        AVLRemove(avl,  &test[1] );
        AVLRemove(avl,  &test[2] );
        AVLRemove(avl,  &test[3] );
        AVLRemove(avl,  &test[6] );
}
static int comp (const void *data1, const void *data2)
{
 	return *(int*)data1 - *(int*)data2;
}
static void randomArr(int *arr, int size)
{
	int i =0;
	srand (time(NULL));
	for ( i = 0 ; i<size ; i++)
	{
		arr[i] =  rand()%100 ;
	}
}

static int action(void *data, void *param)
{
	printf("the num AVLForEach: %d \n", (*(int*)data));

	return 0;
}


