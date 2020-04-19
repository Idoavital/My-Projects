
#include <stdio.h>
#include <stddef.h>

#define IS_ENDIAN (1& *(short)"10"))

void chevkEndian();
int main (int argc, char *argv[])
{
	

	int x = 1;

	chevkEndian();
	printf (" %d ",*(char*)&x);
	return 0;
}

void chevkEndian()
{
	int x =1;

	if ((*(char*)&x) == 1)
		printf("is littel endian \n");
	else
		printf("is big endian \n");

}
