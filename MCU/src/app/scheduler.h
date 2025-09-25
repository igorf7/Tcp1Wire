/*!
 \file   scheduler.h
 \date   December-2022 (created)
 \brief  task scheduler module header file
*/
#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "stm32f10x.h"

#ifdef NULL
    #undef NULL
#endif

#define NULL ((void *)0)
    
#define TASK_QUEUE_SIZE 16U

/* Structure of the task queue item */
typedef struct {
    void (*taskfunc)(void*); // task function pointer
    void *argument; // task function argument pointer
    void *next; // pointer to the next item in the queue
} QueueItem_t;

/*** TASK SCHEDULER API ***/
void InitTaskSheduler(void (*callback)(void));
void PutTask(void (*task)(void*), void *arg);
void RunTaskSheduler(void);
#endif // __SCHEDULER_H
