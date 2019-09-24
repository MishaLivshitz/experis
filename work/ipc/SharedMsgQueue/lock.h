/*
 * This module responsible for managing the synchronization mechanism
 * 
 * Author: Michael Livshitz
 * 
 * Modified: 11.6.19
 * 
 * */

#ifndef LOCK_H_
#define LOCK_H_

#include <stddef.h>

typedef struct Lock Lock;

typedef enum
{
	
	COND_FREE,
	COND_OCCUPIED
	
}Cond_Type;

/**
 * 
 * @brief			A class method to return the size of the data structure	
 * 
 * @param			No params
 * 
 * @return 			Size of the data structure
 * 
 * */
 
size_t 		Lock_AllocSize();

/**
 * 
 *	@brief		This method initializing the sync object
 * 
 * 	@param		_sync: pointer to sync object 
 * 
 * 	@return 	pointer to initialized sync object
 * 
 */

Lock* 		Lock_Init(Lock* _sync);

/**
 * @brief		destroy the object
 * 
 * @param		_sync: pointer to sync object 
 * 
 * */

void 		Lock_Destroy(Lock* _sync);

/**
 * @brief		lock the mutex
 * 
 * @param		_sync: pointer to sync object 
 * 
 * */

void 		Lock_MtxLock(Lock* _sync);
/**
 * @brief		unlock the mutex
 * 
 * @param		_sync: pointer to sync object 
 * 
 * */

void		Lock_MtxUnlock(Lock* _sync);
/**
 * @brief		wait for condition variable
 * 
 * @param		_sync: pointer to sync object 
 * 
 * */

void 		Lock_CondWait(Lock* _sync);
/**
 * @brief		signal to condition variable
 * 
 * @param		_sync: pointer to sync object 
 * 
 * */

void		Lock_CondSignal(Lock* _sync);


#endif
