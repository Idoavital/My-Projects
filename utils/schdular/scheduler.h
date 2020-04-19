#ifndef __SCHEDULER_H__

#define __SCHEDULER_H__

#include <time.h> /* time_t */

#include "ShareStackSched.h" /* Shared declarations between Stack and Scheduler structs */


/* create scheduler struct */ 
SCHED_T* SchedCreate(void);

/* Disposes of resources used by Task*/
void SchedDestory (SCHED_T *sc);

/* add a new task to scheduler */ 
TASK_T* SchedAddTask (SCHED_T *sc, TASK_FUNC_T func, void *param, time_t interval); 

/* removes a task from scheduler */ 
void SchedRemoveTask (SCHED_T *sc, TASK_T *task);

/* runs the scheduler */ 
void SchedRun (SCHED_T *sc);

/* stops the scheduler */ 
void SchedStop (SCHED_T *sc);

/* change interval in a selceted task */ 
void SchedTSetInterval (TASK_T *task , time_t interval);




#endif /* __SCHEDULER_H__ */



