#include <stdio.h>
#include <stdlib.h> /* malloc */


#include "vsm.h"

typedef struct person 
{
	char name[20];
	int age;
} PERSON;


void testMallocdisfreg ();
void testMallocFixSize();
void testMallocInTheEnd();
void testfailedMalloc();
void testfree();
void testFreeSizeAfterDef ();

int main (int argc, char *argv[])
{
	testMallocFixSize();
	testMallocdisfreg ();
	
 	testMallocInTheEnd();
	testfailedMalloc();
	testfree();
	testFreeSizeAfterDef ();

	return 0;

}

void testMallocFixSize()
{
	VSM_T * vsm;
	char *ptr;
	PERSON * test1;
	printf  ("\n ******* test MallocFixSize ************ \n");
	ptr = malloc (1000);
	
	vsm = VSMInit(ptr ,1000); 	
	
	printf  (" vsm : %p \n",(void*)vsm);
	
	test1 = VSMAlloc(vsm, 976);
	if (test1 == NULL)
		printf (" failed allocte fix size \n");
	else
		printf  ("success: malloc fix size: %p\n",(void*)test1);
			
		VSMFree (test1);
	
	free (ptr);
}



void testMallocdisfreg ()
{
	VSM_T * vsm;
	char *ptr;
	PERSON * test1;
	PERSON *test2;
	PERSON *test3;
	PERSON *test4;
	PERSON *test5;
	PERSON *test6;
	PERSON *test7;
	PERSON *test8;
	
	ptr = malloc (1500);
	
	
	printf  ("\n ******* test Defragmentation ************ \n");
	vsm = VSMInit(ptr ,1500); 	
	
	test1 = VSMAlloc(vsm, 200);
	printf ("size  after 200 is : %lu \n ",VSMFreeSpace(vsm));
	test2 = VSMAlloc(vsm, 300);
	
	test3 = VSMAlloc(vsm, 154); 
	printf ("size  after 664 is : %lu \n ",VSMFreeSpace(vsm));
	test4 = VSMAlloc(vsm, 100); 
	
	test5 = VSMAlloc(vsm, 100); 
	test6 = VSMAlloc(vsm, 200); 	
	
	test7 = VSMAlloc(vsm, 180); 	
	
	test8 = VSMAlloc(vsm, 100); 
	printf ("size  after 200 is : %lu \n ",VSMFreeSpace(vsm));
	
	
	printf("the free space - need to be  and the return value - %lu\n", VSMFreeSpace (vsm));
	printf("the large space - need to be  and the return value - %lu\n", VSMLargeSpace (vsm));
	VSMFree (test3);
	
	printf("the free space - need to be  and the return value - %lu\n", VSMFreeSpace (vsm));
	printf("the large space - need to be  and the return value - %lu\n", VSMLargeSpace (vsm));
	
	VSMFree (test4);
	
	printf("the free space - need to be  and the return value - %lu\n", VSMFreeSpace (vsm));
	printf("the large space - need to be  and the return value - %lu\n", VSMLargeSpace (vsm));
	
	VSMFree (test6);
	VSMFree (test7);
	
	test4 = VSMAlloc(vsm, 380); 
	if (test4 == NULL)
			printf (" failed allocte fix size \n");
	else
		printf  ("success: after 380 byte Defragmentation: %p\n",(void*)test4);	

	
	test8->age = 20;
	test5->age = 20;
	test4->age = 20;

	test2->age = 20;
	test1->age = 20;


	free (ptr);
}

void testMallocInTheEnd()
{
	VSM_T * vsm;
	char *ptr;
	PERSON * test1;
	PERSON *test2;
	PERSON *test3;
	PERSON *test4;
	
	ptr = malloc (1000);
	
	printf  ("\n ******* test in the end ************ \n");
	vsm = VSMInit(ptr ,1000); 	
	
	test1 = VSMAlloc(vsm, 236);
	
	test2 = VSMAlloc(vsm, 236);
	
	test3 = VSMAlloc(vsm, 236); 
	
	test4 = VSMAlloc(vsm, 228); 
	
	if (test4 == NULL)
			printf (" failed allocte fix size \n");
	else
		printf  ("success: malloc in the last : %p\n",(void*)test4);
		
	test1->age = 20;
	test2->age = 20;
	test3->age = 20;		

	free (ptr);

}




void testfailedMalloc()
{
	VSM_T * vsm;
	char *ptr;
	PERSON * test1;
	PERSON *test2;
	PERSON *test3;
	PERSON *test4;
	PERSON *test5;
	
	ptr = malloc (1000);
	
	printf  ("\n ******* test try to failed ************ \n");
	vsm = VSMInit(ptr ,1000); 	
	
	test1 = VSMAlloc(vsm, 236);
	
	test2 = VSMAlloc(vsm, 236);
	
	test3 = VSMAlloc(vsm, 236); 
	
	test4 = VSMAlloc(vsm, 208); 
	
	test5 = VSMAlloc(vsm, 8); 
	
	if (test5 == NULL)
			printf (" success to failed \n");
	else
		printf  ("failed : malloc shoud be null : %p\n",(void*)test5);
		
	test1->age = 20;
	test2->age = 20;
	test3->age = 20;
	test4->age = 20;		
	
  free (ptr);			
}



void testfree()
{
	VSM_T * vsm;
	char *ptr;
	PERSON * test1;
	printf  ("\n ******* test free Size ************ \n");
	ptr = malloc (1000);
	
	vsm = VSMInit(ptr ,1000); 	
	
	if (976 == VSMFreeSpace(vsm) )
		printf ("success size when empty is right shoud be 976 - free size if %lu \n" ,VSMFreeSpace(vsm));
	else
		printf ("failed size when empty is right :shoud be 976 - free size if %lu \n" ,VSMFreeSpace(vsm));
	printf  (" vsm : %p \n",(void*)vsm);
	
	
	test1 = VSMAlloc(vsm, 976);		
	
	if (0 == VSMFreeSpace(vsm) )
		printf ("success size when empty is right shoud be 0 - free size if %lu \n" ,VSMFreeSpace(vsm));
	else
		printf ("failed size when empty is right :shoud be 0 - free size if %lu \n" ,VSMFreeSpace(vsm));
		
		
	test1->age = 20;
	free (ptr);
}

void testFreeSizeAfterDef ()
{
	VSM_T * vsm;
	char *ptr;
	PERSON * test1;
	PERSON *test2;
	PERSON *test3;
	PERSON *test4;
	PERSON *test5;
	PERSON *test6;
	PERSON *test7;
	PERSON *test8;
	
	ptr = malloc (1500);
	
	
	printf  ("\n ******* test free size after Defragmentation ************ \n");
	vsm = VSMInit(ptr ,1500); 	
	
	test1 = VSMAlloc(vsm, 200);
	
	if (1260 == VSMFreeSpace(vsm) )
		printf ("success size when empty is right shoud be 1260 - free size if %lu \n" ,VSMFreeSpace(vsm));
	else
		printf ("failed size when empty is not right :shoud be 1260 - free size if %lu \n" ,VSMFreeSpace(vsm));
	
	test2 = VSMAlloc(vsm, 300);
	
	test3 = VSMAlloc(vsm, 154); 
	
	if (764 == VSMFreeSpace(vsm) )
		printf ("success size when empty is right shoud be 764 - free size if %lu \n" ,VSMFreeSpace(vsm));
	else
		printf ("failed size when empty is not right :shoud be 764 - free size if %lu \n" ,VSMFreeSpace(vsm));
	
	test4 = VSMAlloc(vsm, 100); 
	
	test5 = VSMAlloc(vsm, 100); 
	test6 = VSMAlloc(vsm, 200); 	
	
	test7 = VSMAlloc(vsm, 180); 	
	
	test8 = VSMAlloc(vsm, 100); 
	
	if (0 == VSMFreeSpace(vsm) )
		printf ("success size when empty is right shoud be 0 - free size if %lu \n" ,VSMFreeSpace(vsm));
	else
		printf ("failed size when empty is not right :shoud be 0 - free size if %lu \n" ,VSMFreeSpace(vsm));

	
	VSMFree (test3);
	VSMFree (test4);
	
	
	if (280 == VSMFreeSpace(vsm))
	{
		printf ("success size when empty is right shoud be 280 - free size if %lu \n" ,VSMFreeSpace(vsm));
	}
	else
	{
		printf ("failed size when empty is not right :shoud be 280 - free size if %lu \n" ,VSMFreeSpace(vsm));
	}
	
	
	test8->age = 20;
	test7->age = 20;
	test6->age = 20;
	test5->age = 20;
	test4->age = 20;
	test3->age = 20;
	test2->age = 20;
	test1->age = 20;
	free (ptr);
}







