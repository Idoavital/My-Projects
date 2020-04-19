#include <stdlib.h> /* rand*/
#include <stdio.h> /*print*/
#include <unistd.h> /* usleep */
#include <pthread.h> /* thread*/
#include <semaphore.h>  /* semaphore */
#include <string.h> /*strcmp*/

/*************multi prod/cons****************************/
#include "DList.h"
#define SIZE 100
#define ARR_SIZE 50
static char str[20];
pthread_mutex_t broadC;
pthread_cond_t condc, condp;
static int i = 0;
sem_t sema_broad;
static int flag_cond = 1;

static int arr[SIZE];
static int KeepRunning = 1; /*stop runnig while value is 10 */

static int read_index = 0;
static int write_index = 0;

static pthread_mutex_t mutex_dlist = PTHREAD_MUTEX_INITIALIZER ;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER ;
/*
static pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER ;
static pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER ;
*/
static sem_t dlist_sem ;

static DL_T *dlist;

static sem_t read_sema;
static sem_t write_sema;


/* singel functions*/
static void *singelConsumer (void * arg);
static void *singelProdoc (void * arg);
void testBusyWait ();
 /*multi functions*/
static void *multipProd (void* argv);
static void *multipcons (void* argv);
static void testProdCond();
static void setArr();
/*multi function with semaphore*/
static void *multipProdWithSem (void* argv);
static void *multipconsWithSem (void* argv);
static void testProdCondWithSem();
/* circular buffer 1 mutex */
static int circularBufferOneMutex ();
static void* writeToBuffer(void *);
static void* readFromBuffer(void *);

/*   brodcast  */
static int broadCast ();
static void *broadCastProd(void * argv);
static void *broadCastCond(void * argv);



/*****************singel prod/cons**********************/
volatile int isDataReady = 0;
typedef struct
{
    int age  ;
    char name[10] ;
} PERSON;

PERSON person = {10 , "ido"};

/*****************singel prod/cons**********************/


int main (int argc ,char *argv[] )
{
    dlist = DLCreate();
    setArr();

    if (argc >= 1)
    {
        switch (argv[1][0])
        {
            case '1':
                testBusyWait (); /*singel prod/cons */
            break;

            case '2':
                testProdCond(); /*multi with mutex */
            break;

            case '3':
                testProdCondWithSem(); /*multi with semaphore */
            break;

            case '4':
                circularBufferOneMutex ();
            break;

            case '5':
                broadCast();
            break;
        }
    }

    return 0;
}

static void *singelProdoc (void * arg)
{

    while (person.age != 35)
    {
        /* wait until data has been processed */
        while (isDataReady)
        {
        }

        sleep(1);
        person.age ++;
        printf("\nprod run\n...\n...\n");
        isDataReady = 1;
    }
    return NULL;
}

static void *singelConsumer (void * arg)
{
    while (person.age != 35)
    {
        /* wait until data is ready */
        while (!isDataReady)
        {
        }
        printf("\n---- cnsuomer write ---\n person name %s \n person age %d\n", person.name , person.age);
        isDataReady = 0;
    }
    return NULL;
}

void testBusyWait ()
{
    pthread_t cons_thread;
    pthread_t prod_thread;


    pthread_create(&cons_thread , NULL , &singelConsumer , NULL);
    pthread_create(&prod_thread , NULL , &singelProdoc , NULL);

    pthread_join(cons_thread, NULL);
    pthread_join(prod_thread, NULL);
}
/*****************singel prod/cons **********************/


/*****************multi prod/cons **********************/


static void *multipProd (void* argv)
{
    int idx ;
    pthread_t  self;
    self = pthread_self();
    idx = rand() % (SIZE -1);
    printf("multipProd\n");

    while (1)
    {

        pthread_mutex_lock(&mutex_dlist);  /* lock the data and fush*/
        PushFront(dlist, &arr[idx]);
        pthread_mutex_unlock (&mutex_dlist);

        printf("\n----prod run.. %d\n",arr[idx]);  /*print for test*/
        printf("thread prod id %d\n",(int) self); /*print for test*/

        usleep(rand() % 7000000);

    }
return NULL;
}

/*consumer function */
static void *multipcons (void* argv)
{
    pthread_t   self;
    int *temp = NULL;
    self = pthread_self();

    printf("multipcons\n");

    while (1)
    {
        while (DLIsEmpty(dlist)) /*wait for data */
        {
        }
        pthread_mutex_lock(&mutex_dlist);
        if (!DLIsEmpty(dlist)) /*check again that nothing change between  */
        {
            temp = DLGetData(DLBegin(dlist));
            printf("\n\n----cons run.. %d\n",*temp);  /*for test */
            printf("thread cons id %d\n",(int) self); /*for test */
            PopBack(dlist);
        }
        pthread_mutex_unlock (&mutex_dlist);
    }
return NULL;
}

static void testProdCond()
{
    int check_create = 0;
    pthread_t thrd_cons[10];
    pthread_t thrd_prod[4];
    int i =0;

    for (i=0 ; i<10; i++)
    {
        check_create = pthread_create(&thrd_cons[i],NULL , &multipcons , NULL);
        /* check create success */
        if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return ;
        }

    }

    for (i=0 ; i<4; i++)
    {
        check_create = pthread_create(&thrd_prod[i],NULL , &multipProd , NULL);
        /* check create success */
         if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return ;
        }
    }

    /*wait for all thread finish*/
     for (i=0 ; i<10; i++)
     {
         pthread_join(thrd_cons[i] , NULL);
     }
    for (i=0 ; i<4; i++)
    {
         pthread_join(thrd_prod[i] , NULL);
    }

}

static void setArr()
{
    int i= 0;
    for (i=0; i<SIZE ; i++ , arr[i]=i);
}




/***************************3 - semaphopthread_t  self;
    self = pthread_self();re********************************************/
static void *multipProdWithSem (void* argv)
{
    int idx ;
    pthread_t  self;
    self = pthread_self();
    idx = rand() % (SIZE -1);
    printf("multipProd\n");

    while (KeepRunning)
    {

        pthread_mutex_lock(&mutex_dlist);  /* lock the data and fush*/
        PushFront(dlist, &arr[idx]);
        pthread_mutex_unlock (&mutex_dlist);
        sem_post (&dlist_sem);  /*send signal to the consumer to know him that data has been written */

        printf("\n----prod run.. %d\n",arr[idx]);  /*print for test*/
        printf("thread prod id %d\n",(int) self); /*print for test*/

        usleep(rand() % 7000000);

    }

return NULL;
}

static void *multipconsWithSem (void* argv)
{

    pthread_t   self;
    int *temp = NULL;
    self = pthread_self();

    printf("multipcons\n");

    while (KeepRunning || !DLIsEmpty(dlist))
    {

        sem_wait (&dlist_sem); /*wait until the the producers write data to dlist */
        pthread_mutex_lock(&mutex_dlist);
        if (!DLIsEmpty(dlist))
        {

            temp = DLGetData(DLBegin(dlist));
            printf("\n----cons run.. %d\n",*temp); /* print for the test */
            printf("thread cons id %d\n",(int) self); /* print for the test */
            PopBack(dlist);
        }
        pthread_mutex_unlock (&mutex_dlist);

    }


return NULL;
}

static void testProdCondWithSem()
{
    char exit[10]; /*for scan exit from user*/
    int check_create = 0;
    int i =0;
    pthread_t thrd_cons[4];
    pthread_t thrd_prod[10];

    sem_init(&dlist_sem , 0, 0);


    for (i=0 ; i<10; i++)
    {
        check_create = pthread_create(&thrd_prod[i],NULL , &multipProdWithSem , NULL);
         /* check create success */
         if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return ;
        }
    }

    for (i=0 ; i<4; i++)
    {
        check_create = pthread_create(&thrd_cons[i],NULL , &multipconsWithSem , NULL);
         /* check create success */
         if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return ;
        }
    }

        while(KeepRunning)
        {

             scanf(" %s",exit);

             if (0 == strcmp(exit,"q"))
             {
                 KeepRunning = 0;
             }
             printf(" exit ");
        }

     /*wait for all thread finish*/

    for (i=0 ; i<10; i++)
    {
         pthread_join(thrd_prod[i] , NULL);
    }

    for (i=0 ; i<4; i++)
    {
       sem_post (&dlist_sem);
    }

    for (i=0 ; i<4; i++)
    {

        pthread_join(thrd_cons[i] , NULL);
    }
    printf("\nGOOD BUY\n");

}

/***************************4 - circular buffer ********************************************/
static int circularBufferOneMutex ()
{
    char exit[10]; /*for scan exit from user*/
    int check_create = 0;
    int i =0;
    pthread_t thrd_cons[4];
    pthread_t thrd_prod[10];

    if (sem_init(&read_sema, 0, 0))
        return -1;

    if (sem_init(&write_sema, 0, ARR_SIZE-1))
        return -1;


    for (i=0 ; i<10; i++)
    {
        check_create = pthread_create(&thrd_prod[i],NULL , &writeToBuffer , NULL);
         /* check create success */
         if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return -1;
        }
    }

    for (i=0 ; i<4; i++)
    {
        check_create = pthread_create(&thrd_cons[i],NULL , &readFromBuffer , NULL);
         /* check create success */
         if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return -1;
        }
    }

        while(KeepRunning)
        {

             scanf(" %s",exit);

             if (0 == strcmp(exit,"q"))
             {
                 KeepRunning = 0;
             }
             printf(" exit ");
        }

     /*wait for all thread finish*/
      for (i=0 ; i<10; i++)
    {
       sem_post (&write_sema);
    }

    for (i=0 ; i<10; i++)
    {
         pthread_join(thrd_prod[i] , NULL);
    }

    for (i=0 ; i<ARR_SIZE; i++)
    {
       sem_post (&read_sema);
    }

    for (i=0 ; i<4; i++)
    {

        pthread_join(thrd_cons[i] , NULL);
    }
    printf("\nGOOD BUY\n");

    return 0;

}

static void* writeToBuffer(void * argv)
{
    int data = 0;
    data = rand() % (SIZE );

    while (KeepRunning )
    {
        data = rand() % (SIZE );
        sem_wait(&write_sema);


        pthread_mutex_lock(&lock);
            write_index = (write_index < ARR_SIZE -1)  ? write_index+1 : 0 ;
            arr[write_index] = data;
            printf("\nwrite in index %d, data %d" ,write_index, data);
        pthread_mutex_unlock(&lock);

        sem_post(&read_sema);
        usleep(1000000);
    }

    return NULL;

}
static void* readFromBuffer(void * argv)
{
    while (KeepRunning|| write_index != read_index)
    {
        sem_wait(&read_sema);

        pthread_mutex_lock(&lock);
            read_index = ( read_index < ARR_SIZE -1  ? read_index+1 : 0 );
            printf("\nread in index %d, data %d" ,read_index, arr[read_index]);
        pthread_mutex_unlock(&lock);

        sem_post(&write_sema);
        usleep(1000000);
    }

    return NULL;
}

/**************************** broad cast *******************************************/
static int broadCast ()
{
    char exit[10]; /*for scan exit from user*/
    int check_create = 0;
    int i =0;
    pthread_t thrd_cons[4];
    pthread_t thrd_prod[1];
    pthread_cond_init(&condc, 0);
    flag_cond = 1;

    sem_init(&sema_broad,0,0);


    for (i=0 ; i<1; i++)
    {
        check_create = pthread_create(&thrd_prod[i] ,NULL , &broadCastProd ,NULL);
         /* check create success */
         if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return -1;
        }
    }

    for (i=0 ; i<4; i++)
    {
        check_create = pthread_create(&thrd_cons[i],NULL , &broadCastCond , NULL);
         /* check create success */
         if (0 != check_create)
        {
            printf(" failed to crate thread ");
            return -1;
        }
    }

        while(KeepRunning)
        {
             scanf(" %s",exit);
             if (0 == strcmp(exit,"q"))
             {
                 KeepRunning = 0;
             }
             printf(" exit ");
        }

     /*wait for all thread finish*/
    for (i=0 ; i<1; i++)
    {
         pthread_join(thrd_prod[i] , NULL);
    }

    for (i=0 ; i<4; i++)
    {
       sem_post (&sema_broad);
    }

    for (i=0 ; i<4; i++)
    {

        pthread_join(thrd_cons[i] , NULL);
    }
    printf("\nGOOD BUY\n");

    return 0;

}

static void *broadCastCond(void * sema)
{
    pthread_t self;
    self = pthread_self();
    while(KeepRunning)
    {
        sem_post(&sema_broad);
        pthread_mutex_lock(&broadC);
        pthread_cond_wait(&condc, &broadC );
          printf("thread id - %d print sms %s\n ",(int)self,str);
        pthread_mutex_unlock(&broadC);
    }

return NULL;
}

static void *broadCastProd(void * sema)
{
    int j = 0;


    while(KeepRunning)
    {
          for (j =0 ; j < 4 ; j++)
            sem_wait(&sema_broad);

        pthread_mutex_lock(&broadC);

          sprintf (str,"message number %d\n",i++);

        pthread_mutex_unlock(&broadC);
        pthread_cond_broadcast(&condc); /* send broad cast */

        /* wait for all consumer have finished reading */

        sleep(1);
        printf ("finsh to wait\n");

    }
    pthread_cond_broadcast(&condc); /* send broad cast */

    return NULL;
}
