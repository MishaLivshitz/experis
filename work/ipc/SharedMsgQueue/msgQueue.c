#include <stdio.h>
#include <stdlib.h>
#include "sharedManager.h"
#include "msgQueue.h"
#include "MyMalloc.h"
#include "lock.h"
#include "queue.h"
#include <assert.h>
#include <string.h>


struct SharedMessageQueue
{
	void*		 		m_sharedMem;
	Queue*				m_queue;
	Lock*				m_sync;
	char*				m_messages;	
	int 				m_isCreator;
};

SharedMessageQueue* SharedMessageQueue_Create(const char *_name,size_t _memSize, size_t _numOfItems)
{
	
	SharedMessageQueue* q;
	size_t queueSize;
	size_t syncSize;
	
	if(!_numOfItems||!_name)
	{
		return NULL;
	}
	
	q = (SharedMessageQueue*)malloc(sizeof(SharedMessageQueue));
	if(!q)
	{
		return NULL;
	}
	
	queueSize = Queue_AllocSize(_numOfItems);
	syncSize = Lock_AllocSize();
	q->m_sharedMem = SharedManager_Create(_name, _memSize, queueSize, syncSize);
	
	if(!q->m_sharedMem)
	{
		free(q);
		return NULL;
	}

	q->m_queue = SharedManager_GetQueueAddress(q->m_sharedMem);
	q->m_sync = SharedManager_GetSyncAddress(q->m_sharedMem);
	q->m_messages = SharedManager_GetMessagesAddress(q->m_sharedMem);
	
	q->m_sync = Lock_Init(q->m_sync);
	/*TODO:LOCK*/
	q->m_queue = Queue_Init(q->m_queue,_numOfItems);
	q->m_messages = MyMallocInit(q->m_messages,_memSize);
	/*TODO:UNLOCK*/
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
	
	q->m_sharedMem = SharedManager_Connect(_name);
	if(!q->m_sharedMem)
	{
		free(q);
		return NULL;
	}
	
	q->m_queue = SharedManager_GetQueueAddress(q->m_sharedMem);
	q->m_sync = SharedManager_GetSyncAddress(q->m_sharedMem);
	q->m_messages = SharedManager_GetMessagesAddress(q->m_sharedMem);
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
	
	if(_q->m_isCreator)
	{
		Lock_Destroy(_q->m_sync);	
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
	char* newMsg;
	int offset;
	Queue_Result status = MSG_QUEUE_SUCCESS;
	
	if(!_q || !_buffer)
	{
		return MSG_QUEUE_NOT_INIT;
	}
	
	Lock_MtxLock(_q->m_sync);
	
		newMsg = (char*)MyMalloc(_q->m_messages,_bufSize);
		if(!newMsg)
		{
			Lock_MtxUnlock(q->m_sync);
			return MSG_QUEUE_BAD_ALLOC;
		}
	
		while(Queue_IsFull(_q->m_queue))
		{
			Lock_CondWait(_q->m_sync);
		}
				
	Lock_MtxUnlock(_q->m_sync);
	
	offset = newMsg - _q->m_messages;
	memcpy(newMsg, _buffer, _bufSize);
	
	Lock_MtxLock(_q->m_sync);
		Queue_Enque(_q->m_queue, _bufSize, offset);	
	Lock_MtxUnlock(_q->m_sync);
	
	Lock_CondSignal(_q->m_sync);
	
	return status;
}

SharedMessageQueueResult SharedMessageQueue_Recv (SharedMessageQueue *_q, void* _buffer, size_t _bufSize, size_t* _bytesRead)
{
	Queue_Result status;
	size_t offset;
	
	if(!_q)
	{
		return MSG_QUEUE_NOT_INIT;
	}
	
	if(!_buffer)
	{
		return MSG_QUEUE_WRONG_ARGUMENT;
	}
	
	Lock_MtxLock(_q->m_sync);
	
		status = Queue_Deque(_q->m_queue, _bufSize, _bytesRead, &offset);	
		if(-1 == status)
		{
			status =  MSG_QUEUE_BUFFER_TOO_SMALL;
		}
		else 
		{	
			while(QUEUE_UNDERFLOW == status)
			{
				Lock_CondWait(_q->m_sync);	
				status = Queue_Deque(_q->m_queue, _bufSize, _bytesRead, &offset);
			}
			
			memcpy(_buffer, &_q->m_messages[offset], *_bytesRead);
			MyFree(&_q->m_messages[offset]);
		}
		
	Lock_MtxUnlock(_q->m_sync);					
	Lock_CondSignal(_q->m_sync);
		
	return status == QUEUE_SUCCESS ? MSG_QUEUE_SUCCESS: status;
}

int SharedMessageQueue_IsEmpty (SharedMessageQueue* _q)
{
	int isEmpty;
	
	Lock_MtxLock(_q->m_sync);
		isEmpty = Queue_IsEmpty(_q->m_queue);
	Lock_MtxUnlock(_q->m_sync);	
	
	return isEmpty;
}
