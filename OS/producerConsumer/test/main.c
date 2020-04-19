#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ucontext.h>
#include <pthread.h> /* thread*/
#include <sched.h>

int counter = 0;
static int first = 0;
static void * thread1 (void * argv)
{

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    sched_setaffinity(0 , sizeof(cpu_set_t),&mask);

	int i =0 ;
	int temp = 0;
	int my_id = first;
	if (first == 0)
    {
        first++;
    }
    printf ("first %d\n",my_id);


	for (i =0 ; i < 100 ; i++)
	{

        temp = counter ;

        if ( my_id == 0 &&  counter  == 0)  /*1*/
        {
            sched_yield();
            printf("temp 0 - 1 %d  counter %d\n",temp, counter);
        }

	    if ( my_id == 1 && i == 99)  /*4*/
        {
            printf("temp 1  - 4 %d\n",temp);
            sched_yield();
        }

        printf ("mi id %d counter %d\n",my_id, counter);

        counter = ++temp;

        if ( my_id == 1 && i == 98)   /*2*/
        {
            printf("temp 1 - 2 %d  counter %d \n",temp, counter);
            sched_yield();
        }
        if ( my_id == 0 &&  counter == 1)   /*3*/
        {
            sched_yield();
            printf("temp 0 - 3 %d  counter %d\n",temp, counter);
        }




    }
return NULL;
}


int main (int argc , char * argv[])
{


    int a = 1;
    int b = 0 ;


	pthread_t thread_first ;
    pthread_t thread_second ;

	pthread_create (&thread_first , NULL ,&thread1, &a );
	pthread_create (&thread_second , NULL ,&thread1, &b );



	pthread_join(thread_first, NULL);
    pthread_join(thread_second, NULL);

    printf("\n -- %d  --\n",counter );

return 0;
}
