#include <stddef.h> /* size_t*/
#include <stdio.h>

#include "recursion.h"
#include "SList.h"
#include "stack.h"


int fibonacci (int n)
{
    if (n <= 1)
      return n;

    return (fibonacci(n-1) + fibonacci(n-2));
}

int fibonacciNoRec (int n)
{
    int i  =0;
    int sum =1 ;
    int temp = 0;

    if (n == 1)
    {
        return 1;
    }
    for (i = 2;i<=n ; i++)
    {
        sum +=temp;
        temp = sum - temp;
    }
return sum;
}

size_t Strlen (char * str)
{
    if (*str == '\0')
        return 0;
    return (1+Strlen (str+1));
}

int Strcmp (const char * str_1 ,const char * str_2 )
{
    if ((*str_1=='\0' ) ||((*str_1 - *str_2)!= 0)  )
        return (*str_1 - *str_2);
    return Strcmp((++str_1), (++str_2));
}
char *Strcpy(char *dest, const char *src)
{
    *dest = *src ;
    if (*src != '\0')
        Strcpy (++dest,++src) ;
     return dest;
}



Node_t * flipRecursion (Node_t * curr )
{
    Node_t * head = NULL;
    if (NULL == curr->next)
    {
        return curr;
    }

    head  = flipRecursion (curr->next );
    curr->next->next = curr;
    curr->next = NULL;

    return head;
}


 void sortStack(STACK* stack)
{
    int temp = 0;
    if(!isEmpty(stack))
    {
        temp = *(int*) Peek(stack);
        Pop(stack);
        sortStack( stack);
        sortInsret(stack ,temp);
    }

}
 void sortInsret(STACK* stack , int temp)
{
    int new_elm = 0;

    if(isEmpty(stack) || temp >=new_elm )
    {
        Push(stack, &temp);

    }
    else
    {
        new_elm = *(int*)Peek(stack);
        Pop(stack);
        sortInsret(stack, temp);

        Push(stack, &new_elm);
    }
}






