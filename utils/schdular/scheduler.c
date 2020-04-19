#include <time.h> /* time , ctime */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* malloc*/
#include <assert.h> /* assert */

#include "pQueueHeap.h" /* PQUEUE type and finction */ /*real pQueue */
#include "ShareStackSched.h"
#include "task.h"
#include "scheduler.h"



typedef enum flag {RUN , STOP} GO;
struct Sched
{
	PQUEUE * pq;
	GO play  ;

};
/* the sort functoin  of scheduler */
int scIsBefore (const void *param1, const void *param2);

	/* the match funtion to find task in the list */
int IsMatch_t(const void *data1, const void *data2 ,  void *param);

/*******************************************************************************/
/* create scheduler struct */
SCHED_T* SchedCreate(void)
{
	SCHED_T * sc = NULL ;
	sc = (SCHED_T*) malloc (sizeof (SCHED_T));
	if (NULL == sc)
	{
		return NULL;
	}
	sc->pq = pQCreate ( scIsBefore );
	sc->play = RUN;
	return sc;
}

/* add a new task to scheduler */
TASK_T* SchedAddTask (SCHED_T *sc, TASK_FUNC_T func, void *param, time_t interval)
{
	TASK_T *new_task;
	new_task = TaskCreate (func, interval , param);
	if (NULL == new_task) /* check if create is success*/
	{
		return NULL;
	}

	if (pQEnqueue(sc->pq , new_task ))
		return NULL;

	return new_task;
}

/* removes a task from scheduler */
void SchedRemoveTask (SCHED_T *sc, TASK_T *task)
{
	assert (NULL != sc);

	pQErase (sc->pq , IsMatch_t , task, task->param);
}

/* runs the scheduler */
void SchedRun (SCHED_T *sc)
{
	TASK_T *de_task = NULL;
	time_t sleep_time = 0;
	time_t curr_time = time(NULL);

	assert (NULL != sc);

	de_task = pQDequeue(sc->pq);

	/* sort the list again to prevent mistiming in task addition */
	while ( TaskGetRelative(de_task) < curr_time)
	{
		TaskSetRelative (de_task, (curr_time + TaskGetInterval(de_task))) ;
		pQEnqueue(sc->pq , de_task ); /*Enqueue again the task with the relative time */

		de_task = pQDequeue(sc->pq);
	}

	pQEnqueue(sc->pq , de_task );


	while (sc->play == RUN && 0 == pQIsEmpty(sc->pq))
	{
		sleep_time = 0;

	    de_task = pQDequeue(sc->pq);

	    /* check if the current time is bigger then the time to run, in this case the sleep tim eis 0 */
   		if (TaskGetRelative(de_task)  >  time(NULL))
   		{
  	 		sleep_time = TaskGetRelative(de_task)  - time(NULL);
   			while (	sleep (sleep_time)); /* stop the runnig for the interval time of task */
   		}
   		TaskSetRelative (de_task,  time (NULL)  + TaskGetInterval(de_task)) ; /* set the new relative time */
   		pQEnqueue(sc->pq , de_task ); /*Enqueue again the task with the relative time */
   		TaskRun (sc , de_task ); /* run the last task */

	}
}

/* stops the scheduler */
void SchedStop (SCHED_T *sc)
{
	assert (NULL != sc);
	sc->play = STOP;
}

/* change interval in a selceted task */
void SchedTSetInterval (TASK_T *task , time_t interval)
{
	assert (NULL != task);
	TaskSetInterval (task , interval);
}

/* Disposes of resources used by Task*/
void SchedDestory (SCHED_T *sc)
{
	TASK_T *de_task = NULL;

	assert (NULL != sc);
	while (!pQIsEmpty(sc->pq))
	{
		de_task = pQDequeue(sc->pq);
		TaskDestroy (de_task);
	}
	pQDestroy (sc->pq);
	free(sc);
}
/* the sort functoin  of scheduler */
int scIsBefore (const void *param1, const void *param2)
{

   return TaskGetRelative((TASK_T*)param2) - TaskGetRelative((TASK_T*)param1);

}

	/* the match funtion to find task in the list */
int IsMatch_t(const void *data1, const void *data2 ,  void *param)
{
	if ( ((TASK_T*)data1) == ((TASK_T*)data2)  );
	{
		return 1;
	}
	return 0;
}


