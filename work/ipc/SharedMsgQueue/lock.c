
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif

#include "lock.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
struct Lock
{
	pthread_mutexattr_t m_mtxAttr;
	pthread_mutex_t		m_lock;
	pthread_condattr_t 	m_condAttr;
	pthread_cond_t		m_condVar;
	
};

size_t Lock_AllocSize()
{
	return sizeof(Lock);
}

Lock* Lock_Init(Lock* _sync)
{
	
	
	pthread_mutexattr_init(&_sync->m_mtxAttr);
	pthread_mutexattr_setpshared(&_sync->m_mtxAttr, PTHREAD_PROCESS_SHARED);
	
	pthread_condattr_init(&_sync->m_condAttr);
	pthread_condattr_setpshared(&_sync->m_condAttr, PTHREAD_PROCESS_SHARED);
	
	pthread_mutex_init(&_sync->m_lock,&_sync->m_mtxAttr);
	pthread_cond_init(&_sync->m_condVar,&_sync->m_condAttr);

	return _sync;	
}

void Lock_Destroy(Lock* _sync)
{
	pthread_mutexattr_destroy(&_sync->m_mtxAttr);
	pthread_condattr_destroy(&_sync->m_condAttr);
	pthread_mutex_destroy(&_sync->m_lock);
	pthread_cond_destroy(&_sync->m_condVar);
}

void Lock_MtxLock(Lock* _sync)
{
	int err;
	
	err = pthread_mutex_lock(&_sync->m_lock);
	/*assert(err!=EINVAL);*/
	assert(err!=EAGAIN);
	assert(err!=EDEADLK);
}

void Lock_MtxUnlock(Lock* _sync)
{
	int err;
	
	err = pthread_mutex_unlock(&_sync->m_lock);	
	/*assert(err!=EINVAL);*/
	assert(err!=EAGAIN);
}

void Lock_CondWait(Lock* _sync)
{
	int err;
	
	err = pthread_cond_wait(&_sync->m_condVar,&_sync->m_lock);		
	/*assert(err!=EINVAL);*/
	assert(err!=EPERM);
	
}

void Lock_CondSignal(Lock* _sync)
{
	int err;

	err = pthread_cond_signal(&_sync->m_condVar);
	/*assert(err!=EINVAL);*/
	
}
