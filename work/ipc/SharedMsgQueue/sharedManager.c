#include <stddef.h>  /*size_t*/

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "sharedManager.h"

#define DEFAULT_PROJ_ID	7
#define PERMISSION						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH  
#define OFFSET_TO_ADDRESS(A,O)			(((char*)(A)) + (O))

struct SharedManager
{
	size_t 			m_queueOffset;
	size_t 			m_syncOffset;
	size_t			m_messagesOffset;
	int 			m_sid;
};

SharedManager* SharedManager_Create(const char* _name, size_t _memSize, size_t _queueSize, size_t _syncSize)
{
	
	key_t key;
	int sid;
	SharedManager* pShared;
	
	if(-1 == (key=ftok(_name,DEFAULT_PROJ_ID)))
	{
		perror("ftok failed");
		return NULL;
	}
	
	_memSize += sizeof(SharedManager) + _queueSize + _syncSize;
	
	if(-1==(sid = shmget(key,_memSize ,IPC_CREAT|PERMISSION)))
	{
		perror("shmget failed");
		return NULL;
	}
	
	if((void*)-1== (pShared = shmat(sid,NULL,0)))
	{
		perror("shmat failed");
		return NULL;
	}
	
	pShared->m_sid = sid;
	pShared->m_syncOffset =  sizeof(SharedManager);
	pShared->m_queueOffset = pShared->m_syncOffset + _syncSize;
	pShared->m_messagesOffset = pShared->m_queueOffset + _queueSize;
	
	return pShared;
	
}

SharedManager* SharedManager_Connect(const char* _name)
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

void* SharedManager_GetSyncAddress(SharedManager* _pShared)
{
	return OFFSET_TO_ADDRESS(_pShared,_pShared->m_syncOffset);
}

void* SharedManager_GetQueueAddress(SharedManager* _pShared)
{
	return OFFSET_TO_ADDRESS(_pShared,_pShared->m_queueOffset);
}

void* SharedManager_GetMessagesAddress(SharedManager* _pShared)
{
	return OFFSET_TO_ADDRESS(_pShared,_pShared->m_messagesOffset);
}

int SharedManager_Destroy(SharedManager* _pShared, int _isCreator)
{
	int err;
	
	assert(NULL != _pShared);
	
	if(_isCreator)
	{
		err = shmctl(_pShared->m_sid,IPC_RMID,NULL);
		if(-1 == err)
		{
			perror("shmctl failed");
			return err;
		}
	}
	
	err = shmdt(_pShared);
	if(-1 == err)
	{
		perror("shmdt failed");
		return err;
	}
	
	
	return 0;
}
