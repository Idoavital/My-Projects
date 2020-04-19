#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ucontext.h>
#include <pthread.h> /* thread*/


static int counter = 0;

static void * thread1 (void * argv)
{
	int i =0 ;
	for (i =0 ; i < 100 ; i++)
	{
		counter++;
	}
}

int main (int argc , char * argv[])
{
	pthread_t threa1 = PTHREAD_INITIALIZER;
	

}
