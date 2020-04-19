#include <stdio.h>
#include <string.h>
#include "circBuffer.h"

void createTest (CIRC_B * circle);
void testcBufWrite (CIRC_B * circle);



int main (int argc, char *argv[])
{
	CIRC_B * circle  = cBufCreate(15);
	
	 testcBufWrite (circle);
	cBufDestroy(circle)	;
	
	return 0;
}

void createTest (CIRC_B * circle)
{

	 circle = cBufCreate(15);
}


void testcBufWrite (CIRC_B * circle)
{
	char moshe[6] = "moshe";
	char buf[15] ;
	
	
	printf("*----------- write test check free space ------------------------*\n");
	printf ("free space = %lu \n", cBufFreeSpace(circle)  );
	
	
	cBufWrite(circle, moshe,4);
	if (cBufFreeSpace(circle)==11)
	{
		printf ( "write succses, write 4 free space = %lu\n ", cBufFreeSpace(circle) );
	}
	else
	{
		printf ( " write faild \n" );
	}
	
	
	cBufWrite(circle, moshe,4);
	if (cBufFreeSpace(circle)==7)
	{
		printf ( "write succses, write 4 free space = %lu\n ", cBufFreeSpace(circle) );
	}
	else
	{
		printf ( " write faild \n" );
	}
	
	
	cBufWrite(circle, moshe,6);
	if (cBufFreeSpace(circle)==1)
	{
		printf ( "write succses ,write 6 free space = %lu \n", cBufFreeSpace(circle) );
	}
	else
	{
		printf ( " write faild \n" );
	}
	
	cBufWrite(circle, moshe,6);
	if (cBufFreeSpace(circle)==0)
	{
		printf ( "write succses, write 6 free space = %lu \n\n\n", cBufFreeSpace(circle) );
	}
	else
	{
		printf ( " write faild \n" );
	}
	
	
	cBufRead (circle, buf , 10 );
	printf ("after: %s \n", buf);
	printf ( "free space = %lu \n", cBufFreeSpace(circle) );
	
	
	cBufWrite(circle, moshe,5);
	 
	
		printf ( "write succses, write 5 free space = %lu \n\n\n", cBufFreeSpace(circle) );
	
	
	
	
	cBufRead (circle, buf , 15 );
	printf ("after: %s \n", buf);
	printf ( "free space = %lu \n", cBufFreeSpace(circle) );
		
	cBufRead (circle, buf , 15 );
	printf ("after: %s \n", buf);
	printf ( "free space = %lu \n", cBufFreeSpace(circle) );		
		
}


