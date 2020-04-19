#include <stdio.h> /* printf */

#include "DList.h"
#include "DLIter.h"

void testDLcraete ();
void testPush ();
void testPop ();
void testIsempty();
void testSize();
static int PrintDLlist(DL_T* dl);

DL_T *dl;

static DL_ITER_T it10 ; /* will get the value after 10 push*/
static DL_ITER_T it20 ; /* will get the value after 20 push*/

int main (int argc, char *argv[])
{
	int x = 5;
	
	
	
	
	DL_ITER_T local = { 0, 0};
	DL_ITER_T srcBegin = {0, 0};
	DL_ITER_T srcEnd = {0, 0};
	DL_ITER_T dstIt = {0, 0};		
	
	DL_ITER_T srcBegin2 = {0, 0};
	DL_ITER_T srcEnd2 = {0, 0};

		
	DL_T* my_dbl_list = NULL;
	DL_T* splice_list = NULL;

	
	char data1[] = "This is data 1";
	char data2[] = "This is data 2";
	char data3[] = "This is data 3";
	char data4[] = "This is data 4";
	char data5[] = "This is data 5";
	char data6[] = "This is data 6";
	
	char* a = "a";
	char* b = "b";
	char* c = "c";
	char* d = "d";
	char* e = "e";
	testDLcraete ();
	it10 = DLBegin(dl);
	
	it10 = DLInsert( dl,it10, &x);
	DLErase(dl, it10);
	testIsempty();
	testSize();
	testPush ();
	
	testSize();
	testIsempty();
	testPop ();
	testSize();
	DLDestroy(dl);
	
	my_dbl_list = DLCreate();
	splice_list = DLCreate();

	PushBack(splice_list, a);
	PushBack(splice_list, b);
	PushBack(splice_list, c);
	PushBack(splice_list, d);
	PushBack(splice_list, e);
	
		
	/* H->T */	
	local = PushBack(my_dbl_list, data3);
	/* H->3->T */
	printf("Data %s\n",(char*)DLGetData(local));	
	printf("Expected Size |1| Counted |%lu|\n", DLSize(my_dbl_list));

	local = PushFront(my_dbl_list, data2);
	printf("Data %s\n",(char*)DLGetData(local));	
	/* H->2->3->T */
	printf("Expected Size |2| Counted |%lu|\n", DLSize(my_dbl_list));
	
	local = PushFront(my_dbl_list, data1);
	printf("Data %s\n",(char*)DLGetData(local));	
	/* H->1->2->3->T */

	local = PushBack(my_dbl_list, data4);
	printf("Data %s\n",(char*)DLGetData(local));
	printf("Expected Size |4| Counted |%lu|\n", DLSize(my_dbl_list));
	/* H->1->2->3->4->T */
		
	PopFront(my_dbl_list);
	/* H->2->3->4->T */
	
	PopBack(my_dbl_list);
	/* H->2->3->T */
	
	local = PushFront(my_dbl_list, data5);
	printf("Data %s\n",(char*)DLGetData(local));	
	/* H->5->2->3->T */

	local = PushBack(my_dbl_list, data6);
	printf("Data %s\n",(char*)DLGetData(local));	
	printf("Expected Size |4| Counted |%lu|\n", DLSize(my_dbl_list));
	/* H->5->2->3->6->T */

	local = PushBack(my_dbl_list, data3);
	local = PushBack(my_dbl_list, data6);
	local = PushBack(my_dbl_list, data1);
  	local = DLPrev(DLEnd(my_dbl_list));
	/* H->5->2->3->6->2->6->1->T */
  	DLErase(my_dbl_list,local);
	/* H->5->2->3->6->3->6->T */
	
	
	printf("************BEFORE SPLICE ****************\n");
	PrintDLlist(my_dbl_list);
	PrintDLlist(splice_list);
	

		
	dstIt = DLBegin(splice_list);
	dstIt = DLNext(dstIt); /* a, b  */
	
	
	srcBegin2 = DLBegin(my_dbl_list);
	srcEnd2 = DLPrev(DLEnd(my_dbl_list));
	
	DLSplice(dstIt, srcBegin2, srcEnd2);
	
/*	DLSplice(dstIt, srcBegin, srcEnd);*/ /* this one copies sub list to sub list */
	
	printf("************AFTER SPLICE ****************\n");
	PrintDLlist(my_dbl_list);
	PrintDLlist(splice_list);
	
	srcBegin = DLBegin(splice_list);	/*head - a */
	srcEnd = DLNext(DLNext(DLNext(DLNext(srcBegin)))); /*first  3 - 6 */
	dstIt = DLBegin(my_dbl_list); /*( head - tail */
	
	DLSplice(dstIt, srcBegin, srcEnd); /* a-5-2-3-6 *** 3-6-b-c-d-e */
	
	printf("************AFTER SPLICE ****************\n");
	PrintDLlist(my_dbl_list);
	PrintDLlist(splice_list);
	
	srcBegin = DLPrev(DLEnd(my_dbl_list));	/* 3-6 */
	srcEnd = DLPrev(DLEnd(my_dbl_list)); /* 3-6 */
	dstIt = DLPrev(DLEnd(splice_list)); /* e */
	
	DLSplice(dstIt, srcBegin, srcEnd);
	
	printf("************AFTER SPLICE ****************\n");
	PrintDLlist(my_dbl_list);
	PrintDLlist(splice_list);
	
 	DLDestroy(my_dbl_list);	
	DLDestroy(splice_list);
	
	
	
	
	my_dbl_list = NULL;
	splice_list = NULL;

	return 0;
}

static int PrintDLlist(DL_T* dl)
{
	DL_ITER_T endIt = DLEnd(dl);
	DL_ITER_T it = DLBegin(dl);
	
	printf("*********************************************\n");
	while(0 == DLIsEqual(it, endIt))
	{
		printf("Data %s\n",(char*)DLGetData(it));
		it = DLNext(it);
	}
	printf("*********************************************\n");
	
	return 0;
}



void testDLcraete ()
{
	dl = DLCreate();
	if (NULL == dl)
	{
		printf (" \nFAILD to craete\n");
		return ;
	}
	
	printf (" \nsuccess to craete\n" );
}
void testIsempty()
{
	if(1 == DLIsEmpty(dl))
		printf("\nlist is empty\n");
	else
		printf("\nlist is not empty \n");
}
void testPush ()
{
	DL_ITER_T it1 ;
	DL_ITER_T it2 ;
	int i = 0 ;
	char  c = 0 ;
	
	/* push i times member to the dlist */
	for ( ; i < 10 ; i++)
	{
		c = i ; /* change the value of size */
		it10 = PushBack(dl, &c);
		 	PushFront(dl, &c);
	}
	

	for (i=10 ; i < 20 ; i++)
	{
		c = i ; /* change the value of size */
		it20 = PushBack(dl, &c);
			PushFront(dl, &c);
	}
	
	for (i=20 ; i < 50 ; i++)
	{
		c = i ; /* change the value of size */
		it1 = PushBack(dl, &c);
		it2 = PushFront(dl, &c);
	}
	/* check if the first member is equal 49 */
	if (49 == *(char*) DLGetData(it1) )
	{	
		printf(" \nsuccess to push back \n");
	}
	else
	{
		printf(" \nfaild to push back \n");
	}
	
	/* check if the last member is equal 49 */
	if (49 == *(char*) DLGetData(it2) )
	{	
		printf(" \nsuccess to push front \n");
	}
		else
	{
		printf(" \nfaild to push back \n");
	}
	
	
	/* check size */
	if (100 == DLSize(dl))
	{
		printf(" \nsize after push is right \n");
	}
	else
	{
		printf(" \nsize after push is wrong \n");
	}
	
	
}
void testSize()
{
	printf ("size is %lu \n",DLSize(dl));
}

void testPop ()
{
	int i = 49 ;
	for (i=49 ; i >= 0 ; i--)
	{
		PopFront(dl);
		PopBack(dl);
	}

	if (0 == DLSize(dl))
	{
		printf(" \nsize after pop is right \n");
	}
	else
	{
		printf(" \nsize after pop is wrong \n");
	}
	testIsempty();	
}




