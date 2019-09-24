#ifndef QUEUE_H
#define QUEUE_H

/**
 * Queue.h
 *		Queue is FIFO ordered container
 *
 */


#include <stddef.h>		/* size_t */
#include "ADTItem.h"

typedef struct WaitableQueue WaitableQueue;

typedef enum WaitableQueue_Result {
	 QUEUE_SUCCESS				/**< operation OK */
	,QUEUE_NOT_INITIALIZED		/**< Queue is not initialized */
	,QUEUE_INVALID_ARGUMENT		/**< invalid argument passed */
	,QUEUE_UNDERFLOW			/**< nothing to remove */
	,QUEUE_OVERFLOW				/**< no space to add */
} WaitableQueue_Result;


/**
 * Create/Destroy
 * @brief	Create/Destroy new Queue container
 * 
 * @param [in]	_capacity		- maximum size of the queue
 * 
 * @return		pointer to a new Queue container,
 * 				NULL if error
 */
WaitableQueue*	WaitableQueue_Create(size_t _capacity);

void	WaitableQueue_Destroy(WaitableQueue* _queue);

/**
 * Enque/Deque
 * @brief	add or remove element at the far end
 * 
 * @param [in]	_queue		- pointer to Queue which holds the pointer to the array of items
 *
 * @param [in]	_item		- value to be added to queue
 * 
 * @param [in]	_pValue		- pointer to variable that receives item
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
WaitableQueue_Result	WaitableQueue_Enque(WaitableQueue* _q, AdtItem _item);

WaitableQueue_Result	WaitableQueue_Deque(WaitableQueue* _q, AdtItem *_pValue);

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
int	WaitableQueue_IsEmpty(const WaitableQueue* _q);
size_t	WaitableQueue_Size		(const WaitableQueue* _q);

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

#endif /* QUEUE_H */
