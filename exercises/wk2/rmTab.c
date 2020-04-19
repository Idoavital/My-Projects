
#include <stdio.h>
#include <string.h> 

char * RmSpace (char * str);


int main(int argc ,char * argv[])
{
	
		char str[50] = " ";				  /* use for test rmSpace functoin */
	
		strcpy(str,"  the   life   is  wondrful   ");
		printf(" before :---%s---- \n",str);
		RmSpace(str);
		printf ("-----%s----- \n", str);


		strcpy(str,"aaaa bbb cccc");
		RmSpace(str);
		printf (" \n -----%s----- \n", str);


return 0;

}


char * RmSpace (char * str)
{
	int i= 0 , j=0 ;  /* index for loop */
	int flag = 0;		/* flag to remember the first space in the middle of string*/
	int len = strlen(str);
	
	

		for (i=0 ; i<len  ; i++) /* remove white space from the start of the string */
		{
			if (*str ==' ')
				(strcpy(str,str+1));
			
		}		
	
		len = strlen(str);
		for (i= (len-1) ; i< (len) ; i--) /* remove white space from the end of the string */
		{
		
			if (*(str+ (len-1) ) ==' ')
			{
					*(str+(len-1)) = '\0' ; 
					len--;
			}
			else 
				{
					break;
				}	
		}

		len = strlen(str);  /* check the new length of the string*/
		
		for (i=0  ; i<len ; i++)  /* clean white tab from the middle of the string*/
		{
				if (*(str+i) == ' ')
				{
					for (j=i+1 ; *(str+j) == ' ' ; j++)
					{
						flag = 1;
					}
															
				}
				
				if ( flag == 1)  /*if there is a one space alrady */
				{
						strcpy(str+i ,str+j-1 ); /* copy the left string without the space*/
						j =0 ;
						flag = 0;
				}
				
				
		}
		

return str;
} 






