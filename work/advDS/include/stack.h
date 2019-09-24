#ifndef STACK_H
#define STACK_H

/**
 * Stack.h
 *		Stack is LIFO ordered container
 *
 */
#include <stddef.h>		/* size_t */

#include "ADTItem.h"

typedef struct Stack Stack;

typedef enum Stack_Result {
	 STACK_SUCCESS					/**< operation OK */
	,STACK_NOT_INITIALIZED			/**< vector is not initialized */
	,STACK_INVALID_ARGUMENT			/**< invalid argument passed */
	,STACK_BAD_ALLOC				/**< allocation error */
	,STACK_UNDERFLOW				/**< nothing to remove */
	,STACK_OVERFLOW					/**< no space to add */
} Stack_Result;


/**
 * Create/Destroy
 * @brief	Create/Destroy new vector container
 * 
 * @param[in]	_initialSize	- initial size of vector
 * @param[in]	_extendSize		- extend size (for grow/reduce)
 * 
 * @return		pointer to a new vector container,
 * 				NULL if error
 * 
 * @warning		both _initialSize and _extendSize cannot be zero
 */
Stack*	Stack_Create(size_t _initialSize, size_t _extendSize);

void	Stack_Destroy(Stack* _stack, AdtItemDestroy _destroyFunc);

/**
 * Push / Pop
 * @brief	add or remove element at the far end
 * 
 * @param[in]	_stack		- pointer to vector which holds the pointer to the array of ints
 *
 * @param[in]	_value		- value to be added to array
 * 
 *@param[in]	_*pvalue	- pointer to send value to before deletion
 *
 * @return		Success after adding or removing data
 * 				Initialize Error if pointers to array are NULL
 *				Invalid if pointer to recieve value is NULL
 *				Overflow if extend block is 0 when capacity is full
 *				Underflow when removing data from an empty array
 *				Realloc Error when recieving NULL pointer after realloc
 * 
 */
Stack_Result	Stack_Push(Stack* _stack, AdtItem _value);

Stack_Result	Stack_Pop(Stack* _stack, AdtItem *_pValue);
Stack_Result	Stack_Top(const Stack* _stack, AdtItem *_pValue);

/**
 * @brief	retrieve Stack info
 * 			_Size is current number of elements
 * 			_Capacity is current size of allocated storage
 *
 * @param[in]	pointer to vector created
 *
 * @warning		result is undefined for uninitialized vector
 */
size_t	Stack_Capacity(const Stack* _stack);
size_t	Stack_Size(const Stack* _stack);
int		Stack_IsEmpty(const Stack* _stack);

/**
* @brief this method activate the actionfunc on each item of a stack
*
* @params:
*	_vec: pointer to stack container
*	 _actionFunc: the action function
*
* @attention 	The action function return TRUE when the action is done
* @return index of some item if needed 0 if no index is needed and FOR_EACH_ERROR when error
*/

int StackForEach(Stack* _stack,AdtItemAction _actionFunc,void* _context);
#endif /* STACK_H */
