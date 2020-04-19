
#include <assert.h> /*assert*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/
#include <time.h> /* time_t */

#include "scheduler.h" /*scheduler function*/
#include "task.h"


struct Task 
{
	TASK_FUNC_T func;
	time_t interval;
	time_t exec_time; 
	void *param;
};


/* create task struct */ 
TASK_T *TaskCreate (TASK_FUNC_T func, void *param, time_t interval)
{
	TASK_T * task = NULL;
	
	assert(NULL != func && "func cant be NULL");
	assert( 0 != interval && "interval cant be NULL");

	task = (TASK_T *)malloc(sizeof(TASK_T));
	
	if (NULL == task)
	{
		return NULL;
	}
	
	task->func = func;
	task->interval = interval;
	task->exec_time = 0;
	task->param = param;
	
	return task;
} 


/* Disposes of resources used by Task */
void TaskDestroy (TASK_T *task)
{
	assert(NULL != task && "task cant be NULL");
	
	free(task);
}

/* runs the task */  
void TaskRun (TASK_T *task, SCHED_T *sched)
{
	assert(NULL != task && NULL != sched && "");	
	task->func(sched, task , task->param);
}

/* returns the interval of a selcted task */ 
time_t TaskGetInterval (const TASK_T *task)
{
	assert(NULL != task && "task cant be NULL");
	
	return task->interval;
}


/* changes the interval of a selceted task*/ 
void TaskSetInterval (TASK_T *task, time_t new_interval)
{
	assert(NULL != task && "task cant be NULL");
		
	task->interval = new_interval;
}

/* returns the interval of a selcted task */ 
time_t TaskGetExecTime (const TASK_T *task)
{
	assert(NULL != task && "task cant be NULL");
	
	return task->exec_time;
}


/* changes the interval of a selceted task*/ 
void TaskSetExecTime (TASK_T *task, time_t new_exec_time)
{
	assert(NULL != task && "task cant be NULL");
		
	task->exec_time = new_exec_time;	
}




