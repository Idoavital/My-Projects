#include <string.h> /* strcmpr*/
#include <stdio.h>	/* printf */

#include "queue.h"
#define AST_LINE "\n*****************************************\n"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

QUEUE *queue;


void testCreate();
void testqEnqueue ();
void testPeek ();
void testqIsEmpty();

int main (int argc, char *argv[])
{
	
	testCreate ();
	testqIsEmpty();
	testqEnqueue ();
	qDestroy(queue);
	
	
	return 0;
}

void testCreate()
{

	queue = qCreate();
	if (NULL == queue)
	{
		printf(RED AST_LINE"faild to create\n" AST_LINE RESET);
	}
	else
	{
		printf(GRN AST_LINE"\tsuccess create\n" AST_LINE RESET);
	}
}

void testqEnqueue ()
{
	int i = 0;
	for (i = 0 ; i<100; i++)
	{
		qEnqueue (queue, &i);
	}
	if (qIsEmpty(queue)==0)
		printf(GRN AST_LINE"\tsuccess qEnqueue\n" AST_LINE RESET);
	else
		printf(RED AST_LINE"\tfaild qEnqueue\n" AST_LINE RESET);
	
	
	for (i = 0 ; i<100; i++)
	{
		if ( strcmp ((char*) qDequeue (queue),(char*)&i))
		{
			printf(RED AST_LINE"faild to qDequeue\n" AST_LINE RESET);
		}
	}	
			
	printf(GRN AST_LINE"\tsuccess qDequeue\n" AST_LINE RESET);
	
}


void testqIsEmpty()
{
	
	if ( 1 == qIsEmpty(queue) )
		{
			printf(GRN AST_LINE"\t is empty \n" AST_LINE RESET);
		}
			
}















