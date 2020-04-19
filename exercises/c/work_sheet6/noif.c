#include <stdio.h>

/* the functoin get a char and check if the bits number 6 and 2 both on*/
int bothOn(	unsigned char ch);

/* the functoin get a char and check if the bits number 6 and 2 both on*/
int twoOrSixOn(	unsigned char ch);

/* the function get a char and swap between to bits number 5 and 3*/
int swap (unsigned char ch);

/* the functoin check what is closet number that is divided in 16 */
int divideSixteen ( unsigned int );

/* the functoin swap between two number without a temp variable*/
void swapNoTemp (int *first , int *second);

/*the function count the number of a set bits*/
int countBit (unsigned num);

/*the function count the number of a set bits without a loop*/
int countBitWithOutLoop (unsigned number);

/* the functoin get a float number from the user and print it in a binary number*/
void printFloat ();



int main (int argc , char * argv[])
{
	int test_swap_1 =5 , test_swap_2 = 22;
	printf ("**************************************************************\n");
	printf ( "test bothOn for a %d \n" ,bothOn('a'));
	printf ( "test bothOn for j %d \n" ,bothOn('j'));
	printf ( "test bothOn for r %d \n" ,bothOn('r'));

	printf ("**************************************************************\n");
	printf ( " test 22 divided six teen with remineder %d \n ", divideSixteen (22));
	printf ( " test 33 divided six teen with remineder %d \n ", divideSixteen (33));
	printf ( " test 64 divided six teen with remineder %d \n ", divideSixteen (64));

	printf ("**************************************************************\n");
	printf ("befor - number 1 : %d , number 2 : %d \n", test_swap_1 ,test_swap_2);
	swapNoTemp (&test_swap_1, &test_swap_2);
	printf ("after - number 1 : %d , number 2 : %d \n", test_swap_1, test_swap_2);

	printf ("**************************************************************\n");
	printf ("number of bits on in 33: %d \n", countBit (33) );
	printf ("number of bits on in 7: %d \n", countBit (7) );
	printf ("number of bits on in 0: %d \n", countBit (0) );

	printf ("***********************count without loop***************************************\n");
	printf ("number of bits on in 33: %d \n", countBitWithOutLoop (33) );
	printf ("number of bits on in 7: %d \n", countBitWithOutLoop (7) );
	printf ("number of bits on in 0: %d \n", countBitWithOutLoop (0) );

	printf ("**************************************************************\n");
		printFloat ();



	
return 0;
}
/***************************************************/
int bothOn(	unsigned char ch)
{
	int two_on = (1 << 1 );
	int six_on = (1 << 5) ;
	
	
return ( (two_on & ch) && (six_on & ch) );
}

/*************************************************/

int twoOrSixOn(	unsigned char ch)
{
	int two_on = (1 << 1 );
	int six_on = (1 << 5) ;
	
	
return ( (two_on & ch) || (six_on & ch) );
}
/******************************************************/
int swap (unsigned char ch)
{

	int temp_three = ch & (1 << 2) ; 
	int temp_five = ch & (1 << 4) ;   

	ch =   ch | (1 << 2) ; /* set bit 3 to one */
	ch =  ch | (1 << 4) ; /* set bit 5 to one */

	ch &=   temp_five >> 2  ; /* set bit 5 in the place of bit 3 */
	ch &= 	temp_three << 2 ;	 /* set bit 3 in the place of bit 5 */

	return ch; 
}
/******************************************************/

int divideSixteen ( unsigned int user_num)
{
	
	unsigned int ret = 15 ;
		
	ret = user_num & ~ret ;

	return ret ;		
}

/******************************************************/
void swapNoTemp (int *first , int *second)
{
	
	*first = *first ^ *second  ;
    *second = *first ^ *second ;
	*first = *second ^ *first ; 


}	

/******************************************************/
 int countBit (unsigned number)
{
	int count = 0;

	if (0 == number )
		{
			return 0;
		}

	while ( number > 0)
	{
		if (1 & number )
		{
			count++;
		}
		number >>= 1;
		
	}

return count++;
}

/******************************************************/

int countBitWithOutLoop (unsigned number)
{

	number = number - ((number >> 1) & 0x55555555);

    number = (number & 0x33333333) + ((number >> 2) & 0x33333333);

    return (((number + (number >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;

}

/******************************************************/
void printFloat ()
{
    float number =0;	
	int size = sizeof (float) * 8 -1;
	unsigned int * temp = NULL ;



	printf ("enter a float number \n");
	scanf ("%f", &number);
	temp =(unsigned int *) &number;	

	while (size--)
	{
		printf("%d", *temp>>size & 1);
		
	}

}






