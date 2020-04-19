#include <stdlib.h>				/*	EXIT_SUCCESS	*/
#include <stdio.h>				/*	printf()		*/
#include <string.h>				/*	memcpy()		*/
#include <unistd.h>				/*	dup()			*/
#include <assert.h>
#include "sortL.h"				/*	circular buffer	*/


#define RESET   	"\033[0m"	/*	Reset colors 				*/
#define RED     	"\033[31"   /*	Red 						*/
#define GREEN   	"\033[32"   /*	Green 						*/
#define INT_SIZE	12			/*	int test size				*/
#define LOOPS_SIZE	7			/*loop tests size: 0..LOOPS_SIZE*/


#include "pQueue.h" 

typedef struct person
{	
	char name[10] ;
	int age;
}
PERSON;

PERSON rd38[] = {
{"ido",35},
{"moshe",28},
{"evgeni",34},
{"dani",2},
{"guy",26},
{"maayan",24},
{"beni",32},
{"eli",29},
	{"Violet", 3},
	{"John", 400},
	{"Alex", 1},
	{"Gary", 12},
	{"Samwise", 26},
	{"Harry", 27},
	{"Conway", 30},
	{"Vlad", 45},
	{"Jane", 77},		
	{"Golem", 555},		
};

PERSON rd38Sorted[] = {
{"dani",2},
{"guy",26},
{"moshe",28},
{"evgeni",34},
{"ido",35},
};

static void banner(char *name);
int match (const void *data1, const void *data2 ,  void *param);
void testCreate  ();
int CmpAge (const void *param1, const void *param2);
void printData (void *data);
static int pQEnqueueTest1();
void pQDequeueTest();
void testErase ();
static void vlgTest(int argc, char *argv[]);
static void printResult(char *test_name, int condition);

static PQUEUE *pq;

int main (int argc, char *argv[])
{
	printf ("\n ************ testCreate ********************* \n");

	testCreate  ();
	pQEnqueueTest1();
	printf ("\n ************ testerase ********************* \n");
	testErase ();
	printf ("\n queue after erase - ido should erased \n");
	printf ("\n ************ test pQDequeueTest********************* \n");
	pQDequeueTest();
	
	pQEnqueueTest1();
	pQDestroy(pq);
	vlgTest(argc, argv);
	
	
	return 0;
}

void testCreate  ()
{
	pq = pQCreate (CmpAge);
    if (pq != NULL)
    {
        printf("TestDLCreate suceedeed\n");
    }
    else
    {
        printf("TestDLCreate failed \n");
    } 
}


static int pQEnqueueTest1()
{

	printf ("\n ******************  test pQEnqueue *************** \n ");
	
	if (0 != pQEnqueue(pq , &rd38[0]))
		printf ("faild to Enqueue\n");
	if (0 != pQEnqueue(pq , &rd38[1]))
		printf ("faild to Enqueue\n");
	if (0 != pQEnqueue(pq , &rd38[2]))
		printf ("faild to Enqueue\n");
	if (0 != pQEnqueue(pq , &rd38[3]))
		printf ("faild to Enqueue\n");
	if (0 != pQEnqueue(pq , &rd38[4]))
		printf ("faild to Enqueue\n");	
		
	if (5 == pQSize(pq))
	{
		printf ("succes to Enqueue !\n");
	}
	printf ("size : %lu \n", pQSize(pq));
	return 1;
}

void testErase ()
{
	int age = 0;
	void *data ;
	int x = 35 ;
	data = pQErase (pq , match, (void*)&x , &age );
	printf (" data erase ");
	printData (data);
}
void pQDequeueTest()
{
	int i = 0;
	void *data;
	int size = pQSize(pq);
	for (; i< size ; i++)
	{
	data = pQDequeue (pq);
	printData (data);
	printf ("size : %lu \n", pQSize(pq));
	}
	
}
int CmpAge (const void *param1, const void *param2)
{
	PERSON *person1 = NULL;
	PERSON *person2 = NULL;

	assert(NULL != param1 && NULL != param2 );

	person1 = (PERSON *)param1;
	person2 = (PERSON *)param2;

	return ( person1->age > person2->age ? 1: 0);
}

void printData (void *data)
{
	printf (" name:  %s age:%d \n", ((PERSON*)data)->name,((PERSON*)data)->age );
	
}


int match (const void *data1, const void *data2 ,  void *param)
{
	if (((PERSON*)data1)->age == *((int*)data2))
			{
				return 1;
			}
	return 0;
}


#define MAX_LEN 40000

/*	valgrind test			*/
static void vlgTest(int argc, char *argv[])
{
	int out_pipe[2];
	int saved_stdout, saved_stderr;
	static char command[MAX_LEN] = {0};
	
	
	if (argc > 1)	return;
	
	banner("  Valgrind test  ");
		
	saved_stdout = dup(STDOUT_FILENO);  /* save stdout for display later */
	saved_stderr = dup(STDERR_FILENO);
	
	if( pipe(out_pipe) != 0 )           /* make a pipe */
	{
		exit(1);
	}
	
	dup2(out_pipe[1], STDOUT_FILENO);   /* redirect stdout to the pipe */
	dup2(out_pipe[1], STDERR_FILENO);   /* redirect stderr to the pipe */
	close(out_pipe[1]);
	
	/* anything sent to printf should now go down the pipe */
	sprintf(command, "valgrind -v --leak-check=yes --track-origins=yes %s stam", argv[0]);
	system(command);
	fflush(stdout);
	fflush(stderr);
	
	read(out_pipe[0], command, MAX_LEN); /* read from pipe into buffer */
	
	dup2(saved_stdout, STDOUT_FILENO);  /* reconnect stdout for testing */
	dup2(saved_stderr, STDERR_FILENO);  /* reconnect stdout for testing */
	
	printResult("Valgrind", NULL != strstr(command, "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"));
}

static void banner(char *name)
{
	printf("\n---------------------------------	\n|	%s	|	\n---------------------------------\n", name);
}

static void printResult(char *test_name, int condition)
{
	printf("%s test", test_name);
	
	if (condition)
	{
		printf ("%s;1m Succeeded %s\n", GREEN, RESET);
	}
	else
	{
		printf ("%s;1m Failed %s\n", RED, RESET);
	}
}





