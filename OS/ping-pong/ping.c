#define _POSIX_C_SOURCE 199309L
#include <unistd.h>     /* */
#include <stdlib.h>
#include <sys/types.h> /*pit_t */
#include <signal.h> /* signal */
#include <string.h> /*atoi */
#include <stdio.h> /*printf */



static void hdl (int sig, siginfo_t *siginfo, void *context);
volatile int flag = 0;
static pid_t p_id ;


int main(int argc, char *argv[])
{
    struct sigaction act;

    memset (&act, '\0', sizeof(act));

    act.sa_sigaction = &hdl;
    /* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
	act.sa_flags = SA_SIGINFO;

	sigemptyset(&act.sa_mask);

	if (sigaction(SIGUSR1, &act, NULL) < 0)
    {
		perror ("sigaction");
		return 1;
	}

	if (argc < 2)
    {
        printf("my id is %d \n",(int)getpid());

        while(flag == 0)
        {
        }
        printf("get signal\n");
        sleep(1);

    }

    else
    {
         p_id = atoi(argv[1]);
         kill(atoi(argv[1]) , SIGUSR1);

    }


	while(1)
    {

      if (flag == 1)
      {
         flag = 0;
         kill(p_id , SIGUSR1);
         printf("send signal to %d\n",(p_id));
         while(sleep(2));
      }


    }

    return 0;
}


static void hdl (int sig, siginfo_t *siginfo, void *context)
{
    p_id = siginfo->si_pid;
	flag = 1 ;

}


