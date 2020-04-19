#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <unistd.h> /*sleep*/

#include "scheduler.h" /*scheduler function*/
#include "pQueueHeap.h" /* PQUEUE type and finction */ /*real pQueue */
#include "task.h" /*task function*/

typedef enum OnOff {STOP , RUN} ON_OFF;

struct Sched
{
	PQUEUE * pq;
	int status;
};


/* the sort functoin  of scheduler */
int scIsBefore (const void *param1, const void *param2);

/* the match funtion to find task in the list */
int TaskMatch(const void *data1, const void *data2 ,  void *param);


/* create scheduler struct */ 
SCHED_T* SchedCreate(void)
{
	SCHED_T* sc = (SCHED_T*)malloc(sizeof(SCHED_T));
	
	if (NULL == sc)
	{
		return NULL;
	}
	
	sc->pq = pQCreate(scIsBefore);
	if (NULL == sc->pq)
	{
		return NULL;
	}
	
	sc->status = RUN;
	
	return sc;
}


/* Disposes of resources used by Task*/
void SchedDestory(SCHED_T *sc)
{
	TASK_T *de_task = NULL;
	
	assert(NULL != sc && "func cant be NULL");
		
	while (!pQIsEmpty(sc->pq))
	{
		de_task = pQDequeue(sc->pq);
		TaskDestroy (de_task);
	}
	
	pQDestroy(sc->pq);
	
	free(sc);
}

/* add a new task to scheduler */ 
TASK_T* SchedAddTask(SCHED_T *sc, TASK_FUNC_T func, void *param, time_t interval)
{
	TASK_T* task = NULL;
	
	assert(NULL != sc && "sc cant be NULL");
	assert(NULL != func && "func cant be NULL");
	
	task = TaskCreate (func, param, interval);
	if (NULL == task)
	{
		return NULL;
	}
	
	return (pQEnqueue(sc->pq, task) ? NULL : task);
}


/* removes a task from scheduler */ 
void SchedRemoveTask(SCHED_T *sc, TASK_T *task)
{
	assert(NULL != sc && "sc cant be NULL");
	assert(NULL != task && "task cant be NULL");
	
	pQErase (sc->pq, TaskMatch, (void *)task, NULL);
	TaskDestroy (task);
}




/* runs the scheduler */ 
void SchedRun(SCHED_T *sc)
{
	TASK_T *task = NULL;
	time_t sleep_time = 0;
	time_t curr_time = time(NULL);
	
	assert(NULL != sc && "sc cant be NULL");
	
	task =(TASK_T *)pQDequeue(sc->pq);	
	
	while (TaskGetExecTime(task) < curr_time)
	{
		TaskSetExecTime(task, time(NULL) + TaskGetInterval(task));
		pQEnqueue(sc->pq , task); 
		
		task =(TASK_T *)pQDequeue(sc->pq);
	}
	
	pQEnqueue(sc->pq , task); 
	
	while (sc->status == RUN)
	{
		task =(TASK_T *)pQDequeue(sc->pq);	
		
		sleep_time = TaskGetExecTime(task) - time(NULL) > 0 ? TaskGetExecTime(task) - time(NULL) : 0;
		
		while (	sleep (sleep_time)); /* stop the runnig for the interval time of task */
     			
   		TaskSetExecTime(task, time(NULL) + TaskGetInterval(task));
		pQEnqueue(sc->pq , task); /*Enqueue again the task with the relative time */
		TaskRun (task, sc); /* run the last task */
	}
}

/* stops the scheduler */ 
void SchedStop(SCHED_T *sc)
{
	assert(NULL != sc && "sc cant be NULL");

	sc->status = STOP;
}

/* change interval in a selected task */ 
void SchedTSetInterval(TASK_T *task, time_t interval)
{
	assert(NULL != task && "task cant be NULL");

	TaskSetInterval(task, interval);
}


/* the sort functoin  of scheduler */
int scIsBefore (const void *param1, const void *param2)
{
	assert(NULL != param1 && NULL != param2 && "sc cant be NULL");
	
	return ( TaskGetExecTime((TASK_T *)param2) > TaskGetExecTime((TASK_T *)param1));
}

/* the match funtion to find task in the list */
int TaskMatch(const void *data1, const void *data2 ,  void *param)
{
	assert(NULL != data1 && NULL != data2 && "sc cant be NULL");
	
	return ((TASK_T*)data1 == (TASK_T*)data2);
}
