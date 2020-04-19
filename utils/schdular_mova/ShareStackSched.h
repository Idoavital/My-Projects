#ifndef __SHARE_STACK_SCHED_H__

#define __SHARE_STACK_SCHED_H__

typedef struct Task TASK_T;

typedef struct Sched SCHED_T;

typedef void (*TASK_FUNC_T) (SCHED_T *sc, TASK_T *task, void *param);

#endif /*__SHARE_STACK_SCHED_H__*/
