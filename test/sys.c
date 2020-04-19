#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( )
{
 int return_value ;
 char str[256];

 do
   {
       printf ("enter a command ");
       fgets(str , 200, stdin);
       return_value = system (str );

   }
    while (0 != strcmp(str,"q/n"));
    return return_value;
}
