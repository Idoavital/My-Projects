#include <time.h>
#include <stdlib.h>
#include <assert.h>


#include "ShareStackSched.h"
#include "task.h" 



/* create task struct */ 
TASK_T *TaskCreate (TASK_FUNC_T func, time_t interval , void *param)
{
 	
	TASK_T *ta = NULL ;
	
	ta = (TASK_T *)  malloc (sizeof(TASK_T));
	if (NULL == ta)
	{
		return NULL;
	}
	

	ta->func = func;
	ta->inter = interval;
	ta->param = param;
	ta->relative = 0; 
	
	
	return ta;
}


/* Disposes of resources used by Task */
void TaskDestroy (TASK_T *task)
{
	assert (NULL != task);
	free(task);
}

/* runs the task */  
TASK_T *TaskRun (SCHED_T *sc , TASK_T *task  )
{
	assert (NULL != sc);
	assert (NULL != task);
	
	task->func (sc, task , task->param);
	
	return task;
}

/* returns the interval of a selcted task */ 

time_t TaskGetInterval ( TASK_T *task)
{
	assert (NULL != task);
	
	return task->inter;

}


/* changes the interval of a selceted task*/ 
void TaskSetInterval (TASK_T *task, time_t new_interval)
{
	task->inter =  new_interval;
}

time_t TaskGetRelative ( TASK_T *task)
{
	assert (NULL != task);
	
	return task->relative;
}

void TaskSetRelative (TASK_T *task, time_t new_Relative)
{
	task->relative =  new_Relative;
}



