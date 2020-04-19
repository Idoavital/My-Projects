#include <stdio.h>
#include "String.h"
#include <assert.h>


/*code review - Guy*/ 
size_t Strlen (const char *s)
{ 
	

	int len=0;

	assert (NULL != s && "the pointer is NULL ");

	for (len = 0; *(s + len) != 0; len++);  
	;									/* loop only for a "len" counter */
	return len;	
}


char *Strcpy(char *dest, const char *src)
{
	/*copy all char from the src to dest */

	int i = 0;
 
	assert (NULL != dest && "the pointer is NULL ");
	
	for (i = 0; *(src+i) != '\0'; i++)  
	{									/*the loop stop in the end of the src*/
		*(dest + i) = *(src + i);			
	}

	*(dest + (i + 1)) = '\0';      /*copy  NULL cahr to end of the dest*/ 
	
	return dest;					
}

char *Strncpy (char *dest,const char *src, size_t n)
{	
	int i=0;
	for (i=0; i<n ; i++) /*the loop run 'n' time  */
	{	
		
		*(dest+i) = *(src+i);
		if (i > strlen(src)) /* if src less then n, write null*/ 
		{
			*(dest+i) = '\0';
		}
	
	}


	return dest;
}



int Strcmp (const char *s1, const char *s2)
{
	int i=0;

	/*there are 3 conditions for the loop that have to exist*/
    /* 1- if s1-string   didn't came to the end  */
	/* 2- if s2-string   didn't came to the end  */
	/* 3- if the char in (s1+i ) is equal to  (s2+i) */


	for (i=0; (*(s1+i) !='\0') && (*(s2+i)!='\0') && *(s1+i) == *(s2+i) ; i++ )
	;	
	
	return *(s1+i) - *(s2+i);
}

int Strcasecmp(const char *s1, const char *s2)
{
	char temp1=' ', temp2=' '; /*for a s1 and s2 chars respectively */
	int i=0;

	for ( i=0 ;*(s1+i)!='\0' && *(s2+i)!='\0' && temp1==temp2 ;i++)		
	{
		
		temp1=*(s1+i);
		temp2=*(s2+i);
		if (temp1<=90 && temp1 >=65)  /* if temp1 is a upper case change the letter to a lower-case*/
		{ 
				temp1 += 32;
		}
		if (temp2<=90 && temp2 >=65) /* if temp2 is a upper case change the letter to a lower-case*/
		{
				temp2 += 32;
		}
					

	}
	return temp1-temp2;
} 


char * Strdup (const char *s)
/*the function in  duplicates the given string */

{
	
	char *new_str = (char *) malloc ((Strlen(s) + 1) * sizeof (char)); /* save a place in the memory */
	new_str= Strcpy(new_str,s);  /*copy the given string */ 

	return (char*) new_str ;
}
		

char *Strchr(const char *s, int c)
/* searches for the first occurrence of the character c*/
{
		int i = 0;
		for (i=0; *(s+i)!= c && *(s + i) != '\0'; i++)
		{}  /* the loop stop in the first occurrence of the character or in the end of string*/
		
		

	return (char *)(s+i);	
}
 

/*  the functoin add the src stirng to the destination string */
char *Strcat(char *dest, const char *src) 
{
	int i = 0;	
	int len_d = 0;
	len_d = Strlen(dest) - 1;

	for (i = 0; *(src+i) != '\0' ;i++, len_d++) /*loop that start from the end of dest ,length src time*/
	{
		*(dest+len_d) = *(src+i); /* copy the src string*/
	}

	*(dest+len_d) ='\0';


	return dest;
}

  char *Strncat(char *dest, const char *src, size_t n)
{
	
	int len_d = 0;
	len_d = Strlen(dest) - 1;
	Strncpy((dest+len_d),src,n) ;


	return dest;
}  


 /* function finds the first occurrence of the substring needle in the string haystack */
char *Strstr(const char *haystack, const char *needle)
{
	int cmp=0;   /*flag to compaire the cahrters */
	int counter =0 ;
	
	int i=0;
	int len_hay = 0;
	int len_need = 0;
	

	len_hay = Strlen(haystack) ;
	len_need = Strlen(needle) ;

	for (i= 0; i < (len_hay - len_need) && cmp == 0 ;i++ )
	{
		if (*(haystack+i) == *(needle))  /*is the first needle char is equal then check all the substring*/
			{	
				for (cmp = 0 ,counter=0; counter < len_need; counter++)
				{
					if (*(haystack + i + counter) == *(needle + counter))
					{
						cmp = 1;
					}
					else 
					{
						cmp = 0;
					}
						
				}
			}
	}
	i--;
	return (char *)(haystack+i);
}


/* calculates the length of the initial segment of s which consists entirely of characters accept  */
size_t Strspn(const char *s, const char *accept)
{
	
	int num_cmp = 0;
	int cmp = 0;
	int i= 0 ,j =0;
	

	for (i= 0; i < Strlen(s) ;i++ )
	{

		for (j = 0; j < Strlen(accept); j++)
   		{

			if ( *(s+i) == *(accept+j) )
			{		
		
				num_cmp++;		
				break;
			}
			else if( j == Strlen(accept) - 1 ) 
			return num_cmp;  
			
		}
		
	}
	return num_cmp;
}

 /* split string into tokens */
char *Strtok(char *str, const char *delim)
{
	int i=0, j=0; /* 2 variables for a for loop index  */
	int flag =0;  /* if there is equality between the delim to str*/
	
	static char  * tok = NULL  ; /* remind the  equality*/
	static int end_str = 0;  /*remind  if the first loop come to her end */


		if (end_str==1) 
		{
			return NULL;
		}
		if (tok == NULL )
		{
			tok =  str ;
		}

	str = tok ;
		
	
		for (i = 0;   i < Strlen(str) && flag == 0; i++)	/* */
		{
			for (j = 0 ;j < Strlen(delim) ;j++ )
			{
				if ( *(str+i) == *(delim+j))
				{	
					*(str+i) = '\0';
					tok = (str+i+1); 
					flag=1;
					break;
				}		
			}		
		}
		
		
		if (i == Strlen(str) )
		{
			end_str = 1;
		}

return str;
}



