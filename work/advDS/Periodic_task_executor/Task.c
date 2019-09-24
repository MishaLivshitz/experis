#include "task.h"
#include <unistd.h>
#define ACTIVE_MAGIC_NUM  	0xdefdef
#define NANO_TO_SEC(NS) 	(NS)/1000*1000*1000
#define IS_VALID(T)			((T) && (T)->m_magicNum == ACTIVE_MAGIC_NUM)

struct Task{
	
	size_t           m_magicNum;
    int              m_interval;
    Time*  			 m_nextExec;
    TaskFunc         m_taskAction;
    void*            m_context;
};


Task* Task_Create(clockid_t _clock,int _interval, TaskFunc _taskAction, void* _context)
{
	Task* task;
	
	if(!_taskAction)
	{
		return NULL;
	}
	
	task = (Task*)calloc(1,sizeof(Task));
	if(!task)
	{
		return NULL;
	}
	
	task->m_nextExec = Time_Create(_clock,_interval);
	
	if(!task->m_nextExec)
	{
		free(task);
		return NULL;
	}
	
	task->m_interval = _interval;
	task->m_taskAction = _taskAction;
	task->m_context = _context;
	task->m_magicNum = ACTIVE_MAGIC_NUM;
	
	return task;
}

void Task_Destroy(Task* _task)
{
	if(!IS_VALID(_task))
	{
		return;
	}

	Time_Destroy(_task->m_nextExec);
	free(_task);
}

int Task_Execute(const Task* _task)
{

	if(!IS_VALID(_task))
	{
		return 0;
	}
	
	Time_Wait(_task->m_nextExec);
	
	return _task->m_taskAction(_task->m_context);
}

int Task_Compare(const Task* _a, const Task* _b)
{
	return Time_Compare(_a->m_nextExec, _b->m_nextExec);
}

int Task_TimeUpdate(Task* _t)
{
	return Time_SetTime(_t->m_nextExec, _t->m_interval) != NULL;
}
