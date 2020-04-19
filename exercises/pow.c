
		/****************************************************
		*													*
		*	The program get a integer number from the user  *
		*	and print ten power the number (10^number)		*
		*													*
		****************************************************/
#include<stdio.h> 
double TenPow();	/* the functoin get a integr number and return ten power the number */
int main()		/* in the main we get the number from the user and print thr result*/
{
	int num=0;

	printf ("entar a number");
	scanf ("%d",&num);
	printf ("%f",TenPow(num));
	

	return 0;
}

/* the functoin get a integr number and return ten power the number */
double TenPow(int num)
{
	int counter=1;
	double temp=1;
	
	if (num>0)
	{		
		for (counter=1 ; counter<=num ; counter++)
		{
			temp=temp*10;
		}
	}
	
	if (num<0)
	{
		num = (-1) * num;
		for (counter=1 ; counter<=num ; counter++)
		{
			temp=temp*10;
		}
		temp=1/temp;	
	}

return temp;
}	
