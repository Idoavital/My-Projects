#include <string.h> /* strcpy */
#include <stdio.h> /* printf */
#include "stack.h"



typedef struct person
{
	char name[20];
	int age;
} PERSON;


int main (int argc, char *argv[])
{
	PERSON *ptr;
	PERSON p = {"ido ", 5 };
	STACK *s;
	
	
	s = CreateStack (10, sizeof(PERSON));
	
	/*********************test empty and full **************************/
	printf ("test empty - if stack empty print 1 : %d \n", isEmpty(s) );
	
	printf ("test full - if stack full print 1 else 0 : %d \n", isFull(s) );
	
	Push (s,&p);
	

	strcpy (p.name, "dani ");
	p.age = 6; 
	Push(s, &p);
	
	strcpy (p.name, "momo");
	p.age = 20; 
	Push(s, &p);
	
	
	ptr = (PERSON*) Peek(s);
	printf ("\n first peek \nname: %s age %d \n", ptr->name ,ptr->age);
	
	/****************test peek*******************************/
    if(0 == strcmp(ptr->name, "momo") &&

    	(20 == ptr->age))

    {

        printf("\n%s succeeded\n", "Test_Peek()");

    }

    else

    {

        fprintf(stderr, "%s FAILED\n", "Test_Peek()");

    }
	
	
	Pop(s);
	
	ptr = (PERSON*) Peek(s);
	printf ("\n second peek \nname: %s age %d \n", ptr->name ,ptr->age);
	
	printf ("test empty - if stack not empty print 0 : %d \n", isEmpty(s) );
		
		
	
	Destroy(s);
	
	s = NULL ;
	
	return 0;
}


