# include <stdio.h>
# include <stdlib.h>

static char lut_char[255];

void updateLut(char arr[] ,int size_arr ,int max);

void print2Char(char arr1[] , int size_arr1 , char arr2[],int size_arr2, char arr3[],int size_arr3);

int main (int argc, char *argv[])
{
	char arr1[40] = "1223300<<";
	char arr2[40] = "234325hjdd<<dss";
	char arr3[40] = "355555jdddss";


	print2Char( arr1 , 40, arr2 , 40 ,arr3 , 40);
	return 0;
}

void print2Char(char arr1[] ,int size_arr1 , char arr2[],int size_arr2, char arr3[],int size_arr3)
{
	int temp_value = 0;
	int i = 0;
	
	updateLut(arr1 ,size_arr1, 1);
	updateLut(arr2 ,size_arr2, 2);

	for (i = 0; i < size_arr3 ; i += 1)  /* check if there is a char that apper in the 2 array before*/
	{
		temp_value = arr3[i];
		if (lut_char[temp_value] == 2)
			{
				lut_char[temp_value] = 0 ;
			}	
	}

	for (i = 0; i < 256; i += 1)
	{	
		if (lut_char[i] == 2)
		{
			printf ("%c\n",(char)i);
		}
	}
			
}

	/* up date the LUT char*/
void updateLut(char arr[] ,int size_arr ,int max)
{
	int temp = 0 ;
	int i = 0;
	for (i = 0; i < size_arr ; i += 1)
	{
		temp = arr[i];
		if (lut_char[temp] != max)
		{
			lut_char[temp]++;
		}
	}
}

