
#include <stdio.h>
#include <assert.h>
#include <string.h> /* strcpr */
#include "sortL.h"

enum param_person {AGE ,NAME , ERROR};

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
{"dani",2},
{"guy",26},
{"maayan",24},
{"beni",32},
{"eli",29},
	{"Violet", 3},
	{"John", 400},
	{"Alex", 1},
	{"Gary", 12},
	{"Samwise", 26},
	{"Harry", 27},
	{"Conway", 30},
	{"Vlad", 45},
	{"Jane", 77},		
	{"Golem", 555},		
};

static void PrintSortL(SORT_L *sl);
static int insertTest();
static int insertTest1();
static void TesteSortCreate(void);
int CmpAge (const void *param1, const void *param2);
static int SortMergeTest();
/* select the parameter to search on the list by the param ,
	return the 1 if there is a match	*/
int match_age (const void *data1, const void *data2, void *param);
void testMatch();

static SORT_L *sl2;
static SORT_L *sl;


int main (int argc, char *argv[])
{
	
	TesteSortCreate();
	insertTest();
	PrintSortL(sl);
	insertTest1();
	PrintSortL(sl2);
	
	SortMergeTest();
	
	testMatch();
	return 0;
	
}


static int insertTest()
{
	if (1 != SortIsEmpty(sl))
	{
		return 0;
	}
	
	if (0 != SortSize(sl))
	{
		return 0;
	}
	
	SortInsert(sl, &rd38[0]);
	SortInsert(sl, &rd38[1]);
	SortInsert(sl, &rd38[2]);
	SortInsert(sl, &rd38[3]);
	SortInsert(sl, &rd38[5]);
	SortInsert(sl, &rd38[6]);
	SortInsert(sl, &rd38[7]);
	
	
	if (8 != SortSize(sl))
	{
		return 0;
	}

	return 1;
}

static int insertTest1()
{
	sl2 = SortCreate(CmpAge);
	
	SortInsert(sl2, &rd38[8]);
	SortInsert(sl2, &rd38[9]);
	
	SortInsert(sl2, &rd38[10]);
	SortInsert(sl2, &rd38[11]);
	SortInsert(sl2, &rd38[12]);
	SortInsert(sl2, &rd38[13]);
	SortInsert(sl2, &rd38[14]);
	
	
	return 1;
}


void TesteSortCreate(void)

{ 

    sl = SortCreate(CmpAge);
    if (sl != NULL)
    {
        printf("TestDLCreate suceedeed\n");
    }
    else
    {
        printf("TestDLCreate failed \n");
    }

}


static void PrintSortL(SORT_L *sl)
{
	SORT_ITER_T it;
	PERSON *temp_person;
	
	printf("---------------------------------------------------------\n");
	for (it = SortBegin(sl); 1 != SortIsEqual(SortEnd(sl), it) ; it = SortNext(it))
	{
		temp_person = (PERSON *)SortGetData(it);
		printf("%s is %d old\n", temp_person->name, temp_person->age);
	}
	printf("---------------------------------------------------------\n");
}

static int SortMergeTest()
{
	SortMerge(sl, sl2);
	
	PrintSortL(sl);

	return 1;
}

int CmpAge (const void *param1, const void *param2)
{
	PERSON *person1 = NULL;
	PERSON *person2 = NULL;

	assert(NULL != param1 && NULL != param2 );

	person1 = (PERSON *)param1;
	person2 = (PERSON *)param2;

	return ( person1->age > person2->age ? 1: 0);
}

/* select the parameter to search on the list by the param ,
	return the 1 if there is a match*/
int match_age (const void *data1, const void *data2, void *param)
{
	switch (*(size_t*)param )
	{
	case AGE:
	
		if (((PERSON*)data1)->age == *((int*)data2))
			{
				return 1;
			}
	case NAME :
		if (0 == strcmp (((PERSON*)data1)->name , (char*)data2))
			{
				return 1;
			}
	}
	return 0;
}
void testMatch ()
{
	int age = 0;
	SORT_ITER_T it = SortBegin(sl);
	int x = 35;
	it = SortFind (sl,it, match_age , (void*) &x,(void*) &age);
	printf ("age find is  %d",((PERSON*)SortGetData(it))->age );
	
}

