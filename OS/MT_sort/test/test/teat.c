
#define _POSIX_C_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void handler (int sig, siginfo_t *siginfo, void *context)
{
    printf(">>>>>>\n");
	printf ("Sending PID: %ld, UID: %ld\n",
			(long)siginfo->si_pid, (long)siginfo->si_uid);
}

int main (int argc , char *argv[])
{
	int i =3 ;
	struct sigaction act;
    memset (&act, '\0', sizeof(act));
	/* Use the sa_sigaction field because the handles has two additional parameters */
	act.sa_sigaction = &handler;
	/* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
	act.sa_flags = SIG_IGN;

	while (1)
	{

	if (sigaction(SIGINT, &act, NULL) < 0)
	    {
		perror ("sigaction");
		return 1;
		}
		printf ("%d \n",i++);
		sleep(1);
	}
}
