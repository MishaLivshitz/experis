#include <stddef.h>  /*size_t*/

#include "sharedManager.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/stat.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#define	OFFSET_TO_ADDRESS(S,O)		(((char*)(S)) + sizeof(SharedManager) + (O))
#define	ADDRESS_TO_OFFSET(S,A)		(((char*)(A)) - (((char*)(S)) + sizeof(SharedManager)))	
				
#define FREE_SPACE(S)				((S)->m_dataSize - (S)->m_occupied)
#define IS_OVER_MAX_SIZE(S,O,BS)		((O) + (BS) > (S)->m_dataSize)
#define REAL_MSG_SIZE(BUFF_SIZE)		((BUFF_SIZE) + sizeof(size_t))


#define DEFAULT_PROJ_ID	7
#define PERMISSION				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH  

struct SharedManager
{
	pthread_mutex_t m_lock;
	int 			m_sid;
	size_t 			m_headOffset;
	size_t 			m_tailOffset;
	size_t 			m_dataSize;
	size_t 			m_occupied;
	
};

typedef struct Msg
{
	size_t 			m_size;
	char*			m_data[1];
}Msg;

SharedManager* SharedManager_Create(const char* _name, size_t _memSize)
{
	
	key_t key;
	int sid;
	SharedManager* pShared;
	
	if(-1 == (key=ftok(_name,DEFAULT_PROJ_ID)))
	{
		perror("ftok failed");
		return NULL;
	}
	
	/*TODO: Alignment?!*/
	
	if(-1==(sid = shmget(key,_memSize + sizeof(SharedManager),IPC_CREAT|PERMISSION)))
	{
		perror("shmget failed");
		return NULL;
	}
	
	if((void*)-1== (pShared = shmat(sid,NULL,0)))
	{
		perror("shmat failed");
		return NULL;
	}
	
	if(pthread_mutex_init(&pShared->m_lock,NULL))
	{
		if(-1 == shmctl(sid,IPC_RMID,NULL))
		{
			perror("shmctl failed");
		}
		
		perror("pthread_mutex_init failed");
		return NULL;
	}
	
	pShared->m_sid = sid;
	pShared->m_dataSize = _memSize;
	pShared->m_occupied = 0;
	pShared->m_headOffset = 0;
	pShared->m_tailOffset = 0;	
	
	return pShared;
	
}

SharedManager* SharedManager_GetMem(const char* _name)
{
	key_t key;
	int sid;
	SharedManager* pShared;
		
	if(-1 == (key=ftok(_name,DEFAULT_PROJ_ID)))
	{
		perror("ftok failed");
		return NULL;
	}
	
	if(-1==(sid = shmget(key,0,PERMISSION)))
	{
		perror("shmget failed");
		return NULL;
	}
	
	if((void*)-1== (pShared = shmat(sid,NULL,0)))
	{
		perror("shmat failed");
		return NULL;
	}
	
	return pShared;
}

int SharedManager_Destroy(SharedManager* _pShared, int _isCreator)
{
	int err;
	assert(NULL != _pShared);
	
	if(_isCreator)
	{
		err = pthread_mutex_destroy(&_pShared->m_lock); 
		if(err)
		{
			perror("pthread_mutex_destory failed");
			return err;
		}
		
		err = shmctl(_pShared->m_sid,IPC_RMID,NULL);
		if(-1 == err)
		{
			perror("shmctl failed");
			return err;
		}
	}
	else
	{
		err = shmdt(_pShared);
		if(-1 == err)
		{
			perror("shmdt failed");
			return err;
		}
	}
	
	return 0;
}

static void* HandleSplitMsgWrite(SharedManager* _pShared,void* _buffer,size_t* _bufSize)
{
	size_t partSize;
	
	partSize = _pShared->m_dataSize - _pShared->m_tailOffset;
	memcpy(OFFSET_TO_ADDRESS(_pShared,_pShared->m_tailOffset), _buffer, partSize);
	*_bufSize -= partSize; 
	_pShared->m_occupied += partSize;
	_buffer = (char*)_buffer + partSize;
	
	return _buffer;
}

static void* HandleSplitMsgRead(SharedManager* _pShared,void* _buffer,size_t *_msgSize)
{
	size_t partSize;
	
	partSize = _pShared->m_dataSize - _pShared->m_headOffset;
	memcpy(_buffer, OFFSET_TO_ADDRESS(_pShared,_pShared->m_headOffset), partSize);
	*_msgSize -= partSize; 
	_pShared->m_occupied -= partSize;
	_buffer = (char*)_buffer + partSize;
	
	return _buffer;
}

static void WriteMsg(SharedManager* _pShared, void* _buffer, size_t _bufSize)
{
	size_t* tailAddress;
	
	tailAddress = (size_t*)OFFSET_TO_ADDRESS(_pShared,_pShared->m_tailOffset); 
	*tailAddress = _bufSize;
	++tailAddress;
	_pShared->m_tailOffset = ADDRESS_TO_OFFSET(_pShared,tailAddress);
	
	if(IS_OVER_MAX_SIZE(_pShared,_pShared->m_tailOffset, _bufSize))
	{
		_buffer = HandleSplitMsgWrite(_pShared,_buffer,&_bufSize);
		_pShared->m_tailOffset = 0; 
	}
	
	memcpy(OFFSET_TO_ADDRESS(_pShared,_pShared->m_tailOffset),_buffer,_bufSize);
	_pShared->m_tailOffset += _bufSize;
	_pShared->m_occupied += REAL_MSG_SIZE(_bufSize);
	
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

SharedManagerResult SharedManager_Enqueue(SharedManager* _pShared, void* _buffer, size_t _bufSize)
{
	SharedManagerResult status = SHARED_MEM_SUCCESS;
	
	assert(_pShared && _buffer);
	
	/*TODO: Alignment?!*/
	myMtxLock(&_pShared->m_lock);
		
		if(REAL_MSG_SIZE(_bufSize) > FREE_SPACE(_pShared))
		{
			status = SHARED_MEM_FULL;
		}
		else  
		{
			WriteMsg(_pShared, _buffer, _bufSize);
		}
	
	myMtxUnlock(&_pShared->m_lock);
	
	return status;
}

static SharedManagerResult ReadMsg(SharedManager* _pShared, void* _buffer, size_t _bufSize, size_t* _bytesRead)
{
	size_t* headAddress;
	size_t msgSize;
	
	headAddress = (size_t*)OFFSET_TO_ADDRESS(_pShared,_pShared->m_headOffset);
	msgSize = *headAddress;
	*_bytesRead = msgSize;
	
	if(msgSize > _bufSize)
	{
		return SHARED_MEM_BUFFER_TO_SMALL;
	}

	++headAddress;
	_pShared->m_headOffset = ADDRESS_TO_OFFSET(_pShared,headAddress);
	
	if(IS_OVER_MAX_SIZE(_pShared,_pShared->m_headOffset,msgSize))
	{
		_buffer = HandleSplitMsgRead(_pShared,_buffer,&msgSize);
		_pShared->m_headOffset = 0;
	}

	memcpy(_buffer, OFFSET_TO_ADDRESS(_pShared,_pShared->m_headOffset),msgSize);
	_pShared->m_headOffset += msgSize;
	_pShared->m_occupied -= REAL_MSG_SIZE(msgSize);
	
	return SHARED_MEM_SUCCESS;
}

SharedManagerResult SharedManager_Dequeue(SharedManager* _pShared, void* _buffer, size_t _bufSize, size_t* _bytesRead)
{
	
	SharedManagerResult status = SHARED_MEM_SUCCESS;
	
	assert(_pShared && _buffer);
	
	/*TODO: Alignment?!*/
	myMtxLock(&_pShared->m_lock);
		
		if(0 == _pShared->m_occupied)
		{
			status = SHARED_MEM_EMPTY;
		}
		else
		{	
			status = ReadMsg(_pShared,_buffer,_bufSize, _bytesRead);
		}
		
	myMtxUnlock(&_pShared->m_lock);
	
	return status;
}

int SharedManager_IsEmpty(SharedManager* _pShared)
{
	int isEmpty;
	assert(_pShared);
	
	myMtxLock(&_pShared->m_lock);
		isEmpty = 0 == _pShared->m_occupied;
	myMtxUnlock(&_pShared->m_lock);
	
	return isEmpty;
}
