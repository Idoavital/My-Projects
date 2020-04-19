

#include <stdio.h>
#include <unistd.h> /*sleep */

#include "wlib.h"

int main(int argc, char *argv[])
{
    int i = 3;
    printf("\nMAIN START \n");
    MMI( argc , argv);
    printf("main argv 2 of the first time %s  \n" ,argv[2] );
    while (i-- )
    {
        while(sleep(1));
       printf("main argv 2 %s\n" ,argv[2] );
       printf( "\nin the main app %d\n ",i);
    }


    printf("\n MAIN FINISH\n");
    return 0;
}
