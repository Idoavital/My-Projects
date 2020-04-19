
#include <stdio.h>
#include <stdlib.h> /*qsort */
#include <string.h> /* strcmp*/

#include "search.h"


typedef struct person
{
	char name[10] ;
	int age;
}
PERSON;

int cmprAge (const void * data1, const void * data2);

int cmprInt (const void * data_1, const void * data_2);

static void testSearch();

PERSON rd38[] = {
{"ido-1",35},
{"evgeni",34},
{"dani-1",2},
{"maayan",24},
{"guy-2",2},
{"beni",32},
{"eli",29},
{"moshe-2",35},
	{"violet", 3},
	{"john", 400},
	{"alex", 1},
	{"gary", 12},
	{"samwise", 26},
	{"harry", 27},
	{"conway", 30},
	{"vlad", 45},
	{"jane", 77},
	{"golem", 555},
};


int main(int argc, char *argv[])
{

    qsort(&rd38[0], 14, sizeof(PERSON), cmprAge);
    testSearch();
    printf("\n");
    return 0;
}

/**************** tests search ***********************/
static void testSearch()
{

    void * temp;
    PERSON find_test = {"ido-h",35} ;

printf("\n/**************** tests search ***********************/\n");

    temp = binarySearch(rd38, 14, sizeof(PERSON) , cmprAge, &find_test);

    if(temp==NULL)
    {
        printf("jump search failed to find data");
    }
    else
    {
        if ( ((PERSON*)temp)->age == 35 )
            printf ("find  binari= name %s age %d \n",((PERSON*)temp)->name , ((PERSON*)temp)->age );
        else
            printf("jump search failed to find data");
    }

    temp = jumpSearch(rd38, 14, sizeof(PERSON) , cmprAge, &find_test);

    if(temp==NULL)
    {
        printf("jump search failed to find data");
    }
    else
    {
        if ( ((PERSON*)temp)->age == 35 )
            printf ("find jump = name %s age %d \n",((PERSON*)temp)->name , ((PERSON*)temp)->age );
        else
            printf("jump search failed to find data");
    }


    /* try to find a member is not in the array */
    find_test.age = 800 ;
    temp = jumpSearch(rd38, 14, sizeof(PERSON) , cmprAge, &find_test);

    if(temp==NULL)
    {
        printf("jump search failed to find data - success \n");
    }
    else
    {
        if ( ((PERSON*)temp)->age == 35 )
            printf ("find jump = name %s age %d \n",((PERSON*)temp)->name , ((PERSON*)temp)->age );
        else
            printf("jump search failed to find data \n");
    }

    /* try to find a member is not in the array */
    find_test.age = 22 ;
    temp = jumpSearch(rd38, 14, sizeof(PERSON) , cmprAge, &find_test);

    if(temp==NULL)
    {
        printf("jump search failed to find data - success \n");
    }
    else
    {
        if ( ((PERSON*)temp)->age == 35 )
            printf ("find jump = name %s age %d \n",((PERSON*)temp)->name , ((PERSON*)temp)->age );
        else
            printf("jump search failed to find data \n");
    }

}



int cmprAge (const void * data1, const void * data2)
{
	 return (((PERSON*)data1)->age - ((PERSON*)data2)->age);
}

int cmprName (const void * data_1, const void * data_2)
{
		return strcmp(((PERSON*)data_1)->name,((PERSON*)data_2)->name );
}

int cmprchar (const void * data_1, const void * data_2)
{
		return strcmp(((char*)data_1) , ((char*)data_2) );
}

int cmprInt (const void * data_1, const void * data_2)
{
		return ((*(int*)data_1) - (*(int*)data_2) );
}

size_t prsomToNum(const void *data, const void *param)
{
	return	(size_t)((PERSON*)data)->age;
}
