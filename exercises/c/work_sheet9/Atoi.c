#include <stdio.h>
#include <string.h> /* strrev strcat */
#include <stdlib.h>

/* convert string to int */
int Atoi(char * str);

/*	 convert int to string  */
char  *Itoa ( int num ,char * buffer, int bace);

char *strrev(char *str);

int main (int argc, char *argv[])
{
	char  str [33] ;
	int x = 0;	

    printf ("*******************test Atoi************************\n");
	x = Atoi ("3456");
	printf (" itoa 3456 :%d\n",x);

	x = Atoi ("0");
	printf (" itoa 0 :%d\n",x);

	x = Atoi ("18000");
	printf (" itoa 18000 :%d\n",x);

	printf ("\n*******************test Itoa************************\n");

	Itoa (9999, str , 10);
	printf ("int to string 12345 base 10: %s\n",str);

	Itoa (123456789 , str , 2);
	printf ("int to string 12345 base 2: %s\n",str);

	Itoa (123456789 , str , 16);
	

	printf ("int to string base 16: %s\n",str);
	return 0;
}
/************************************************************/

/* convert from chsr * to int */
int Atoi(char * str)
{
	int ret =0;
	int i = 0;
	
	for (i= 0 ;str[i] != '\0' ; i++)
	{
		ret *= 10;		/* move digits to place the str digit in her place*/
		ret += (int)str[i]-'0'; /* convert from ascii */
	}
	
	return ret;
}

 /* convert string from int */
char  *Itoa ( int num ,char * buffer, int bace)
{	
	int i =0 ;
	int temp = num;

	if(num == 0)
		buffer[0] = '0';
	{
		for ( i =0 ; temp != 0; i++)
		{
			printf("\n  remandier: %d \n", (int)temp%temp%bace);
			buffer[i] = temp%bace > 9 ? (temp%bace - 10 + 'a' ) : (temp%bace + '0')  ;
			temp/= bace;
			
		}
	}
	buffer[i] = '\0' ;
	strrev (buffer);

return buffer;
}

char* strrev (char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
	return str;
}
