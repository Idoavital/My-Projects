
#include "Pali.h"


int IsPalindrome (const char *str)
{
	int flag = 0; /* check equal */
	int counter = 0 ;
	int len = strlen(str); 


	/*	eaual the first char + counter in the string to the last char - counter in the string*/

	for (; counter < (len/2) ; counter++)
		if (*(str+counter) == *(str +len-counter -1)) /* if equal change flag to 1*/
		{
			flag=1; 
		}	
		else 
		{
			flag=0;	
		}


return flag;
}
