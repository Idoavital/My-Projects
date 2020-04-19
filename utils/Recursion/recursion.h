#ifndef RECURSION_H_INCLUDED
#define RECURSION_H_INCLUDED
#include "SList.h"
#include "stack.h"

int fibonacci (int n);

int fibonacciNoRec (int n);

size_t Strlen (char * str);

int Strcmp (const char * str_1 ,const char * str_2 );

char *Strcpy(char *dest, const char *src);

Node_t * flipRecursion (Node_t * curr);

void sortStack(STACK* s);

void sortInsret(STACK* stack , int temp);

#endif /* RECURSION_H_INCLUDED*/
