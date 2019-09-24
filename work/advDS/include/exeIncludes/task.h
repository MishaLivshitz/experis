/*
 * This file describes the functionality of task module
 * 
 * Author: Michael Livshitz
 * Date: 15/5/19
 * 
 * **/
#ifndef _TASK_H
#define _TASK_H

#include "Time.h"

typedef int (*TaskFunc)(void* context);

typedef struct Task Task;

/*
 * @brief: This method creates a task
 * 
 * @params:
 * 			_clock: clock id
 * 			_interval: interval time for task to execute
 * 			_taskAction: the action of the task
 * 			_context: additional space for user
 * 
 * @return: new task when success else return NULL 
 * 
 * */
Task* Task_Create(clockid_t _clock ,int _interval, TaskFunc _taskAction, void* _context);


/*
 * @brief: This method destroys a task
 * 
 * @params:
 * 			_task: task
 * 			
 * */
void Task_Destroy(Task* _task);

/*
 * @brief: This method executes a task
 * 
 * @params:
 * 			_task: task
 * 			
 * @return: 1 when it is needed to execute the task again else return 0
 * 			
 * */

int Task_Execute(const Task* _task);

/*
 * @brief: This method compares a task
 * 
 * @params:
 * 			_a: task a
 * 			_b: task b
 * 
 * @return: positive when a > b negative if a < b else 0
 * 			
 * */

int Task_Compare(const Task* _a, const Task* _b);

/*
 * @brief: This method updates the next execution time of a task
 * 
 * @params:
 * 			_t: task
 * @return: 1 when success else 0
 * 			
 * */
int Task_TimeUpdate(Task* _t);
#endif
