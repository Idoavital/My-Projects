#define _BSD_SOURCE

#define _POSIX_C_SOURCE 199309L /*sig info*/

#include <unistd.h> /*  exec */
#include <stdlib.h>     /*  */
#include <sys/types.h> /* pit_t sem_t*/
#include <signal.h> /* signal */
#include <string.h> /* atoi */
#include <stdio.h> /* printf */
#include <semaphore.h> /* semopen() semwait() sempost()*/
#include <pthread.h> /* pthreade create */
#include <fcntl.h> /* O_CREAT */


#include "wlib.h"


/******************************************************************************/
int main(int argc,char * argv[])
{

    printf("WD START\n");
    MMI(argc , argv);

    DNR();


    return 0;
}

