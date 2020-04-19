#include <string.h>
#include <stdio.h>

#include  "add.h"

int main (int argc , char* argv[])
{

	char str[20] = "4332425" ; 
	char str2[20] = "1222" ;
	char result[21] = "4332425" ; 

	printf ("-------------check for the add function----------------\n") ;
	printf(" %s + %s  = ", str, str2) ;
	add (result, str, str2) ;
	printf ("  %s ! \n\n", result) ; 

	strcpy(str , "88888");
	strcpy(str2 , "5654465");

	printf ("-------------check for the add function----------------\n") ;
	printf(" %s + %s  = ", str, str2) ;
	add (result, str, str2) ;
	printf ("  %s ! \n\n", result) ; 



return 0 ; 
}
