#ifndef _SHARED_MEM_
#define _SHARED_MEM_

typedef struct SharedManager SharedManager;

typedef enum
{
	SHARED_MEM_FULL = 0,
	SHARED_MEM_EMPTY,
	SHARED_MEM_SUCCESS,
	SHARED_MEM_BUFFER_TO_SMALL
	
}SharedManagerResult;


SharedManager* SharedManager_Create(const char* _name, size_t _memSize);

SharedManager* SharedManager_GetMem(const char* _name);

int SharedManager_Destroy(SharedManager* _pShared,int _isCreator);

SharedManagerResult SharedManager_Enqueue(SharedManager* _pShared, void* _buffer, size_t _bufSize);

SharedManagerResult SharedManager_Dequeue(SharedManager* _pShared, void* _buffer, size_t _bufSize, size_t* _bytesRead);

int SharedManager_IsEmpty(SharedManager* _pShared);

#endif
