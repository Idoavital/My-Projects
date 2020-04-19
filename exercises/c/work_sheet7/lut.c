# include <stdio.h>
#include <stdlib.h>


#define LUT_SIZE  256   /* the size of the array table*/
#define EXIT  27		/*	the ascii of exit*/

void Apressed();
void Tpressed();


static void (*pi_function[LUT_SIZE])() ;

int main (int argc , char * argv [])
{
	
	int ch_input =0 ;
	pi_function['a'] = Apressed;
	pi_function['t'] = Tpressed;

    system("stty -icanon -echo");

	while (ch_input != EXIT )
	{
		
		ch_input = getchar();
		if (pi_function[ch_input] != NULL)
			pi_function[ch_input]();
	}

	system("stty icanon echo");

return 0;
}

void Apressed()
{
	printf ("A pressed\n");
}

void Tpressed()
{
	printf ("T pressed\n");
}
