
#include <stdio.h>
#include <stdlib.h>

#include "fsm.h"

void testFsmSugg(size_t no_elem, size_t size_elem);

int main (int argc, char *argv[])
{
	void * temp;
	void * temp1;
	void * temp2;
	FSM_T *pool;
	pool = (FSM_T *)malloc (176);
	
	testFsmSugg(10 , 3);
	FSMInit (pool, 10 , 3);
	
	
	printf ("address pool %p\n",(void *)pool);
	
	temp = FSMAlloc(pool);
	printf ("address malloc%p\n",temp);
	
	temp1 = FSMAlloc(pool);
	printf ("address malloc%p\n",temp);
	
	temp2 = FSMAlloc(pool);
	printf ("address malloc%p\n",temp);
	
	FSMFree(temp1);
	
	FSMFree(temp2);
	
	return 0;
}

void testFsmSugg(size_t no_elem, size_t size_elem)
{
	size_t  sugg = 0;
	sugg = FSMSuggesteSize( no_elem,  size_elem);
	
	printf ("\nsuggested size byte : %lu \n",sugg );
}
