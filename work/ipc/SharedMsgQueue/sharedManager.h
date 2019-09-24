/*
 * This module responsible for managing the shared memory offsets and provide the actual addresses
 * 
 * Author: Michael Livshitz
 * 
 * Modified: 11.6.19
 * 
 * */


#ifndef _SHARED_MEM_
#define _SHARED_MEM_

#include <stddef.h>

typedef struct SharedManager SharedManager;

typedef enum
{
	SHARED_MEM_FULL = 0,
	SHARED_MEM_EMPTY,
	SHARED_MEM_SUCCESS,
	SHARED_MEM_BUFFER_TOO_SMALL

}SharedManagerResult;

/**
 * @brief		This method creates the shared memory and initialized the offset table
 * 
 * @param		_name: 			Name to generate token
 * 				_memSize:		Total memory size for user uses
 * 				_queueSize: 	queue size provided by queue module
 * 				_syncSize:		sync size provided by lock module 	
 * 
 * @return		pointer to created and initialized shared memory
 * */
SharedManager* SharedManager_Create(const char* _name, size_t _memSize, size_t _queueSize, size_t _syncSize);

/**
 * 
 * @brief		This method connects to shared memory which was created with SharedManager_Create
 * 
 * @param		_name: 			Name to generate token
 * 
 * @return		pointer to created and initialized shared memory when success else NULL
 * */

SharedManager* SharedManager_Connect(const char* _name);

/**
 * 
 * @brief		This method destroy a shared memory which was created by SharedManager_Create
 * 
 * @param		_pShared: pointer to shared memory
 * 				_isCreator: boolean parameter which defines if the caller is the creator of the shared or not
 * 
 * @return		0 when success else return errno
 * */

int SharedManager_Destroy(SharedManager* _pShared, int _isCreator);

/**
 * @brief 		These methods return the actual address of the needed objects by their offset
 * 
 * @param		_pShared: pointer to shared memory
 * */
void* SharedManager_GetSyncAddress(SharedManager* _pShared);

void* SharedManager_GetQueueAddress(SharedManager* _pShared);

void* SharedManager_GetMessagesAddress(SharedManager* _pShared);

#endif
