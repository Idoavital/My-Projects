#include <stdio.h>
#include <string.h>  /*strcmp */
#include <stdlib.h> /* malloc*/
#include <sys/stat.h> /*fstat */
#include <sys/types.h>  /*fstat */
#include <pthread.h> /*thread */

#include "MT_Sort.h"



pthread_t *thread_sort;

typedef struct
{
    char *base;
    int num;
    size_t size;
    size_t counter;
    CMP_T cmp;

}ArrData;

static void * Qsort (void * argv);

int MT_Sort(void* base, size_t num, size_t size, CMP_T cmp, size_t noOfThreads)
{

    int i=0;
    int j = 0;
    char * min_d =NULL;
    size_t div_num = 0;
    ArrData  *thread_data = NULL;
    char *temp_arr = NULL;
    int index = 0;

    temp_arr = malloc(num * size +1);

    if (NULL == temp_arr) /* check create*/
    {
        return -1;
    }


    thread_sort = malloc(sizeof(pthread_t) * noOfThreads);
    if (NULL == thread_sort) /* check create*/
    {
        return -1;
    }

    thread_data = malloc(sizeof(ArrData) * noOfThreads);
    if (NULL == thread_data) /* check create*/
    {
        return -1;
    }

    div_num = num / noOfThreads;
    /*build stract for */

    for (i =0 ; i< noOfThreads -1 ; i++ )
    {
        thread_data[i].base =(char*) base + (i* div_num * size);
        thread_data[i].cmp = cmp;
        thread_data[i].num = div_num;
        thread_data[i].size = size;
        thread_data[i].counter =0 ;
    }

    /* build the last*/
    if (noOfThreads > 1)
    {
        thread_data[i].base = (char*) base + (i* div_num * size);
        thread_data[i].cmp = cmp;
        thread_data[i].num = num - (div_num * (noOfThreads -1));
        thread_data[i].size = size;
        thread_data[i].counter = 0 ;
    }

        /*create thread for sorting n part of the array*/
    for (i =0 ; i< noOfThreads ; i++ )
    {
        if ( pthread_create(&thread_sort[i] , NULL , Qsort ,&thread_data[i] ))
        {
            return -1;
        }
    }

    /* wait for all thread to finish the sorting */
    for (i =0 ; i< noOfThreads ; i++ )
    {
          pthread_join(thread_sort[i],NULL);
    }

    /* merge sorted parts */
   for (i = 0 , index =0; i < num - 10; i++)
   {

       for (j = index; j < noOfThreads && thread_data[j].num == 0; j++);
       index = j;

       for(j = 0, min_d = thread_data[index].base; j < noOfThreads  ; j++)
       {
           if (thread_data[index].num > 0 && 0 < cmp( min_d, thread_data[j].base))
           {
               min_d =  thread_data[j].base;
               index = j;
           }
       }

       memcpy(((char*)temp_arr + size * i), min_d , size);

       thread_data[index].base = ((char *) thread_data[index].base + size);
       thread_data[index].num--;
   }


    memcpy(base , temp_arr , size * num);

    free(temp_arr);
    free(thread_sort);
    free(thread_data);

return 0;
}



static void * Qsort (void * argv)
{
    ArrData *temp_data = (ArrData*)argv;
    qsort(temp_data->base , temp_data->num ,temp_data->size,temp_data->cmp);

    return NULL;
}












