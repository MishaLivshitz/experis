/*
 * Queue.h
 *		Queue is FIFO ordered container
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>		/* size_t */
#include "ADTItem.h"

typedef struct Queue Queue;

typedef enum Queue_Result {
	 QUEUE_SUCCESS				/**< operation OK */
	,QUEUE_NOT_INITIALIZED		/**< Queue is not initialized */
	,QUEUE_INVALID_ARGUMENT		/**< invalid argument passed */
	,QUEUE_UNDERFLOW			/**< nothing to remove */
	,QUEUE_OVERFLOW				/**< no space to add */
} Queue_Result;


/**
 * @brief 		A class method to return the size of the data structure	
 * 
 * @param		_capacity		- maximum size of the queue	
 * 
 * */
 
size_t Queue_AllocSize(size_t _capacity);
/**
 * Create/Destroy
 * @brief	Create/Destroy new Queue container
 * 
 * @param [in]	_capacity		- maximum size of the queue
 * @param [in]  _membuf			- memory buffer for the queue
 * 
 * @return		pointer to a new Queue container,
 * 				NULL if error
 */
 

Queue*	Queue_Init(void* _memBuff, size_t _capacity);

void	Queue_Destroy(Queue* _queue);

/**
 * Enque/Deque
 * @brief	add or remove element at the far end
 * 
 * @param [in]	_queue		- pointer to Queue which holds the pointer to the array of items
 *
 * @param [in]	_item		- value to be added to queue
 * 
 * @param [in]	_bytesRead	- place to return the data from item
 * 
 * @param [in]	_offset		- place to return the data from item
 * 
 *
 * @warning if _pValue is null no value will be returned
 * 
 * @return		Success after adding or removing data
 * 				Initialize Error if pointers to array are NULL
 *				Invalid if pointer to recieve value is NULL
 *				Overflow if extend block is 0 when capacity is full
 *				Underflow when removing data from an empty array
 * 
 */
Queue_Result Queue_Enque(Queue* _queue, size_t _size,size_t _offset);

Queue_Result Queue_Deque(Queue* _queue, size_t _bufSize, size_t* _bytesRead, size_t* _offset);

/**
 * @brief	retrieve Queue info
 * 			_Capacity is max number of elements
 * 			_Size is current number of elements
 * 			_IsEmpty/IsFull the Queue state
 *
 * @param [in]	pointer to Queue created
 *
 * @warning		result is undefined for uninitialized Queue
 */
int	Queue_IsEmpty(const Queue* _q);
int Queue_IsFull (const Queue* _q);
size_t	Queue_Capacity	(const Queue* _q);
size_t	Queue_Size		(const Queue* _q);

/**
* @brief this method activate the actionfunc on each item of a vector
*
* @params:
*	 _queue: pointer to vector container
*	 _actionFunc: the action function
*
* @attention 	The action function return TRUE when the action is done
* 
* @return index of some item if needed 0 if no index is needed and FOR_EACH_ERROR when error
*/

int QueueForEach(Queue* _queue,AdtItemAction _actionFunc,void* _context);
#endif /* QUEUE_H */
