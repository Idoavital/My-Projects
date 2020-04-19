#ifndef __TASK_H__

#define __TASK_H__

#include "ShareStackSched.h" /* Shared declarations between Stack and Scheduler structs */

struct Task 
{

	TASK_FUNC_T func;
	void *param;
	time_t inter;
	time_t relative;
};

/* create task struct */ 
TASK_T *TaskCreate (TASK_FUNC_T func, time_t interval , void *param); 

/* Disposes of resources used by Task */
void TaskDestroy (TASK_T *task);

/* runs the task */  
TASK_T *TaskRun (SCHED_T * sc, TASK_T *task );

/* returns the interval of a selcted task */ 
time_t TaskGetInterval ( TASK_T *task);

/* changes the interval of a selceted task*/ 
void TaskSetInterval (TASK_T *task , time_t new_interval);

/* returns the relative time of a selcted task */
time_t TaskGetRelative ( TASK_T *task);

void TaskSetRelative (TASK_T *task, time_t new_Relative);
#endif /* __TASK_H__ */




