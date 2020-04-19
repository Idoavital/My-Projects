#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <sys/types.h> /*pit_t */
#include <signal.h> /* signal */
#include <string.h>
#include <stdio.h> /*printf */

typedef void  signfuc (int );


static void pong (int pid_parent);
static void ping (int pid_child);
static void saInit (struct sigaction *sa ,signfuc fun);

static pid_t parent_id , child_id ;

int main(int argc, char *argv[])
{
    struct sigaction child , parent;

    saInit (&child ,ping);
    saInit (&parent ,pong);

    sigaction(SIGUSR1, &child, NULL);
    sigaction(SIGUSR2, &parent, NULL);

    parent_id = getpid();
    child_id = fork();

    if (child_id == 0)
    {
        printf("i am a child --parent id %d\n ", (int)parent_id);
        while(1)
        {
        }
    }
    else
    {
        printf("i am a parent --child id %d\n",(int)child_id);
        kill (child_id ,SIGUSR1 );
        while(1)
        {
        }
    }

    return 0;
}


void pong (int pid_parent)
{
    printf("\npong\n");
    /* send signal to child */
    kill(child_id , SIGUSR1);
    sleep(1);
}

void ping (int pid_child)
{
    printf("\nping\n");
     /* send signal to child */
    kill(parent_id , SIGUSR2);
}

void saInit (struct sigaction *sa ,signfuc fun)
{
    memset (sa, 0, sizeof(struct sigaction));
    sa->sa_handler = fun;
    sigemptyset(&sa->sa_mask);
}
