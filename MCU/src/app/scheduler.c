/*!
 \file   scheduler.c
 \date   December-2022 (created)
 \brief  task scheduler module
*/
#include "scheduler.h"

/* Task queue */
static QueueItem_t TaskQueue[TASK_QUEUE_SIZE];
/* Queue write pointer */
static QueueItem_t* writePointer = NULL;
/* Queue read pointer */
static QueueItem_t* readPointer = NULL;
/* Pointer to background task */
static void (*BackgroundTask)(void);

/*!
 \brief Initializes the task queue
 \param Background task callback
 */
void InitTaskSheduler(void (*callback)(void))
{
	uint32_t i;
    
    BackgroundTask = callback;
	
    for(i = 0; i < TASK_QUEUE_SIZE; i++) {
		TaskQueue[i].taskfunc = NULL;
		TaskQueue[i].argument = NULL;
		TaskQueue[i].next = &TaskQueue[i+1];
	}
	TaskQueue[TASK_QUEUE_SIZE-1].next = &TaskQueue[0]; // loop the queue
	writePointer = readPointer = &TaskQueue[0]; // initialize pointers
}

/*!
 \brief Puts a task to the queue for processing
 \param task to processing
 \param argument of the task
 */
void PutTask(void (*task)(void*), void *arg)
{
__disable_irq();
	writePointer->taskfunc = task;
	writePointer->argument = arg;
	writePointer = writePointer->next;
	if (writePointer == readPointer) {
		readPointer = readPointer->next; // queue overflow control
	}
__enable_irq();
}

/*!
 \brief Manages the launch of tasks
 */
void RunTaskSheduler(void)
{
    if (writePointer == readPointer) { // checks the task queue is empty or not
        BackgroundTask();  // run backgroud task
    }
    else {
        readPointer->taskfunc(readPointer->argument); // run active task from queue
        readPointer = readPointer->next; // moves the pointer to the next task
    }
}
