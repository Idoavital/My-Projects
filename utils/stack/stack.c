#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc*/
#include <assert.h> /* use assert */
#include <errno.h>
#include "stack.h"

struct Stack
{	
	size_t top ;
	size_t sizeOfElm; 
	size_t noOfElms;
	char arrElms[1];
};




/* craete a new stack and allocte  memroy for it ,  return pointer to the head of the stack*/
/* the user shoud insert the number of elements snd the size of the element to craete the stack*/
STACK* CreateStack(size_t noOfElms, size_t sizeOfElm)
{


	STACK *s  = (STACK*)malloc(offsetof(STACK,arrElms) + sizeOfElm * noOfElms); 
	
	if (s == NULL) /* check if allocate memory failed */
	{
		assert (s != NULL && "FAILED TO ALLOCATE MEMORY ");
		return NULL;
	}
	
	
	s->noOfElms = noOfElms;
	s->sizeOfElm = sizeOfElm;
	s->top = 0;
	
	return s;
}

/* insert a new element to the stack*/
/* return int status of the actoin , -1: faild, 0: success, 1: stack is full */
int Push(STACK *s, void *elm)
{	
	assert (s != NULL && "S  CAN'T BE NULL ");
	
	if (1 == isFull(s))   /* check if the stack is full*/
	{		
		return -1;
	}
	
	memcpy (s->arrElms + (s->sizeOfElm * s->top) ,elm ,s->sizeOfElm );
	 /* update the head of the stack */
	s->top++;
	
	return 0;
}

/* take out the last element from the stack*/
void Pop(STACK *s)
{
	assert (s != NULL && "S  CAN'T BE NULL ");
	
	if (1 == isEmpty(s))
	{
		s->top = 0;
	}
	
	s->top--;

}

/*return pointer to the last element*/
void *Peek(STACK *s)
{	
	assert (s != NULL && "S  CAN'T BE NULL ");
	
	if (1 == isEmpty(s))
	{
		
		return NULL;
	}
	
	return (s->arrElms + (s->sizeOfElm * (s->top-1)));
}

/* destroy the stack and release the memory of the stack*/
void Destroy(STACK *s)
{
	assert (s != NULL && "S  CAN'T BE NULL ");	
	free(s);
	s = NULL;
}
/* check if the stack is empty*/
int isEmpty (STACK *s)
{
	assert (s != NULL && "S  CAN'T BE NULL ");
	
	if (s->top == 0)
	{
		return 1;
	}
	
	return 0;
}
/* check if the stack is full*/
int isFull (STACK *s)
{
	assert (s != NULL && "S  CAN'T BE NULL ");
	
	if (s->top == s->noOfElms)
	{
		return 1;
	}
	
	return 0;
}








