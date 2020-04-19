
#ifndef __STACK_H__

#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct Stack STACK;


/* craete a new stack and allocte  memroy for it ,  return pointer to the head of the stack*/
/* the user shoud insert the number of elements snd the size of the element to craete the stack*/
STACK *CreateStack(size_t noOfElms, size_t sizeOfElm);


/* insert a new element to the stack*/
/* return int status of the actoin , -1: faild, 0: success, 1: stack is full */
int Push(STACK *s, void *elm);

/* take out the last element from the stack*/
void Pop(STACK *s);

/*return pointer to the last element*/
void *Peek(STACK *s);

/* destroy the stack and release the memory of the stack*/
void Destroy(STACK *s);

/* check if the stack is empty*/
int isEmpty (STACK *s);

/* check if the stack is full*/
int isFull (STACK *s);

#endif /* __STACK_H__ */
