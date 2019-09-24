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
	sem_t  			m_semFree;	
	sem_t  			m_semOccupied;
	pthread_mutex_t	m_lock;
};

WaitableQueue*	WaitableQueue_Create(size_t _capacity)
{
	WaitableQueue* queue = NULL;	
	const int notShared = 0;
	
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
	
	if(sem_init(&queue->m_semFree,notShared,_capacity))
	{
		pthread_mutex_destroy(&queue->m_lock);
		free(queue->m_vec);
		free(queue);
		return NULL;
	}
	
	if(sem_init(&queue->m_semOccupied,notShared,0))
	{
		pthread_mutex_destroy(&queue->m_lock);
		sem_destroy(&queue->m_semFree);
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
	sem_destroy(&_queue->m_semFree);
	sem_destroy(&_queue->m_semOccupied);
	free(_queue->m_vec);
	free(_queue);
}

static void mySemWait(sem_t* _sem)
{
	int err;
	
	while(EINTR == (err=sem_wait(_sem)))
	{}
	
	assert(err!=EINVAL);

}

static void mySemPost(sem_t* _sem)
{
	int err;
	
	err = sem_post(_sem);
	
	assert(err!=EINVAL);
	assert(err!=EOVERFLOW);
	
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
	
	
	mySemWait(&_queue->m_semFree);
	
		myMtxLock(&_queue->m_lock);
		
			_queue->m_vec[_queue->m_tail++] = _item;
			_queue->m_tail %= _queue->m_capacity;
			_queue->m_nitems++;
			
		myMtxUnlock(&_queue->m_lock);
		
	mySemPost(&_queue->m_semOccupied);
	
	return QUEUE_SUCCESS;
}

WaitableQueue_Result WaitableQueue_Deque(WaitableQueue* _queue, AdtItem *_pValue)
{

	if(!_queue)
	{
		return QUEUE_NOT_INITIALIZED;
	}
		
	mySemWait(&_queue->m_semOccupied);
	
		myMtxLock(&_queue->m_lock);
		
			if(NULL != _pValue)
			{
				*_pValue = _queue->m_vec[_queue->m_head];
			}
			
			++_queue->m_head;
			_queue->m_head %= _queue->m_capacity;
			_queue->m_nitems--;
			
		myMtxUnlock(&_queue->m_lock);
		
	mySemPost(&_queue->m_semFree);
	
	return QUEUE_SUCCESS;

}

int	WaitableQueue_IsEmpty(WaitableQueue* _queue)
{
	size_t nItems;
	
	if(!_queue)
	{
		return 0;
	}

	myMtxLock(&_queue->m_lock);
		nItems = _queue->m_nitems;
	myMtxUnlock(&_queue->m_lock);
	
	return nItems==0;
	
}

size_t	WaitableQueue_Size(WaitableQueue* _queue)
{
	size_t nItems;
	if(!_queue)
	{
		return 0;
	}
	
	myMtxLock(&_queue->m_lock);
		nItems = _queue->m_nitems;
	myMtxUnlock(&_queue->m_lock);
	
	return nItems;
}
