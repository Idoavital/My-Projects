# include<stdio.h>

void Hello();

int main()
{
	Hello(); 	/* the functoin write "hello world" */
	return 0;
}
		
 void Hello() 
{
	int world[]={0x48,0x65,0x6c,0x6c,0x6f,0x20,0x57,0x6f,0x72,0x6c,0x6c,0x64,0x21}; 
	for (int i = 0; i < 12; i++)
		printf("%c", world[i]);
	printf("\n");
	
} 
