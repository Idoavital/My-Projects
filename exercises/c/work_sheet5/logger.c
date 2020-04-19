#include <stdio.h>  

#include <string.h> /*use strcmpr  */

#define MAX_BUFFER 100
enum {CMDNUMBER = 5}; /* number of system command  */

typedef enum  {FALSE , TRUE} BOOL;

struct Command
{	
	char * name;
	int  (*compare)(const char*,const char*); 	
	BOOL (*operate)( char*,const char*) ;
};

/* compare the string user to table command */
static int compareCmd(const char*,  char*); 

/* compare the first char of user string to '<' */
static int cmpFirst (const char* ,const char *) ;

/* the function delete the text file of the user*/
static BOOL RmFile(char *  ,const char * );

/*count the number of the line in the text file */
static BOOL count (char * ,const char * );

/*exit from the program */
static BOOL DoExit(char *  ,const char * );

/*add the string user to the begi of the text */
static BOOL WriteToBegin (char *  ,const char * );

/*Doing nothing  */
static int myDefaultCmp(const char*  , const char * );

/*add line to file*/
static BOOL writeLine(char *  ,const char * );



struct Command action[]  =	 /*build array of Command */
{	
	{"-remove\n", strcmp, RmFile },	
	{"-count\n", strcmp, count },
	{"-exit\n", strcmp, DoExit },
	{"<(oneChar)", cmpFirst, WriteToBegin }, 
	{"-defualt", myDefaultCmp , writeLine}
} ;


/*********************************************************************************/

int main (int argc, char* argv[])
{

	int stop = 1; 		   /*	decide when to stop get strings from the user*/
	char newLine[MAX_BUFFER] ;    /* this wiil be the string that the user enter*/
	FILE *pstr ;		  /*file pointer fo the new text file	*/
	char name [30] ;

	if (argv[1] == NULL)		/* check if the user didn't enter a name for a file */ 
	{
		printf ("you have to enter a name for the file\n");
		return 1;
	}
	strcpy(name , argv[1]);

	pstr = fopen (name, "w+");  /*open a new file  */

	if (pstr == NULL)	
	{
		printf (" Failed opening file line %d", __LINE__);
		return 1;
	}

	printf ("Enter a string \n");
	
	while (stop)  /* get a strings and command from the user  */
	{
		

		fgets(newLine , MAX_BUFFER , stdin);
	
		stop = compareCmd(newLine, name);
	
	 }
	
	if (fclose (pstr) == EOF)	/* check if file closed */
			{
				printf (" Failed closing file line %d \n", __LINE__);
				return 1;
			}

	

return 0;
	
}
/*********************************************************************************/

static int myDefaultCmp( const char*  cmdName, const char * userCmd)
{
		
		return 0;
}

/**********************************************************************************/


BOOL writeLine(char * fileName ,const char * userCmd)
{

	
	FILE *file = fopen (fileName,"a+" );
	 if (file == NULL)	
			{
				printf (" Failed opening file line %d \n", __LINE__);
				return 1;
			} 
	

		fputs (userCmd , file);
		if (fclose (file) == EOF)	/* check if file closed */
			{
				printf (" Failed closing file line %d \n", __LINE__);
				return 1;
			}


	return TRUE;
}
/*************************************************************************************************************/


static int compareCmd (const char*  userCmd,  char * name_of_file)  /* compare and act the user command */
{

		int equal = 0 ;
		int i =0 ;
		int ret = 0; /* if the action[i].aoperate been done returned 1 */
		
		for (; i < CMDNUMBER ; i++)
		{
				
			equal = (int) action[i].compare(action[i].name , userCmd);
			if (0 == equal )
				{
					
					ret = action[i].operate(name_of_file ,userCmd );
					break ;
				}
		}
		
	return ret;
}
/*********************************************************************************/
static int cmpFirst (const char*  cmdName, const char * userCmd) /* compare the first char of the user string */
{
	int ret = 1 ;

	if (*userCmd == '<')
		{
			ret = 0;
		}
	
	
	return ret;
}
/*********************************************************************************/

static BOOL RmFile(char * fileName ,const char * userCmd) /* delete the file*/
{	
	BOOL ret = 1;	
	if (-1 == remove(fileName))
	{
		printf("failed to remove file \n");
	}	
	else 
		printf (" file been remove \n");

	return ret;
}

/*********************************************************************************/
static BOOL count(char * fileName ,const char * userCmd) /* count the number of lines in the file */


{	
	FILE * filePointer;   /*pointer for open the file  */
	BOOL ret = 1;
	int line_sum = 0; 	/* variable fo count the lines in the file*/
	filePointer = fopen (fileName,"r" );
	 if (filePointer == NULL)	
			{
				printf (" Failed opening file line %d", __LINE__);
				return 1;
			} 
	
	while ( feof (filePointer) != 1)
	{

		if ('\n' == fgetc (filePointer))
		{			
			line_sum++;
		}
	}
	
	fclose(filePointer);
	printf ("the number of line %d \n", line_sum) ;

	return ret;
}


/*********************************************************************************/
static BOOL DoExit(char * fileName ,const char * userCmd)
{

	BOOL ret = 0;
	printf (" exit from the program\n") ;
	
	return ret;
}
/*********************************************************************************/

static BOOL WriteToBegin (char * name_of_file ,const char * userCmd)
{
	
	BOOL ret = 1;
	FILE * pstr;
	FILE * temp_pstr;
	char str[MAX_BUFFER];

	pstr = fopen(name_of_file, "r+");
			if (pstr == NULL)	/* check if file opend */
			{
				printf (" Failed opening file");
				return 1;
			}
	
	temp_pstr = fopen("TEMP", "w+");
			if (pstr == NULL)	/* check if file opend */
			{
				printf (" Failed opening file line %d \n", __LINE__);
				return 1;
			}

		
	fputs(userCmd+1, temp_pstr); /* copy the string user to the begin of a temp file */
	

	while (fgets(str, MAX_BUFFER, pstr))  /*copy the old file to a new file */
	{
			fputs (str, temp_pstr);
	}

	fflush(temp_pstr);
	fseek ( pstr, 0, SEEK_SET );
	fseek ( temp_pstr, 0, SEEK_SET );

	
	while (fgets(str,MAX_BUFFER, temp_pstr)) /* copy back the temp file to the old file*/
	{
			fputs (str,pstr);
	}

	
	
	
	if (fclose (pstr) == EOF)	/* check if file closed */
			{
				printf (" Failed closing file line %d \n", __LINE__);
				return 1;
			}

	
	if (fclose (temp_pstr) == EOF)	/* check if file closed */
			{
				printf (" Failed closing file line %d \n", __LINE__);
				return 1;
			}

	return ret;
}


















