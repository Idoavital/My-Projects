#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strncpy , strtok */
#include <stddef.h> /* offset */

#define  FAIL  1
#define MAXBUFER 512 /* size of string*/

/* #define CHECK_CLOSE(file) 0 == file ?  file = NULL : fprintf\
	(stderr, " Failed closing file line %d \n", __LINE__)
	
 #define CHECK_OPEN(file) NULL == file ? fprintf(stderr, " Failed opening file line %d \n", __LINE__): 
*/

typedef struct classMember
{
	char first_name[15];
	char last_name[15];
	char celluar_number[11];
	int id_number;
	char gender;
} classInfo ;

static char buf [512] ; /* temp buf to use by functoin*/

/* the function get  array of struct print the array member  */
static void printArray( classInfo * class,int size);

/* the functoin count line of text */
static int countLine(char * fileName );

/* insert the data from the text to the struct array*/
static void insertData ( classInfo * class , int size , char * class_name);

/* print the offset  */
static void printOffset( classInfo * class,int size);



/*********************************************************************************/

int main (int argc, char *argv[])
{

	int number_of_lines = 0 ;
	classInfo * first_class ;
	

	number_of_lines = countLine ("class38");   /*check the size of the line for the size of the array*/
	
	first_class =  malloc (number_of_lines * sizeof(classInfo)); /* make array of classInfo*/

	insertData ( first_class , number_of_lines , "class38");
	
	printArray( first_class , number_of_lines);		/* print the array member*/

	printOffset( first_class , number_of_lines);
	return 0;
}


/******************************************************************************/

static int countLine(char * fileName ) /* count the number of lines in the file */

{	
	FILE * class_file;  	 /*pointer for open the file  */
	int line_sum = 0; 		/* variable fo count the lines in the file*/

	class_file = fopen (fileName,"r" );

	if (class_file == NULL)		/*check if the file opened*/
	{
		fprintf(stderr, " Failed opening file line %d \n", __LINE__);
		return FAIL ;
	}
	
	while ( feof (class_file) != 1)
	{

		if ('\n' == fgetc (class_file))			/*count the line evrey /n */
		{			
			line_sum++;
		}
	}
	
	if (fclose (class_file) == EOF)		/* check if the file is closed*/
	{
		fprintf (stderr, " Failed closing file line %d \n", __LINE__) ;
	}


	return line_sum;
}
/*********************************************************************************/

static void insertData ( classInfo * class , int size , char * class_name)
{
	FILE * class_file;
	int i = 0;
	char * tok_pi ;

	class_file = fopen (class_name, "r");
	if (class_file == NULL)		/*check if the file opened*/
	{
		fprintf(stderr, " Failed opening file line %d \n", __LINE__);
		return  ;
	}
	
	for (i= 0 ; i< size ; i++)
	{
		fgets(buf, MAXBUFER, class_file) ;

		tok_pi = strtok (buf ," 	");
		strncpy (class[i].first_name,tok_pi ,15);

		tok_pi = strtok (NULL ," 	");
		strncpy (class[i].last_name,tok_pi ,15);

		tok_pi = strtok (NULL , " 	");
		class[i].id_number = atoi(tok_pi);

		tok_pi = strtok (NULL , " 	");
		strncpy (class[i].celluar_number,tok_pi ,10);
		
	
		tok_pi = strtok (NULL , " 	");
		class[i].gender = *tok_pi;
	}

	if (fclose (class_file) == EOF) /* check if the file is closed*/
	{
		fprintf (stderr, " Failed closing file line %d \n", __LINE__) ;
	}

}
/*************************************************************/
static void printArray( classInfo * class,int size)
{
	int i = 0;
	for ( i= 0 ; i < size ; i ++)
	{
		printf ("first name: %s \n", class[i].first_name);
		printf ("last  name: %s \n", class[i].last_name);
		printf ("id number: %09d \n", class[i].id_number);
		printf ("celluar number: %s \n", class[i].celluar_number);		
		printf ("gender: %c \n", class[i].gender);
		printf ("\n ---------------------- \n");
	}
}


static void printOffset( classInfo * class,int size)
{
	printf ("  ** %d ** \n",((int) ((char*)class[1].first_name - (char*)class)));


	printf (" offset between classInfo - first_name  %lu ** \n", offsetof(classInfo  , first_name));
	printf (" offset between classInfo - last_name  %lu ** \n", offsetof(classInfo  , last_name));
	printf (" offset between classInfo - celluar_number  %lu ** \n ", offsetof(classInfo  , celluar_number));
	printf (" offset between classInfo - id_number  %lu ** \n ", offsetof(classInfo  , id_number));
	printf (" offset between classInfo - gender  %lu ** \n", offsetof(classInfo  , gender));


}




