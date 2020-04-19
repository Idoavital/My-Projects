#include <stdio.h>
#include <strings.h>


char *Strcpy(char *str1,const char *STR2);
char *Strncpy (char *str1,const char *STR2, size_t n);
int Strcasecmp (const char *s1, const char *s2);
char *Strchr(const char *s, int c);




int main()
{
	
	char str1[50]="abcdcdcs.srwtr", str2[50]="AbAAAA";
	char c='.';
	char  *x, *y ;
	 /* , *str3;
	 str3 ="dfdgfd";
	size_t size =4 ;

	
	 /* x = strcasecmp (str1 , str2);
	    y = strcasecmp (str1 , str2); */

	x = strchr(str1,  c);
	y = Strchr(str1,  c);
	printf (" %s  %s %d %d\n",str1,str2, x, y);
	
	

	return 0;
}


 /* the founctoin copies the second string to the first string */
 /*	and return thr adress of the first string                 */
char *Strcpy(char *str1,const char *STR2)
{
	int i=0;
	
	for (i=0; *(STR2+i) != '\0' ; i++)
	{
		*(str1+i) = *(STR2+i);
	}
	*(str1+(i+1)) = *(STR2+(i+1));
	
return str1;
}

char *Strncpy (char *str1,const char *STR2, size_t n)
{	
	int i=0;
	for (i=0; i<n ; i++)
	{	
		if ( *(STR2+i) == '\0' )
		{
			*(str1+i)='\0';			
		}
		*(str1+i) = *(STR2+i);
			
		}
	return str1;
}



int Strcasecmp (const char *s1, const char *s2) /*  compair two string evoid of a upper case*/
{
	char temp1=' ' , temp2=' ' ;
	int i=0 , value_re=0 ;

	for (i=0 ; *(s1+i)!='\0' && *(s2+i) !='\0' && value_re ==0; i++)
	{	
		temp1 = *(s1+i);
		temp2 = *(s2+i);
		if (*s1 <=90 && *s1 >= 65 )	/* chenge to a lower case of s1*/
		{
			temp1 = *(s1+32);
		}	
		if (*s2 <=90 && *s2 >= 65 )	/* chenge to a lower case s2*/
		{
			temp2= *(s1+32);
		}	
		value_re= temp1- temp2;
	}

	value_re=*(s1+i)-*(s2+i);
return value_re;

}

char *Strchr(const char *s, int c)

{
		while (*s != '\0' && *s != c)
		{	
			s++;
		}

return s;
}

