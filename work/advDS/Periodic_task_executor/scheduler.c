#include <stdlib.h>
#include "scheduler.h"
#include "task.h"
#include "pq.h"

#define ACTIVE_MAGIC_NUM 	0xdefdef
#define IS_VALID(E)			((E) && (E)->m_magicNum == ACTIVE_MAGIC_NUM)
#define P_QUEUE(E) 			((E)->m_pQueue)
#define RUN_CONDITION(E)	(PrioQ_Size((P_QUEUE(E))) != 0 && !(E)->m_paused)	
	
struct PeriodicExecutor
{
	int		 	m_magicNum;
	PrioQ* 	 	m_pQueue;
	clockid_t	m_clockID;
	int 		m_paused;
};

PeriodicExecutor* PeriodicExecutor_Create(clockid_t _clk_id)
{
	PeriodicExecutor* pExec;
	
	pExec = (PeriodicExecutor*)calloc(1,sizeof(PeriodicExecutor));
	
	if(!pExec)
	{
		return NULL;
	}
	
	P_QUEUE(pExec) = PrioQ_Create((AdtItemCompare)Task_Compare);
	
	if(!P_QUEUE(pExec))
	{
		free(pExec);
		return NULL;
	}
	
	pExec->m_clockID = _clk_id;
	pExec->m_magicNum = ACTIVE_MAGIC_NUM;
	
	return pExec;
}

void PeriodicExecutor_Destroy(PeriodicExecutor* _executor)
{
	if(!IS_VALID(_executor))
	{
		return;
	}
	
	_executor->m_magicNum = -1;
	PrioQ_Destroy(P_QUEUE(_executor), (AdtItemDestroy)Task_Destroy);
	free(_executor);
}

int PeriodicExecutor_Add(PeriodicExecutor* _executor,int (*_taskFunction)(void *),void* _context, size_t _period_ms)
{
	Task* newTask;
	
	if(!IS_VALID(_executor))
	{
		return 0;
	}
	
	newTask = Task_Create(_executor->m_clockID,_period_ms,_taskFunction,_context);
	
	if(!newTask)
	{
		return -1;
	}
	
	PrioQ_Enqueue(P_QUEUE(_executor), newTask);
	return 1;
}

size_t PeriodicExecutor_Run(PeriodicExecutor* _executor)
{
	size_t i;
	Task* task;
	
	if(!IS_VALID(_executor))
	{
		return 0;
	}
	
	_executor->m_paused = 0;
	
	for(i=0; PrioQ_Size(P_QUEUE(_executor)) != 0 && !_executor->m_paused; i++)
	{
		PrioQ_Dequeue(P_QUEUE(_executor),(AdtItem)&(task));
		if(Task_Execute(task))
		{
			Task_TimeUpdate(task);
			PrioQ_Enqueue(P_QUEUE(_executor),task);
		}
		else
		{
			Task_Destroy(task);
		}
	}
	
	return i;
}

size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor)
{
	if(!IS_VALID(_executor))
	{
		return 0;
	}
	
	_executor->m_paused = 1;
	return PrioQ_Size(P_QUEUE(_executor));
}
