# include <stdio.h>
#include <string.h>
#include <ctype.h>		/*for tolower function	*/
#include <stdlib.h>  /*for a malloc*/

int  numAndLower(char *str, char * envp);

int main(int argc,char *argv[], char *envp[])
{ 


	int i = 0  ,ptr_vector_size = 0 ,add_vector = 0 ;  /* i and j are index for loop,*/
	int total_string_len = 0; 		/*counter for the aize of the new array[][]	*/
	char ** new_env;   /*the new pointer */



	 for ( i =0 ; 0 != envp[i]; i++ )  /* loop for count the size of the envp array*/
	{
		total_string_len += (strlen(envp[i]) + 1);
	} 
	
	ptr_vector_size = (i+1) * sizeof(char*);

	new_env = (char**) malloc( ptr_vector_size + total_string_len); /*a new memory place for copy the envp array*/
	
	
	for (i=0 ; envp[i] != NULL ;i++ ) 
	{
	
	new_env[i] = (char*)(new_env + ptr_vector_size ) + add_vector ;
	
	add_vector = (add_vector+ numAndLower(new_env[i] ,envp[i]));
	
	}

		for ( i =0 ; 0 != envp[i]; i++ ) 
			printf ("%s \n",new_env[i] );



	free (new_env);

return 0;
}

int  numAndLower(char *str, char * envp)  /*functoin to  lower case and return a the length of the line*/
{
	
	int i= 0;
	
	for (i = 0 ;0 != envp[i]  ; i++)
	{
		str[i] = tolower(envp[i]);
		
	}
	str[i+1] = '\0';

return (i+1);
}




