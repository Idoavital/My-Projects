#include <stdio.h>    /* file*/
#include <stdlib.h>    /* malloc*/
#include <sys/stat.h>     /*fstat */
#include <sys/types.h>     /*fstat */
#include <fcntl.h>
#include <string.h>   /*strtok*/
#include <time.h>    /* time */


#include "MT_Sort.h"

#define  MULTI_DICTIONARY 5
FILE *file;

struct timespec ts_start; /*  for measure thread time */
struct timespec ts_end;  /* for measure thread time */

static struct stat buf;
static char *dictionary;
static char **word;
static size_t size_word;

static void swap (char * first[] , char * second[] );

static void createDictionary ();

int cmprchar (const void * data_1, const void * data_2);


int main(int argc, char *argv[])
{
    double time_s = 0;
    int i = 0;
    createDictionary();

    /* first check time of sort with one tread  */
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
    qsort(word ,size_word, sizeof(size_t), cmprchar);

    clock_gettime(CLOCK_MONOTONIC, &ts_end);

    time_s = ts_end.tv_sec - ts_start.tv_sec;
    time_s +=(double) (ts_end.tv_nsec - ts_start.tv_nsec)/1000000;

    printf ("time_s  of one thread sort %0.3f \n", (double)(time_s) );


    for (i =0 ; i < size_word ; i++)
    {
        printf( "%s ", word[i]);
    }

    /* shuffle the array */
    for (i = 0;i<size_word ;i++)
    {
        swap (&word[rand()%size_word] , &word[rand()%size_word]);
    }

     /* check time of sort with 4 thread */
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
    MT_Sort(word, size_word  , sizeof(size_t) , cmprchar, 4);
    clock_gettime(CLOCK_MONOTONIC, &ts_end);

    time_s = ts_end.tv_sec - ts_start.tv_sec;
    time_s +=(double) (ts_end.tv_nsec - ts_start.tv_nsec)/1000000;

    printf ("time_s  of multi thread sort %0.3f \n", (double)(time_s) );


    /*free the memory  */
    free (word);
    free (dictionary);

    return 0;
}



static void createDictionary ()
{
    int i = 0;
    int lines = 0;
    char ch ;
    char *token = NULL;

        /*open the dictionary file*/
    file = fopen("/usr/share/dict/american-english", "r");

    fstat(fileno(file), &buf);

    dictionary = (char*)malloc(MULTI_DICTIONARY * (buf.st_size )+1);
    dictionary[MULTI_DICTIONARY * buf.st_size] = '\0';

    /*copy the words*/
    fread(dictionary, sizeof(char), buf.st_size, file);

    fseek(file, 0, SEEK_SET);
    /*get the number of lines (words)*/

    while ((ch = fgetc(file)) != EOF)
    {
      if (ch == '\n')
      lines++;
    }


    for (i = 0 ; i < MULTI_DICTIONARY  ; i ++)
      memmove( dictionary  + (i * buf.st_size ), dictionary , buf.st_size );

    word = (char**)malloc(MULTI_DICTIONARY *(lines) * sizeof(size_t) );

    fclose(file);

    /* get the first token */
     i= 0;
     token =strtok(dictionary,"\n");
     word[i] = token;
    /* walk through other tokens */
    while( token != NULL)
    {
       i++;
       token = strtok(NULL,"\n");
       word[i] = token ;
    }

    /* suffle */
    size_word = lines * MULTI_DICTIONARY;
    for (i = 0;i<size_word ;i++)
    {
        swap (&word[rand()%size_word ] , &word[rand()%size_word]);
    }


}

static void swap (char * first[] , char * second[] )
{
    char *temp = *first ;
    *first = *second;
    *second = temp;

}

int cmprchar (const void * data_1, const void * data_2)
{
    return strcmp(((char*)*(void**)data_1) , ((char*)*(void**)data_2) );
}






















