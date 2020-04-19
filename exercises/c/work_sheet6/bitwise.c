#include <stdio.h>

/* the function get a number and return 1 if is a power of 2 , and if not return 0 */
int isPow (unsigned int x) ;

/*the function get x and y calc x (2^y)*/
double dubPow2 (unsigned int x, int y) ;

/* the functoin return the number add one */
int addOne (unsigned int ) ;

/* the function get array of integer and and print the number that have exactly 3 bits on */
void  printThree (unsigned int [], int ) ;

/* the function print a mirror of the number*/
int mirrorWithLoop (int ) ;

/* the function print a mirror of the number without a loop*/
unsigned int mirrorWithOutLoop (unsigned int x );

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


	
	
/********************* test *******************************/
	unsigned int arr[] = {4 ,2 ,7 ,1212};
	int test_swap_1 =5 , test_swap_2 = 22;



	printThree( arr ,4);


	printf ("miror 2341 :  %u " , mirrorWithLoop (2341));


	 /*printf(" %g \n",dubPow2(x,y));
	printf("  %d \n",addOne(x) );		 */



		
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

/***********************************************/
double dubPow2 (unsigned int x, int y)
{

	double ret = 0 ;

		ret = x << y;

return ret;

}

/*******************************************************/
int isPow (unsigned int x)
{

	int y;

	y = ((x & (x - 1)) == 0) ? 1 : 0;
	
	return y;
}


/* ****************************************************/
int addOne(unsigned int x)
{
	int num_add = 1 ;


	while (x & num_add)   /* find the first zero bit*/
	{
			x = x ^ num_add ;	/* change the first bits to zero*/
			num_add <<= 1;
			
	}

		x = x ^ num_add ;  /* after find zero we change him to one */

	
return x ;
}

/***************************************************************/

void  printThree (unsigned int arr[] , int size) 
{
	int i = 0;			/* loop index */
	int count = 0;	   /* count the 1 bits*/
	int temp = 0;  		 

	for  (i = 0; i < size; i++ )   /* loop for a run on the array */
	{	

		temp = arr[i];
			
		while ( temp > 0 )  	/*  loop for check evry bit separate */
		{	
			if (temp & 1)		/* check if there is the bit is on*/
			{
				count++;
			}
			temp >>= 1;			
		}	

		if (3 == count )  
		{	
			printf ("to the number %d there is 3 bits of 1 \n", arr[i] );
		}
		count = 0;
	}

}

/************************************************************/
int mirrorWithLoop (int x)
{
	int mirror = 0;	
	int size = 16 ;

	while (size--)	
	{
		mirror |= (1 & x );
		mirror <<= 1 ;
		x >>= 1;
	}
		

return mirror>>1 ;
}

unsigned int mirrorWithOutLoop (unsigned int x )
{

	
	x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);	/* swap odd and even bits */
	
	x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);	/* swap consecutive pairs */
	
	x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);	/* swap nibbles ... */
	
	x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);	/* swap bytes	*/
	
	x = ( x >> 16             ) | ( x               << 16);	/* swap 2-byte long pairs	*/


return  x;
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
		
	number = number - ((number >> 1) & 0x55555555); /* counts odd and even bits */

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







