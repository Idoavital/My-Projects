

struct Task 
{
	
	TASK_FUNC_T func;
	unsigned int inter;
};


/* create task struct */ 
TASK_T *TaskCreate (TASK_FUNC_T func, unsigned int interval)
{
	TASK_T *ta = (TASK_T *)  malloc (sizeof(TASK_T));
	if (NULL == ta)
	{
		return NULL;
	}
	ta->func = func;
	ta->inter = intreval;
}


/* Disposes of resources used by Task */
void TaskDestroy (TASK_T *task)
{

}

/* runs the task */  
TASK_T *TaskRun (const TASK_FUNC_T *task);

/* returns the interval of a selcted task */ 
unsigned int TaskGetInterval (const TASK_FUNC_T *task);

/* changes the interval of a selceted task*/ 
void TaskSetInterval (TASK_FUNC_T *task, unsigned int new_interval);
