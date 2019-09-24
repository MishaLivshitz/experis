/*
* @brief: This module describes the functionality of the schedular
*
* Author: Michael Livshitz
* Date: 15/5/19
* 
*/
#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <stddef.h>		 /*size_t*/
#include <sys/types.h>
#include <time.h>

typedef struct PeriodicExecutor PeriodicExecutor;

/*
*	@brief: Create a periodic executor that will measure time using given clock.
*			Clockid_t specify the id of the system clock to be used. CLOCK_REALTIME,
*			CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC and similar provided it’s
*			supported by the underlying system
* 
* 	@params:
* 			_clk_id: clock id
* 			
* 	@return: new periodic executer when success else NULL 
* */
PeriodicExecutor* PeriodicExecutor_Create(clockid_t _clk_id);

/*
 * 	@brief: Destroy previously created executor. Cleaning all allocated memory and resources
 * 
 * 	@params: 
 * 			_executor: executor
 * 
 * */

void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);

/*
 * 
 * 	@brief: Adding task to the executor
 * 
 * 	@params:
 * 			_taskFunction ​ is represented by a user provided function pointer.
 * 			_context: parameter for user
 * 			_period_ms ​ is the period of recurrence in milliseconds.
 * 
 * 	@return 0 if not valid, -1 if task create failed and 1 when success.
 * */
int PeriodicExecutor_Add(PeriodicExecutor* _executor,int (*_taskFunction)(void *),void* _context, size_t _period_ms);

/*
 * 	@brief:Start running the tasks previously added to the executor or resume a previously paused Executor.
 *		   This function will return in one of two cases:
 *						1. The tasks were executed to completion.
 *						2. The executor was paused
 * 	@params:
 * 			_executor: executor
 * 
 *  @returns: the number of execution cycles (user task function calls) performed.
 * 
 * */
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);


/*
 *	@brief:	Pause the execution of the executor. If a task is currently being executed then pause after
 *			it has completed the current cycle.
 *			The paused executor can be resumed later on by calling PeriodicExecutor_Run API
 * 
 * 	@params:
 * 			_executor: executor
 * 
 * 	@returns: the number of tasks remaining inside the executor.
 * */
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor);
#endif
