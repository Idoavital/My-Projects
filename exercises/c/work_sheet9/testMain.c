
# include <stdlib.h>
# include <string.h>
#include "MEM.h"

int main (int argc, char *argv[])
{
	char  str[100] = "1234567890123456789012345678901234567890";
	char prt[] = "abcabcabcabcabcabcabcabcabcabcabcabcabcabcabc,";
	int i = 0 ;
 
		
	/*	str = malloc (120);
		prt = (char *)str;
	*/
				
			printf ("dst %p: %s\n", prt, prt );
			printf ("prt %p: %s\n", str, str);
			

		for ( i = 0 ; i < 100 ; i ++)
		{
		
			printf ("1- :%p: %c\n", str+i, str[i] );
			

		}

			/* str = Memset(str,'t',38); 	*/
			Memmove (str+4 ,str+1 ,30); 
	
		 /* prt = (char *)str; */


		 /* Memmove (str+5 ,str ,6); */
		printf ("dest %p: %s\n",prt , prt  );
		printf ("src %p: %s\n", str, str);

	
		for ( i = 0 ; i < 100 ; i ++)
		{	
			printf ("2- :%p: %c\n", prt+i, prt[i] );
		}


	return 0;
}
