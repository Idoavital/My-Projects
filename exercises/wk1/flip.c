#include <stdio.h>

int main ()
{
	int num=0;
	scanf("%d",&num);
	Flip (num);
	return 0;
}
/* the functoin get number and print the number flip   */
void Flip (int reminder)
{
	int index=0;		
	do 					/*the loop print the last digt and delet the last digt from the number */
	{
		printf ("%d",remainder %10); /*print the last digt of the number*/
		remainder= remainder/10;		
	}
	while (remainder>1); 			/*the loop end when after the last digt of the number print*/
}
