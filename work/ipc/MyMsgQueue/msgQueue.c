#include <stdio.h>
#include <stdlib.h>
#include "sharedManager.h"
#include "msgQueue.h"
#include <assert.h>

struct SharedMessageQueue
{
	SharedManager* 		m_sharedMem;		
	int 				m_isCreator;
};


SharedMessageQueue* SharedMessageQueue_Create(const char *_name, size_t _memSize)
{
	
	SharedMessageQueue* q;
	
	if(!_memSize||!_name)
	{
		return NULL;
	}
	
	q = (SharedMessageQueue*)malloc(sizeof(SharedMessageQueue));
	if(!q)
	{
		return NULL;
	}
	
	q->m_sharedMem = SharedManager_Create(_name,_memSize);
	if(!q->m_sharedMem)
	{
		free(q);
		return NULL;
	}
	
	q->m_isCreator = 1;
	
	return q;
}

SharedMessageQueue* SharedMessageQueue_Connect(const char *_name)
{
	SharedMessageQueue* q;
	assert(_name);
	
	q = (SharedMessageQueue*)malloc(sizeof(SharedMessageQueue));
	if(!q)
	{
		return NULL;
	}
	
	q->m_sharedMem = SharedManager_GetMem(_name);
	if(!q->m_sharedMem)
	{
		free(q);
		return NULL;
	}
	
	q->m_isCreator = 0;
	
	return q;
}

void SharedMessageQueue_Destroy(SharedMessageQueue *_q)
{
	int err;
	if(!_q)
	{
		return;
	}
	
	err = SharedManager_Destroy(_q->m_sharedMem, _q->m_isCreator);
	if(err)
	{
		return;
	}
	
	
	free(_q);
}

SharedMessageQueueResult SharedMessageQueue_Send (SharedMessageQueue *_q, void* _buffer, size_t _bufSize)
{
	if(!_q || !_buffer)
	{
		return MSG_QUEUE_NOT_INIT;
	}
	
	if(SHARED_MEM_FULL == SharedManager_Enqueue(_q->m_sharedMem,_buffer,_bufSize))
	{
		return MSG_QUEUE_OVERFLOW;
	}
	
	return MSG_QUEUE_SUCCESS;
}

SharedMessageQueueResult SharedMessageQueue_Recv (SharedMessageQueue *_q, void* _buffer, size_t _bufSize, size_t* _bytesRead)
{
	SharedManagerResult status;
	
	if(!_q || !_buffer)
	{
		return MSG_QUEUE_NOT_INIT;
	}
	
	status = SharedManager_Dequeue(_q->m_sharedMem,_buffer,_bufSize, _bytesRead);
	
	if(SHARED_MEM_EMPTY == status)
	{
		return MSG_QUEUE_UNDERFLOW;
	}
	
	if(SHARED_MEM_BUFFER_TO_SMALL == status)
	{
		return MSG_QUEUE_BUFFER_TOO_SMALL;
	}
	
	return MSG_QUEUE_SUCCESS;
}

int SharedMessageQueue_IsEmpty (SharedMessageQueue* _q)
{
	return NULL == _q ? 0:  SharedManager_IsEmpty(_q->m_sharedMem);
}
