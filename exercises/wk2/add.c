#include <string.h> /* for a strlen strings */
#include  <stdlib.h>
#include  "add.h"

void add ( char *final_result, char *str1, char* str2)
{
	
	
	int temp = 0 ;
	int digit1 = 0;   /* temp int for the casting char from string 1*/
	int digit2 = 0;	  /* temp int for the casting char from string 2*/
	int i = 0;        /*index for the loop */


	int reminder =0;

	
	int len_str1 = strlen (str1) ;
	int len_str2 = strlen (str2) ;


	strrev(str1); 	 /*reverse the string a fit  for thr rigth digits numbers*/
	strrev (str2);	/*reverse the string a fit  for thr rigth digits numbers*/
			
	for (i = 0; i < len_str1 || i < len_str2 ; i++)
	{
		if ( i < len_str1 )   /* if we came to the end of the string the digits equal zero */
			{
				digit1 =(int) (*(str1+i)) - (int)('0') ;
			}
		else 
			{
				digit1 = 0 ;
			}

		if ( i < len_str2 )		/* if we came to the end of the string the digits equal zero */
			{
				digit2 =(int) (*(str2+i))- (int)('0') ; ;
			}
		else 
			{
				digit2 = 0 ;
			}
		temp = digit1 + digit2 + reminder;   /*add the digits and check after if the answer is a two digits */
		
		if ( temp < 10)
		{
			final_result[i]=  (temp ) +'0' ;
			reminder =0;	
				
		}

		else     /* if temp is a 2 digits ,  */
		{
			
			temp = temp -10 ; 
			final_result[i] = temp + '0' ; 
			reminder = 1 ;
			
		}
		
	}
			
		 final_result[i]=reminder +'0';  /*if reminder left in the end*/
		 final_result[i+1]= '\0' ;      /* place null to end of the string */

		 strrev (final_result) ;
}








char *strrev(char *str )
{
	int i = 0;
	int len = strlen(str);
	char temp = ' ' ;
	for (i = 0  ; i< (strlen(str)/2) ; i++)
	{
		temp = str[i];
		str[i] = str [len - 1 - i] ;
		str [len - 1 - i] = temp; 
	}
return str ;
}




