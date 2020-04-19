#include <time.h> /* include */
#include <stdio.h>

#include "scheduler.h"
#include "ShareStackSched.h"
#include "task.h"


typedef struct person
{
	char name[10] ;
	char family[10] ;
	int age;
}
PERSON;

PERSON rd38[] = {
{"ido","abitbul",35},
{"moshe","vaknin",28},
{"evgeni","yaltzin",34},
{"dani","borsthin",2},
{"guy","frid",26},
{"maayan","daniel",24},
{"beni","bonbon",32},
{"eli","theSmart",29},
};

TASK_T *task_1;
TASK_T *task_2;
TASK_T *task_3;
TASK_T *task_stop;

static SCHED_T *sc;

static FILE *fptr;

void testCreate ();

void testAddTask ();

void testRemoveTAsk ();


void printRd38first (SCHED_T *sc, TASK_T *task, void *param);
void printRd38Seconde (SCHED_T *sc, TASK_T *task, void *param);
void printRd38Three (SCHED_T *sc, TASK_T *task, void *param);
void StopShced (SCHED_T *sc, TASK_T *task, void *param);

static int rm_task_1 = 0;

int main (int argc, char *argv[])
{



   fptr = fopen("schudalrTest.txt","w");

   if(fptr == NULL)
   {
      printf("Error!");
      return 1;
   }

    rm_task_1 = 0;
    testCreate();
	testAddTask ();
	SchedRun (sc);

	fclose ( fptr);


	SchedDestory (sc);

	return 0;
}

void testCreate ()
{
	sc = SchedCreate ();
	if (NULL == sc )
	{
		printf ("\nfailed to create \n");
	}
	else
	{
		printf ("\nsuccess to create \n");
	}
}
void testAddTask ()
{
	time_t interval_1 = 2 ;
	time_t interval_2 = 4 ;
	time_t interval_3 = 6 ;
	time_t interval_stop = 20 ;
	void *param = (void*) 1;


    task_1 = SchedAddTask (sc, printRd38first ,param, interval_1);
	task_2 =SchedAddTask (sc, printRd38Seconde , param, interval_2);
	task_3 =SchedAddTask (sc, printRd38Three , param, interval_3);
	task_stop =SchedAddTask (sc, StopShced , param, interval_stop);




}

void testRemoveTAsk ()
{
	fprintf (fptr," remove the second member");

	SchedRemoveTask ( sc, task_2);
}

void printRd38first (SCHED_T *sc, TASK_T *task, void *param)
{
	static int chenge =0;

	time_t cur_time;
    time(&cur_time);

    /* printf ("Current time = %s", ctime(&cur_time)); */

	fprintf(fptr," the first member  %d  %s  %s\n",rd38[0].age, rd38[0].name , rd38[0].family );
	fprintf(fptr," the first time   %s\n\n",  ctime(&cur_time)) ;

	printf ("print evrey %lu : \n", TaskGetInterval (task_1));
	if (chenge == 2)
	{
		printf (" chenge task 1 interval to 1 sec\n");
		SchedTSetInterval (task_1 , 1);
	}
	chenge++;
	fprintf (fptr ,"internal task_1 = %lu  \n", TaskGetInterval (task_1));
	fflush (fptr);

	printf(" the first member  %d  %s  %s\n",rd38[0].age, rd38[0].name , rd38[0].family );
	printf(" the first time   %s\n\n",  ctime(&cur_time)) ;


}

void printRd38Seconde (SCHED_T *sc, TASK_T *task, void *param)
{

	time_t cur_time;
    time(&cur_time);

    rm_task_1++;

	fprintf(fptr,"\n the second member  %d  %s  %s\n",rd38[1].age, rd38[1].name , rd38[1].family );
	fprintf(fptr," the second time   %s\n\n",  ctime(&cur_time) );
	printf ("print evrey %lu : \n", TaskGetInterval (task_2));
	if (3 == rm_task_1) /* remove task 1 when rm_task is 3*/
	{
		printf (" remove task 1");
		SchedRemoveTask (sc , task_1);
	}

	printf(" the second member  %d  %s  %s\n",rd38[1].age, rd38[1].name , rd38[1].family );
	printf(" the second time   %s\n\n",  ctime(&cur_time) );


	fflush (fptr);

}

void printRd38Three (SCHED_T *sc, TASK_T *task, void *param)
{
	static int stop =0;
	time_t cur_time;
    time(&cur_time);


	fprintf(fptr," the third member  %d  %s  %s\n",rd38[2].age, rd38[2].name , rd38[2].family );
	fprintf(fptr," the third time   %s\n\n",  ctime(&cur_time) );
	fflush (fptr);

	printf ("print evrey %lu : \n", TaskGetInterval (task_3));
	printf(" the third member  %d  %s  %s\n",rd38[2].age, rd38[2].name , rd38[2].family );
	printf(" the third time   %s\n\n",  ctime(&cur_time) );


	if (4 == stop)
	{
		SchedStop (sc);
	}
	stop++;
}

void StopShced (SCHED_T *sc, TASK_T *task, void *param)
{
	fprintf (fptr ,"stop the play");
	printf ("stop the play \n");
	SchedStop (sc);
}



