/******************************************************************************/
#include <sys/types.h>  /*fstat */
#include <sys/stat.h>  /*fstat */
#include <stdlib.h> /*malloc*/
#include <string.h> /*strcmp*/ /* strtok*/
#include <stdio.h>  /* fprint */ /*scanf */
#include <ctype.h> /*to lower */

#include "hash.h"

#define TABLE_SIZE 200

HASH_T *hash;
FILE * file;

static char *str = NULL;
static struct stat buf;
/************** static functoin ************************************/
static void testCreate ();
static void createDictionary ();
static void test_size();
static void test_destroy();
static size_t hashFunc(const void *str);
static int findWord();
static int cmpData(const void *data_1,const void *data_2);
static void test_remove();
static void test_removeNull();
/***************************************************/

int main(int argc, char *argv[])
{

    testCreate ();

    createDictionary ();
    findWord();
    test_size();
    test_remove();
    test_removeNull();
    test_destroy();

    return 0;
}

/* find word in the dictionary*/
static int findWord()
{
    int i =0;
    int find = 1;
    char end[22];
    void *find_data;
    while (find)
    {
        printf("\n enter word for Search \n enter end אo finsh \n");
        scanf("%s",end);
        printf("key = %lu\n" ,hashFunc (end));

        for( i = 0; end[i] != '\0' ; i++)
        {
            end[i]=tolower(end[i]);
        }

        find_data = HashFind(hash ,end);

        if(!find_data)
        {
            printf(" the word %s is not in the Dictionary",end);
        }
        else
        {
            printf(" the word %s is  in the Dictionary",(char*)find_data);
        }
        printf("\n");
        find = strcmp( "end" , end);
    }
 return 0;
}

static void testCreate ()
{
    hash= HashCreate(hashFunc , cmpData , TABLE_SIZE);
    if (hash == NULL)
    {
        printf(" failed craete \n");
        return;
    }
        printf(" success craete \n");

}
static void test_remove()
{
    /*********************************************************/
    size_t result = HashRemove(hash , "hello");
        /*********************************************************/
        if (0 != result)
        {
                printf ("\x1b[31m");
                printf ("\nHASH TABLE REMOVE FAILED\n");
                printf ("\x1b[0m");
        }
        /*********************************************************/
        else
        {
                printf ("\x1b[32m");
                printf ("\nHASH TABLE REMOVE SUCCESS\n");
                printf ("\x1b[0m");
        }
        /*********************************************************/
}

static void test_removeNull()
{
    /*********************************************************/
    size_t result = HashRemove(hash , "hello");

        printf("---try to remove a word that already deleted");
        /*********************************************************/
        if (0 != result)
        {
                printf ("\x1b[32m");
                printf ("\nHASH TABLE REMOVE FAILED - need to failed \n");
                printf ("\x1b[0m");
        }
        /*********************************************************/
        else
        {
                printf ("\x1b[31m");
                printf ("\nHASH TABLE REMOVE SUCCESS - need to failed\n");
                printf ("\x1b[0m");
        }
        /*********************************************************/
}
static void test_destroy()
{
    HashDestroy(hash);
}
static void test_size()
{

    size_t result = HashSize(hash);

        if (99163 != result)
        {
                printf ("\x1b[32m");
                printf ("\nsize is right \n");
                printf ("\x1b[0m");
        }
        else
        {
            printf ("\nsize is wrong \n");
        }
}

static size_t hashFunc(const void *str)
{
	char* str2 = (char*)str;
    size_t hash = 5381;
    int c;

    while ('\0' != (c = *str2++))
	{
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return (hash%TABLE_SIZE);
}

static int cmpData(const void *data_1,const void *data_2)
{
    return (strcmp((char*)data_1,(char*)data_2));
}


static void createDictionary ()
{
    char *token = NULL;

        /*open the dictionary file*/
    file = fopen("/usr/share/dict/american-english", "r");

    fstat(fileno(file), &buf);

    str = (char*)malloc(buf.st_size + 1);
    str[buf.st_size] = '\0';

    /*copy the words*/
    fread(str, sizeof(char), buf.st_size, file);

    fclose(file);

    /* get the first token */
    token = strtok(str,"\n");

    /* walk through other tokens */
    while( token != NULL )
    {
      HashInsert(hash,token);
      token = strtok(NULL,"\n");
    }
}
