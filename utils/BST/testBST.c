
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "BST.h" 

#define SIZE 200
#define RANGE 10000


static void TestBSTCreate(void);

static int comp (const void *data1, const void *data2, void *param);

static int act (void *data, void *param);

static void IsEmptyTest(void);

static void randomArr(int *arr, int size);

static void BSTInsertTest(void);

static void  BSTForEachTest();

static void BSTFindTest();

static void removeTest ();

int arr[SIZE];

BST_ITER it =NULL;

BST_T *bst = NULL;

int main (int argc, char *argv[])
{
	TestBSTCreate();
	IsEmptyTest();
	BSTInsertTest();
	BSTForEachTest();
	BSTFindTest();
	BSTForEachTest();
	removeTest ();
	
	printf("\n");
	
	BSTDestroy(bst);
	
	return 0;
}


static void TestBSTCreate(void)
{

	bst = BSTCreate(comp, NULL);

	if (bst != NULL)
   	{
   		printf("TestBSTCreate suceedeed\n");

   	}
	else
	{

		printf("TestBSTCreate failed \n");
	}

}


static void IsEmptyTest(void)
{
	if (IsEmpty(bst))
	{
		printf("IsEmpty() succeeded\n");
	}
	else
	{
		printf("IsEmpty() failed\n");
	}
}
static void BSTInsertTest(void)
{
	int i =0;
	int size = SIZE;
	randomArr(arr, size);
	for (i = 0 ;i< size ; i++)
	{
		 BSTInsert(bst , &arr[i]);
	}
	
	it = BSTInsert(bst , &arr[i]);
	for (i = 11 ;i< size ; i++)
	{
		 BSTInsert(bst , &arr[i]);
	}
	
}
static int comp (const void *data1, const void *data2, void *param)
{
 	return *(int*)data1 - *(int*)data2;
}

static int act (void *data, void *param)
{
	printf ("%d ", *(int*)data);
	return 0;
}

static void randomArr(int *arr, int size)
{
	int i =0;
	srand (time(NULL));
	for ( i = 0 ; i<size ; i++)
	{
		arr[i] = rand()%100;
	}
}

static void  BSTForEachTest()
{

	BST_ITER from =  BSTBegin(bst);
	BST_ITER to = BSTEnd(bst);
	
	 BSTForEach( from,  to, act , NULL); 
	
}

static void BSTFindTest()
{
	int x = rand()%100;
	int y = rand()%100;
	BST_ITER temp ;
	
	temp = BSTFind(bst, &x);	
	if(temp!= NULL)
	{
		if (x == *(int*)(BSTGetData(temp)))
		{
			printf("\n success to find %d", *(int*)(BSTGetData(temp)) );
		}
		else
			printf ("\n num %d not find ", x);
	
		
	}
	else
		printf ("\n num %d not find ", x);
		
	temp = BSTFind(bst, &y);	
	if(temp!= NULL)
	{
		if (y == *(int*)(BSTGetData(temp)))
		{
			printf("\n success to find %d", *(int*)(BSTGetData(temp)) );
		}
		else
			printf ("\n num %d not find ", y);
		
	}
	else
		printf ("\n num %d not find ", y);
		
}

static void removeTest ()
{
	printf ("\nremove iter %d \n", *(int*)(BSTGetData(it)) );
	BSTRemove(it);
	printf(" after remove \n");
	BSTForEachTest();
}


