#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include <string.h> /* strcmp */
#include "SList.h"

#define AST_LINE "\n*****************************************\n"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

void testInsert ();
void TestRemove (Node_t *head , Node_t *remove ,Node_t *last );
void testflip ();
void testisloop ();
void testIntersection ();
void testforEach ();


static int Myfunc(char* data, char* param);
static int MyFind(char* data, char* param);

int main (int argc, char *argv[])
{

/*
	int x1 =1;
	int x2 =2;
	int x3 =3;
	int x4 =4;

	Node_t *n1 = SListCreate (&x1);
	Node_t *n2 = SListCreate (&x2);
	Node_t *n3 = SListCreate (&x3);
	Node_t *n4 = SListCreate (&x4);
	
	SListInsertAfter (n2,n1);
	SListInsertAfter (n3, n2);
	SListInsertAfter (n4,n3);
	printf(GRN "--------------before flip---------- \n");
	printf("n1 addres %p, n1 next addres= %p \n",(void*)n1,(void*) n1->next);
	printf("n2 addres %p, n2 next addres= %p \n",(void*)n2,(void*) n2->next);
	printf("n3 addres %p, n3 next addres= %p \n",(void*)n3,(void*) n3->next);
	printf("n4 addres %p, n4 next addres= %p \n",(void*)n4,(void*) n4->next);
	
	
	SListFlip(n1);
	
	printf("--------------after flip---------- \n");
	printf("n1 addres %p, n1 next addres= %p \n",(void*)n1,(void*) n1->next);
	printf("n2 addres %p, n2 next addres= %p \n",(void*)n2,(void*) n2->next);
	printf("n3 addres %p, n3 next addres= %p \n",(void*)n3,(void*) n3->next);
	printf("n4 addres %p, n4 next addres= %p \n"RESET,(void*)n4,(void*) n4->next);

	*/
	

	
	/* test crate ande insert */
	testInsert();
	testflip ();
	testisloop ();
	testIntersection ();
	testforEach ();
	

	return 0;
}


void testInsert ()
{
	int i =0 ;
	Node_t *node[200];
	char test[200];
	
	/* craete */
	for (i=0 ; i <200 ; i++)
	{
		test[i]=i;
		node[i] = SListCreate(&test[i]);
		if (node[i]==NULL )
		{
			printf("#### faild to crate , node = null #####");
		}
		
		/* check if data insert */
		if (*(char*)node[i]->data != (char)i )
		{
			printf("i = %d  node = %d  ",i,*(char*)node[i]->data );
			printf("#### faild to insert data \n ####");
		}
	}
	

	printf (GRN AST_LINE"!!!  success to craete !!!\n" AST_LINE RESET);
	
	for (i=1 ; i <200 ; i++)
	{
		
		SListInsertAfter (node[i],node[i-1]);
		
	}
	i =0;
	
	/* check if succes to  */
	for (i=0 ; i <199 ; i++)	
	{
	
		if ((void*)(node[i+1]) != ((char*) node[i]->next))
		{
		
		printf("node %d addres %p, next addres= %p \n",i,(void*)(node[i]),(void*) node[i]->next);
		printf ("#### faild to insert ###");
		break;
		
		}
	}
	
	printf (GRN AST_LINE"!!!  success to INSERT !!!\n" AST_LINE RESET);

	for (i=0 ; i <200 ; i++)
	{
		free(node[i]);
	}
	
}

void TestRemove (Node_t *head , Node_t *remove ,Node_t *last )
{
/* get 3 node and check the if */
	SListRemove(remove);
	if (head->next == last)
		printf("woowww");
}

void testflip ()
{
	int i =0 ;
	int j =199 ;
	Node_t *node[200];
	char test[200];
	
	/* craete */
	for (i=0 ; i <200 ; i++)
	{
		test[i]=i;
		node[i] = SListCreate(&test[i]);
	}
	
	
	for (i=1 ; i <200 ; i++)
	{
		
		SListInsertAfter (node[i],node[i-1]);
		
	}
	
	SListFlip(node[0]);
	
	/*check if the data flip*/
	for (i=0 ; i <200 ;j--, i++)
	{
		if (*(int*)node[i]->data == j)
			{
				printf("faild \n ");
				printf (RED AST_LINE"!!!  faild to flip !!!\n" AST_LINE RESET);
				return;
			}
	
	}
	
	printf (GRN AST_LINE"!!!  success to flip !!!\n" AST_LINE RESET);
	
	for (i=0 ; i <200 ; i++)
	{
		free(node[i]);
	}
}
	
void testisloop ()
{
	int i =0 ;
	Node_t *node[200];
	char test[200];
	
	/* craete */
	for (i=0 ; i <200 ; i++)
	{
		test[i]=i;
		node[i] = SListCreate(&test[i]);
	}
	
	
	for (i=1 ; i <200 ; i++)
	{
		
		SListInsertAfter (node[i],node[i-1]);
		
	}
		/*make a loop */
	node[199]->next = node[80] ;
	if (1 == SListHasLoop(node[0]))
		printf (GRN AST_LINE"!!!  success test loop !!!\n" AST_LINE RESET);
	else
		printf (RED AST_LINE"!!!  faild test loop !!!\n" AST_LINE RESET);
	for (i=0 ; i <200 ; i++)
	{
		free(node[i]);
	}	
		
}
	
void testIntersection ()
{
	int i =0 ;
	Node_t *node[200];
	Node_t *node2[100];
	char test[200];
	
	/* craete */
	for (i=0 ; i <200 ; i++)
	{
		test[i]=i;
		node[i] = SListCreate(&test[i]);
	}
		
	for (i=1 ; i <200 ; i++)
	{	
		SListInsertAfter (node[i],node[i-1]);	
	}


	for (i=0 ; i <100 ; i++)
	{
		test[i]=i;
		node2[i] = SListCreate(&test[i]);
	}
		
	for (i=1 ; i <100 ; i++)
	{	
		SListInsertAfter (node2[i],node2[i-1]);
	}

	/* test list find : check if my find test[20] return node  [20] */
	if (node[20] == SListFind(node[0], (Match_t) MyFind , &test[20]))
		printf (GRN AST_LINE"!!!  success test Find !!!\n" AST_LINE RESET);
	else
		printf (RED AST_LINE"!!!  fails Find !!!\n" AST_LINE RESET);
			
		/* free node and nod 2*/

		/*create intersection	*/
	SListInsertAfter (node[150],node2[99]);
	
	
	/* check find intersection */
	if(SListFindIntersection(node[0], node2[0]) == node[150])
		printf (GRN AST_LINE"!!!  success Find Intersection !!!\n" AST_LINE RESET);
	else
		printf (RED AST_LINE"!!!  fails FindIn tersection !!!\n" AST_LINE RESET);
			
			
		/* free node and nod 2*/
	for (i=0 ; i <200 ; i++)
	{
		free(node[i]);
		
	}		

	for (i=0 ; i <100 ; i++)
	{
		free(node2[i]);
		
	}		
}


void testforEach ()
{
	int i =0 ;
	Node_t *node[200];
	char test[200];
	
	/* craete */
	for (i=0 ; i <200 ; i++)
	{
		test[i]=i;
		node[i] = SListCreate(&test[i]);
	}
		
	for (i=1 ; i <200 ; i++)
	{	
		SListInsertAfter (node[i],node[i-1]);	
	}
	
	
	if( 0 == SListForEach(node[0], (Action_t) Myfunc , &test[97]))
		printf (GRN AST_LINE"!!!  success for each !!!\n" AST_LINE RESET);
	else
		printf (RED AST_LINE"!!!  fails for each  !!!\n" AST_LINE RESET);
			
	
		/* free node and nod 2*/
	for (i=0 ; i <200 ; i++)
	{
		free(node[i]);
		
	}		

}
static int MyFind(char* data, char* param)
{
	if(0 == strcmp(data, param))
	{
		return 0;
	}
	
	return -1;	
}



static int Myfunc(char* data, char* param)
{
	
	memcpy(data, param,1);
				
	return 0;	
}
















