#include "sortL.h"
#include <stdio.h>
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
{"dani",38},
{"guy",26},
{"maayan",24},
{"beni",32},
{"eli",29},
}

int main (int argc, char *argv[])
{
	pritnf ("fdsfsedf");
	return 0;
	
}

int CmpAge (const void *param1, const void *param2)
{
	PERSON *person1 = NULL;
	PERSON *person2 = NULL;

	assert(NULL != param1 && NULL != param2 && "param1 and param2 cant be NULL");

	person1 = (PERSON *)param1;
	person2 = (PERSON *)param2;

	return ((person1->age > person2->age) ? 1 : 0);
}
