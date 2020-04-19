#ifndef __TASK_H__

#define __TASK_H__

#include "ShareStackSched.h" /* Shared declarations between Stack and Scheduler structs */
#include <time.h> /* time_t */

/* create task struct */ 
TASK_T *TaskCreate (TASK_FUNC_T func, void *param, time_t interval); 

/* Disposes of resources used by Task */
void TaskDestroy (TASK_T *task);

/* runs the task */  
void TaskRun (TASK_T *task, SCHED_T *sched);

/* returns the interval of a selcted task */ 
time_t TaskGetInterval (const TASK_T *task);

/* changes the interval of a selceted task*/ 
void TaskSetInterval (TASK_T *task, time_t new_interval);

/* returns the interval of a selcted task */ 
time_t TaskGetExecTime (const TASK_T *task);

/* changes the interval of a selceted task*/ 
void TaskSetExecTime (TASK_T *task, time_t new_exec_time);

#endif /* __TASK_H__ */
