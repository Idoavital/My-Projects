#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t pth;	// this is our thread identifier

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
	char *str;
	int i = 0;
    pthread_t thId = pthread_self();
    printf("theard id %d \nIS EQUAL - %d\n", (int)thId, pthread_equal(thId, pth));
	str=(char*)arg;

	while(i < 110 )
	{
		usleep(1);
		printf("threadFunc says: %s\n",str);
		++i;

		if (i==5)
            pthread_exit(NULL);
	}

	return NULL;
}

int main(void)
{

	int i = 0;
    pthread_t thId = pthread_self();
    printf("theard id - %d\n",(int)thId);

    printf("theard id - %d\n",(int)pth);
    pthread_create(&pth,NULL,threadFunc,"foo");
     printf("theard id - %d\n",(int)pth);

	while(i < 100)
	{
		usleep(1);
		printf("main is running...\n");
		++i;
	}

	printf("main waiting for thread to terminate...\n");
	pthread_join(pth,NULL);

	return 0;
}
