
#include <stdio.h>
#include <stdlib.h>

#include "SList.h"
#include "recursion.h"
#include "stack.h"

#define SIZE 20

void testflip ();

static void sortStackTest(void);

int main(int argc, char *argv[])
{

    int x = 0;
    size_t ret = 0;
    char arr[20] = "babalala";
    char arr2[20] = "00000";

    x = fibonacci (40);
    printf("%d\n",x);

    x =  fibonacciNoRec(40);
    printf("%d\n",x);

    ret = Strlen ("123456789");
    printf("strlen : %lu\n",ret);

    x = Strcmp ("12346" ,"1234");
    printf("strcmp : %d\n",x);

    Strcpy(arr2 , arr);
    printf("strcpy : %s\n",arr2);

     testflip ();
    sortStackTest();
    return 0;
}
void testflip ()
{
	int i =0 ;
	int j =SIZE-1 ;
	Node_t *node[SIZE];
	Node_t *node_temp;
	int test[SIZE];

	/* craete */
	for (i=0 ; i <SIZE ; i++)
	{
		test[i]=i;
		node[i] = SListCreate(&test[i]);
		printf("%d ", i);
	}


	for (i=1 ; i <SIZE ; i++)
	{

		SListInsertAfter (node[i],node[i-1]);

	}

	node_temp =flipRecursion(node[0]);

		printf (" after flip \n" );
	for (i=0 ; i <SIZE ;j--, i++)
	{
        printf("%d ",*(int*)(node_temp->data));
        node_temp=node_temp->next;
	}

	/*check if the data flip*/
	for (i=0 ; i <SIZE ;j--, i++)
	{
		if (*(int*)node[i]->data == j)
			{
				printf("faild \n ");
				printf ("!!!  faild to flip !!!\n");
				return;
			}

	}

	printf ("!!!  success to flip !!!\n" );

	for (i=0 ; i <SIZE ; i++)
	{
		free(node[i]);
	}
}
static void sortStackTest(void)
{
    STACK* s = NULL;
    int i = 0;
    int arr[10] = {3,5,2,-1,7,8,4,10,519,-20};
    s = CreateStack(10 , sizeof(int));

    printf("befor sort :\n");
    for(i = 0; i < 10; printf("%d, " ,arr[i]) , Push(s , &arr[i]) , i++);
    printf("\n");
    sortStack(s);
    printf("after sort :\n");
    for(i = 0 ; i < 10; i ++)
    {
        printf("%d, ",*(int*)Peek(s));
        Pop(s);
    }
    printf("\n");


}
