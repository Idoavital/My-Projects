#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include "vector.h" 

void checkCreate (VECTOR * v);

void checkPush (VECTOR * v);

typedef struct person
{
	char name[20];
	int age;
} PERSON;

static PERSON prr[5] =
	{
	{"moshe", 28},
	{"gad" , 20},
	{"guy", 12},
	{"dani", 30},
	{"bibi", 50},
	};

int main (int argc, char *argv[])
{
		
	VECTOR *v1 =  vCreate(10, sizeof(PERSON));
	
	VECTOR *v2 =  vCreate(20, sizeof(PERSON));
	
	VECTOR *v3 =  vCreate(0, sizeof(PERSON));
	
	
/***** check vCreate  ****/
	checkCreate(v1);
	checkCreate(v2);
	checkCreate(v3);

/****** check vPush *****/
	checkPush(v3);

	vDestroy (v1);
	vDestroy (v2);
	vDestroy (v3);
	return 0;
}


/************test vCreate*****************/

void checkCreate (VECTOR * v)
{

	printf ("*************** vCraete test ******************\n");
	if (NULL != v)
	{
		printf ("\n create check : pointer not NULL - seccess \n") ;
		printf (" capacity = %lu\n", vCapacity(v));
		printf (" size of array = %lu\n", vSize(v));
	}
	else
	{
		printf (" create check : pointer not NULL - failed \n") ;
	}
}


/*********************test vPush**********************************/
void checkPush (VECTOR * v)
{
	int i = 0;
	
	printf ("*************** vPush test ******************\n");
	printf (" capacity = %lu\n", vCapacity(v));
	printf (" size of array = %lu\n", vSize(v));
	
	for (i = 0; i < 5; i += 1)
	{
		vPush(v,&prr[i]);
		printf (" capacity = %lu\n", vCapacity(v));
		printf (" size of array = %lu\n", vSize(v));
	}
	

}





















