#include <stdio.h>


int last (int *arr,int flag , int size); /* functoin  that return the last live man */


int main (int argc, char * argv[] )
{
	int arr[100] = {0};
	int x = last ( arr, 1 ,100);
	printf ("num %d ", x);


	return 0;
}



/*
	arr - the pointer of a soldier array
	flag - for to sign if the first soldier is a live or dead (1 - live) 
	size - the aize of the array
	
*/

int last (int *arr,int flag , int size)  /*flag -   */
{
		int i=0; 	/* index for a loop*/
		static int victory =0 ;   /* variable to remember the last place of the a live soldier*/
		static int stop = 0;		/* count the number of a killings	*/
		
		for (i= 0; i < (size) && stop < size-1 ; i++)
		{
			if (flag == 0 && arr[i] == 0 ) /* if the soilder is a live and should die  */
			{
				arr[i] = 1 ;  	 /*sign a 1 if the soilder is killed*/
				flag =1;
				stop++;
				if (stop == size-1)
				return victory+1;  		/*return the last time */
			}

			else if (arr[i] == 0 && flag == 1 )  /* if the soilder is a live and should die  */
			{		
				 
				flag =0;
				victory = i;
			}
			
		}

		victory = last (arr, flag ,size) ;

return victory;
}
