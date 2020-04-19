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
#include "scheduler.h"
#include "task.h"


#define SEM_PERM 0600  /*semaphore permmision*/
#define SEM_NAME "/mysema" /*semaphor global name */
enum load {LOAD_FROM_APP , LOAD_FROM_WD };


static struct WD
{
     SCHED_T *wd_sc;  /* scheduler */
     char **argv_w;  /* pointer to the argv */
     pid_t watch_pid; /* the id of the processes of need to watch on*/
     TASK_T *task_send_signal;  /*task for send signal*/
     TASK_T *task_check_status;
     int flag_load_from ; /* flag for recognize how load to app */
     int flag_stop_sched ;
     char watch_path[BUFSIZ]; /*the path of the app that need to watch on*/
     sem_t  *sem_barrier;
     pthread_t sched_trhead; /* thread to run the schedular */
     struct sigaction act_usr1; /*struct hendler for SIGUSR1 */
     struct sigaction act_usr2; /*struct hendler for SIGUSR1 */



}wd;

volatile int alive_flag ;/*if set to 1 - the processes is alive*/


/************************************************************************/
/*static void ifLoadFromConsole ();*/

static void setWatchPidandExec();  /* set the vaiable of wd.watch_pid */
/* hendler functoin for SIGUSR1 */
static void sigusrHdl(int sig, siginfo_t *siginfo, void *old_siginfo);

static int sigInit(); /*init and registers hendler*/

/*set the env variable only for the first time the app is load */
static void setFirstTimeEnv();

static const char *GetFullPath(void);

/**************** scedular functions and task****************************/

static void AddTasks();    /*add tasks to scheduler*/

/*the functoin send signal to the wd.watch_pid */
static void sendSIgnal (SCHED_T *sc, TASK_T *task, void *param);
/* check the status of the alive_flag
   and if the status is 0 call to functoin for restart the processes */
static void CheckAlive (SCHED_T *sc, TASK_T *task, void *param);
/* create scedduler add tasks and run*/
static void* runSched(void * param);

static void cleanUp();
/******************************************************************************/
int MMI(int argc ,char *argv[])
{

    wd.argv_w = argv;
      /* get env to check if is the app laoded from WD or from console */
    if(NULL == getenv("_MY_PARENT_NAME") ) /* if not exist , create a new one */
    {

        setFirstTimeEnv();
        setenv("_MY_PARENT_NAME", GetFullPath() ,0);
        wd.flag_load_from = LOAD_FROM_APP;
    }
    else
    {
        /*save the parent path*/
        strcpy(wd.watch_path , getenv("_MY_PARENT_NAME"));
        /*set the new path for the sun */
        setenv("_MY_PARENT_NAME", GetFullPath() ,0);

        wd.flag_load_from = LOAD_FROM_WD;
    }

    wd.sem_barrier = sem_open(SEM_NAME, O_CREAT, SEM_PERM, 0);
    if(wd.sem_barrier == SEM_FAILED)
    {
        perror("ERROR creating thread.");
        return -1;
    }
    /* register signal SIGUSR1  and init sigaction struct*/
    sigInit();

    /*fork exec for the new WD process*/
    setWatchPidandExec();

    if (wd.flag_load_from == LOAD_FROM_APP)
            sem_wait(wd.sem_barrier); /* wait for the child to upload */
    else
            sem_post(wd.sem_barrier); /* post to parent */

    /*create new thread for run the scheduler tasks */
    if (0 != pthread_create(&wd.sched_trhead,NULL,runSched, NULL))
        {
            perror("parent pthread_create");
            return -1;
        }
    return 0;
}

/* The process will not be restarted after termination */
void DNR(void)
{
    /*if i watch dog*/
    if (0 == strcmp(GetFullPath(),"/home/stav/svn/Proj/arch/linux64/bin/Debug/wd.out" ))
    {
        pthread_join(wd.sched_trhead,NULL);
        kill(wd.watch_pid,SIGUSR2);
    }
    /*if i app*/
    else
    {
        kill(wd.watch_pid,SIGUSR2);
        pthread_join(wd.sched_trhead,NULL);
    }

}


/*************************** scheduler functoin ***************************************************/


static void AddTasks()
{
    wd.task_send_signal  = SchedAddTask (wd.wd_sc, sendSIgnal ,NULL, 1); /* send signal evrey 1 sec */
    wd.task_check_status = SchedAddTask (wd.wd_sc, CheckAlive , NULL, 4); /*check if alive evry 4 sec*/
}

static void* runSched(void * param )
{
    wd.wd_sc = SchedCreate ();
	if (NULL == wd.wd_sc )
	{
		printf ("\nfailed to create \n");
		return NULL;
	}

    AddTasks();
    SchedRun(wd.wd_sc);
    SchedDestory(wd.wd_sc);

    return NULL;
}


/***************************** task functoin *************************************************/

static void CheckAlive (SCHED_T *sc, TASK_T *task, void *param)
{
    if (wd.flag_stop_sched )/* check if get signal USR2*/
    {
        SchedStop(wd.wd_sc);
    }
    else
    {
        if (alive_flag)
        {
            alive_flag = 0; /*reset the flag */
        }
            else
        {
            /* call the exec function
            and set new watch pid   */
            wd.flag_load_from = LOAD_FROM_APP;
            setWatchPidandExec();
            sem_wait(wd.sem_barrier);

        }
    }


}

static void sendSIgnal (SCHED_T *sc, TASK_T *task, void *param)
{
    if (wd.flag_stop_sched )/* check if get signal USR2*/
    {
        cleanUp();
    }
    else
    {
#ifdef DEBUG
    fprintf(stderr, "sending PING from pid %d\n", getpid());
#endif
    kill (wd.watch_pid, SIGUSR1);
    }


}

static void cleanUp()
{
    SchedStop(wd.wd_sc);
    sem_close(wd.sem_barrier);
}

/*********************************** signal functoins *******************************************/

static void sigusrHdl(int sig, siginfo_t *siginfo, void *old_siginfo)
{
    alive_flag = 1;
#ifdef DEBUG
    printf("get signal %d\n",getpid() );
#endif

}

static void sigusr2Hdl(int sig, siginfo_t *siginfo, void *old_siginfo)
{
    wd.flag_stop_sched = 1;
}

static int sigInit()
{
    /* Use the sa_sigaction field because the handles has two additional parameters */
    wd.act_usr1.sa_sigaction = &sigusrHdl;
    wd.act_usr2.sa_sigaction = &sigusr2Hdl;

    sigemptyset(&wd.act_usr1.sa_mask);
    sigemptyset(&wd.act_usr2.sa_mask);
    /* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
	wd.act_usr1.sa_flags = SA_SIGINFO;
	wd.act_usr2.sa_flags = SA_SIGINFO;
    /* register SIGUR1 */
	 if ( sigaction (SIGUSR1, &wd.act_usr1 , NULL) < 0)
     {
		perror ("sigaction");
		return -1;
	}
	/* register SIGUR2 */
	if ( sigaction (SIGUSR2, &wd.act_usr2 , NULL) < 0)
     {
		perror ("sigaction");
		return -1;
	}

return  0;
}
/************************************************************************************************/
/* set the vaiable of wd.watch_pid */
static void setWatchPidandExec()
{
    /* if load from console - create a new WD */
    if (wd.flag_load_from == LOAD_FROM_APP)
    {
        wd.watch_pid = fork();
        /*replaces the current process image with a new process
          with the pid of the parent*/
        if (0 == wd.watch_pid)
        {
            printf("exe %s", wd.watch_path);
            if (-1 == execv(wd.watch_path , wd.argv_w ))
            {
                perror("execlp() failed\n");
            }
        }
    }
    else
    {
        wd.watch_pid = getppid();
    }
    alive_flag = 1;
}
/***********************************************************************/

static void setFirstTimeEnv()
{
    strcpy(wd.watch_path,"/home/stav/svn/Proj/arch/linux64/bin/Debug/wd.out");
}

/******************  GetFullPath functoin ***********************/
static const char *GetFullPath(void)
{
	size_t length = 0;
	static char fullpath[BUFSIZ];

	length = readlink("/proc/self/exe", fullpath, sizeof(fullpath));

	/* Catch some errors: */
	if (length < 0)
    {
        fprintf(stderr, "Error resolving symlink /proc/self/exe.\n");
        return NULL;
	}
	if (length >= BUFSIZ)
	{
        fprintf(stderr, "Path too long. Truncated.\n");
        return NULL;
	}

	/* I don't know why, but the string this readlink() function
	* returns is appended with a '@'.
	*/
	fullpath[length] = '\0';       /* Strip '@' off the end. */

	return fullpath;
}

