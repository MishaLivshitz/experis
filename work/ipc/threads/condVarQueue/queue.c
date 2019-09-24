#include "queue.h"
#include <stdlib.h>
#include <stddef.h>  /*size_t*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "ADTItem.h"
#include <assert.h>
#include <errno.h>

	
struct WaitableQueue{
	
	void** 			m_vec;
	size_t 			m_capacity;
	size_t 			m_nitems;
	size_t 			m_tail;
	size_t 			m_head;
	pthread_cond_t  m_condFree;	
	pthread_cond_t  m_condOccupied;
	pthread_mutex_t	m_lock;
};

WaitableQueue*	WaitableQueue_Create(size_t _capacity)
{
	WaitableQueue* queue = NULL;	
	
	if(0 == _capacity)
	{
		return NULL;
	}	

	if(NULL == (queue = (WaitableQueue*)malloc(sizeof(WaitableQueue))))
	{
		return NULL;
	}
	
	if(NULL == (queue->m_vec = (void**)malloc(_capacity*sizeof(void*))))
	{
		free(queue);
		return NULL;	
	}
	
	if(pthread_mutex_init(&queue->m_lock,NULL))
	{
		free(queue->m_vec);
		free(queue);
		return NULL;
	}
	
	if(pthread_cond_init(&queue->m_condFree,NULL))
	{
		pthread_mutex_destroy(&queue->m_lock);
		free(queue->m_vec);
		free(queue);
		return NULL;
	}
	
	if(pthread_cond_init(&queue->m_condOccupied,NULL))
	{
		pthread_mutex_destroy(&queue->m_lock);
		pthread_cond_destroy(&queue->m_condFree);
		free(queue->m_vec);
		free(queue);
		return NULL;
	}

	queue->m_capacity =_capacity;
	queue->m_nitems = 0;
	queue->m_tail = 0;
	queue->m_head = 0;

	return queue;
}

void WaitableQueue_Destroy(WaitableQueue* _queue)
{

	if(!_queue)
	{
		return;
	}
	
	assert(WaitableQueue_IsEmpty(_queue));
	
	pthread_mutex_destroy(&_queue->m_lock);
	pthread_cond_destroy(&_queue->m_condFree);
	pthread_cond_destroy(&_queue->m_condOccupied);
	free(_queue->m_vec);
	free(_queue);
}

static void myCondWait(pthread_cond_t* _condV, pthread_mutex_t* _mtx)
{
	int err;
	
	err=pthread_cond_wait(_condV, _mtx);
	assert(err!=EINVAL);
	assert(err!=EPERM);

}

static void myCondSignal(pthread_cond_t* _condV)
{
	int err;
	
	err = pthread_cond_signal(_condV);

	assert(err!=EINVAL);
	
}

static void myMtxLock(pthread_mutex_t* _mtx)
{
	int err;
	
	err = pthread_mutex_lock(_mtx);
	
	assert(err != EINVAL);
	assert(err != EAGAIN);
	assert(err != EDEADLOCK);
}

static void myMtxUnlock(pthread_mutex_t* _mtx)
{
	int err;
	
	err = pthread_mutex_unlock(_mtx);
	
	assert(err != EINVAL);
	assert(err != EAGAIN);
	assert(err != EPERM);
}

WaitableQueue_Result WaitableQueue_Enque(WaitableQueue* _queue, AdtItem _item)
{
	if(!_queue)
	{
		return QUEUE_NOT_INITIALIZED;
	}
	
	myMtxLock(&_queue->m_lock);
		
		while(_queue->m_capacity <= _queue->m_nitems)
		{
			myCondWait(&_queue->m_condFree,&_queue->m_lock);			
		}
		
		_queue->m_vec[_queue->m_tail++] = _item;
		_queue->m_tail %= _queue->m_capacity;
		++_queue->m_nitems;
			
	myMtxUnlock(&_queue->m_lock);
	myCondSignal(&_queue->m_condOccupied);
	
	return QUEUE_SUCCESS;
}

WaitableQueue_Result WaitableQueue_Deque(WaitableQueue* _queue, AdtItem *_pValue)
{

	if(!_queue)
	{
		return QUEUE_NOT_INITIALIZED;
	}
		
	myMtxLock(&_queue->m_lock);
		
		while(!_queue->m_nitems)
		{
			myCondWait(&_queue->m_condOccupied,&_queue->m_lock);			
		}
		
			if(NULL != _pValue)
			{
				*_pValue = _queue->m_vec[_queue->m_head];
			}
			
			++_queue->m_head;
			_queue->m_head %= _queue->m_capacity;
			--_queue->m_nitems;
			
	myMtxUnlock(&_queue->m_lock);	
	myCondSignal(&_queue->m_condFree);
	
	return QUEUE_SUCCESS;

}

int	WaitableQueue_IsEmpty(const WaitableQueue* _queue)
{
	return WaitableQueue_Size(_queue) == 0;
}

size_t	WaitableQueue_Size(const WaitableQueue* _queue)
{
	size_t nItems;
	pthread_mutex_t lock = _queue->m_lock;
	
	if(!_queue)
	{
		return 0;
	}
	
	myMtxLock(&lock);
		nItems = _queue->m_nitems;
	myMtxUnlock(&lock);
	
	return nItems;
}
