#include <stdio.h>
#include <math.h> /* pow*/
#include <string.h>
#include <ctype.h> /* isdigit */
#include <stdlib.h> /* strtod*/

#include "calc.h"
#include "stack.h"

enum assoc {LEFT , RIGHT};

typedef double ( *ACT ) (double num1 , double num2);

typedef struct lut_t
{
    int precedence;
    int associativity;
    ACT fun;

}LUT ;


static double add (double num1 , double num2);

static double minus (double num1 , double num2);

static double multiplication (double num1 , double num2);

static double divide (double num1 , double num2);

static double power(double num1 , double num2);
/*calc the two last numbers in the stack */
static void calc2LastElem(STACK * stack_out, LUT lut_now );
/* peek from the stack operator and calculate the last 2 number in the stack numbers (out)*/
static void peekAndPush (STACK* stack_operator, STACK* stack_out );

static LUT lut[256];

void calcInit ()
{

    lut[0].precedence = 0;
    lut[0].fun = NULL;
    lut[0].associativity = LEFT;

    lut['-'].precedence = 2;
    lut['-'].fun = minus;
    lut['-'].associativity = LEFT;

    lut['+'].precedence = 2;
    lut['+'].fun = add;
    lut['+'].associativity = LEFT;

    lut['*'].precedence = 3;
    lut['*'].fun = multiplication;
    lut['*'].associativity = LEFT;

    lut['/'].precedence = 3;
    lut['/'].fun = divide;
    lut['/'].associativity = LEFT;

    lut['^'].precedence = 4;
    lut['^'].fun = power;
    lut['^'].associativity = RIGHT;

    lut['('].precedence = 5;
    lut['('].fun = NULL;
    lut['('].associativity = RIGHT;

    lut[')'].precedence = 0;
    lut[')'].fun = NULL;
    lut[')'].associativity = LEFT;

}
/* initizaltion the LUT of the calc*/
double Calculate (const char *string)
{
    STACK *stack_out = NULL;
    STACK *stack_operator = NULL;
    char *ptr_d = NULL;
    int flag = 1;

    int temp_operator = 0;
    double temp_ret =0;

    stack_out = CreateStack( strlen(string) , sizeof(double) );
    stack_operator = CreateStack(strlen(string), sizeof(LUT));


    ptr_d = (char *)string ;
    while(*ptr_d != '\0')
    {
        /* skip on spaces*/
        while(*ptr_d == ' ')
        {
            ptr_d += 1 ;
        }

        if(isdigit(*ptr_d)||( (*ptr_d =='-') &&flag == 1 ))
        {
            temp_ret = strtod(ptr_d, &ptr_d); /* */
            Push(stack_out , &temp_ret );
            flag =0;

        }
         else
         {
            temp_operator = (int)(*ptr_d);

            /* while (there is an operator at the top of the operator stack with greater precedence or the operator at the top of the operator stack has
                        equal precedence) and  (the operator is left associative) */
            while( !isEmpty( stack_operator)
                                  && ((LUT*)Peek(stack_operator))->precedence >= lut[temp_operator].precedence
                                            &&((LUT*)Peek(stack_operator))->precedence  != 5
                                                    && (lut[temp_operator].associativity == LEFT))
            {
                peekAndPush ( stack_operator, stack_out );

            }

            /*if is a right bracket calc the string until the left bracket */
            if (temp_operator != ')')
            	{
                	Push(stack_operator, &lut[temp_operator]);
               		 flag =1;
                }
            else
            {
                while(((LUT*)Peek(stack_operator))->precedence  != 5)
                {
                    peekAndPush ( stack_operator, stack_out );
                }
                Pop(stack_operator);
                flag = 0;
            }
            ptr_d += 1;


        }

    }

     /* while there are still operator  on the stack */
    while (!isEmpty( stack_operator))
    {
        peekAndPush ( stack_operator,  stack_out );
    }
    temp_ret  =*(double*)Peek(stack_out);
    Destroy(stack_operator);
    Destroy(stack_out);
    return temp_ret;
}


/****************************static functions *************************************************/
static void peekAndPush (STACK* stack_operator, STACK* stack_out )
{

    LUT temp_lut;

    temp_lut = *(LUT*) Peek(stack_operator);
    Pop(stack_operator);
    calc2LastElem(stack_out, temp_lut );

}


static void calc2LastElem(STACK * stack_out, LUT lut_now )
{
    double ret = 0;
    double num_1 = 0;
    double num_2 = 0;

    num_2 = * (double*)Peek(stack_out);
    Pop(stack_out);

    num_1 =* (double*)Peek(stack_out);
    Pop(stack_out);

    ret = lut_now.fun(num_1 , num_2);

    Push(stack_out, &ret);

}
static double add (double num1 , double num2)
{
 return (num1 + num2);
}

static double minus (double num1 , double num2)
{
 return (num1 - num2);
}

static double multiplication (double num1 , double num2)
{
 return (num1 * num2);
}

static double divide (double num1 , double num2)
{
    double num = NAN;
    if (num2 == 0)
    {

        return num;
    }

 return (num1 / num2);
}
static double power(double num1 , double num2)
{
    return (pow(num1, num2));
}
