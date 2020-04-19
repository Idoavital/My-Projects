#include <stdio.h>
#include <inttypes.h>

void boom(int start, int end);
void swap(int** pi1, int ** pi2);

int main(int argc ,char * argv[])
{
	
	int i =7 , j =3;
	int *po1 = &i;
	int *po2 = &j;

	  

	printf("------swap-------\n");
	printf("BFORE po1 %p po2 %p\n",(void*)po1, (void*)po2);
	swap (&po1, &po2);
	printf("after  po1 %p po2 %p\n",(void*)po1, (void*)po2);

	return 0;
}


/*7 BOOM - the finctoin print all the number in the range and replace 
	the number that divid in 7 with no reminder in the word BOOM
 */
void boom(int start, int end)
{
	int i = 0;
	int flag = 0;
	
	
	while (start <= end )  
	{
		if (start %7 ==0)  /*replace a number divide 7  */
			{
			printf("BOOM") ;
			start++;
			flag =0;
			}

		for( i=start ; i>0 ; i = i/ 10 ) 		/*	*/
		{
				if (i%10 == 7 )	
				{
				printf("BOOM") ;	
				start++; 
				flag =1 ;
				break;
				}
			 
		}

		if ( flag == 0) 
		{
			printf(",%d ",start);
			start++;
		}
		flag = 0;
	}
}

void swap(int** pi1, int ** pi2)
{
	int *help = *pi1;
		*pi1 = *pi2 ;
		*pi2 = help ;

}






