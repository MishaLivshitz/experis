#ifndef VECTOR_H
#define VECTOR_H
/**
 * vector.h
 *		Vector is array abstraction
 *			Grow and Reduce on demand
 *			Indexed from 1
 */
#include <stddef.h>		/* size_t */

#include "ADTItem.h"

typedef struct Vector Vector;

typedef enum Vector_Result {
	 VECTOR_SUCCESS					/**< operation OK */
	,VECTOR_NOT_INITIALIZED			/**< vector is not initialized */
	,VECTOR_INVALID_ARGUMENT		/**< invalid argument passed */
	,VECTOR_BAD_ALLOC				/**< allocation error */
	,VECTOR_UNDERFLOW				/**< nothing to remove */
	,VECTOR_OVERFLOW				/**< no space to add */
	,VECTOR_WRONG_INDEX				/**< item does not exists */
} Vector_Result;


/**
 * Create/Destroy
 * @brief	Create/Destroy new vector container
 * 
 * @param [in]	_initialSize	- initial size of vector
 * @param [in]	_extendSize		- extend size (for grow/reduce)
 * 
 * @return		pointer to a new vector container,
 * 				NULL if error
 * 
 * @warning		both _initialSize and _extendSize cannot be zero
 */
Vector*	Vector_Create(size_t _initialSize, size_t _extendSize);

void Vector_Destroy(Vector* _vector,AdtItemDestroy _destroyFunc);

/**
 * Add/Delete
 * @brief	add or remove element at the far end
 * 
 * @param [in]	_vector:	the container created in Vector_Create
 * @param [in]	_value:		the value to add to Vector
 * @param [out]	_pValue:	the place to receive the deleted item
 *			if NULL - no value will be returned
 * 
 * @return 	
 * 		VECTOR_SUCCESS
 * 		VECTOR_NOT_INITIALIZED
 * 		VECTOR_BAD_ALLOC
 * 		VECTOR_OVERFLOW
 * 		VECTOR_UNDERFLOW
 */
Vector_Result	Vector_Add(Vector* _vector, AdtItem _value);

Vector_Result	Vector_Delete(Vector* _vector, AdtItem *_pValue);

/**
 * Accessors
 * @brief	retrieve or update value at specified position
 * 
 * @param [in]	_vector:	the container created in Vector_Create
 * @param [in]	_index:		the index of the item
 * @param [in]	_value:		the new value to set to item
 * @param [out]	_pValue:	the place to receive the item
 *			if NULL - no value will be returned
 * 
 * @return 	
 * 		VECTOR_SUCCESS
 * 		VECTOR_NOT_INITIALIZED
 * 		VECTOR_WRONG_INDEX
 */
Vector_Result	Vector_Set(Vector* _vector, size_t _index, AdtItem _value);

Vector_Result	Vector_Get(Vector* _vector, size_t _index, AdtItem *_pValue);

/**
 * @brief	retrieve Vector info
 * 		_Size is current number of elements
 * 		_Capacity is current size of allocated storage
 *
 * @warning		result is undefined for uninitialized vector
 */
size_t			Vector_Capacity(Vector* _vector);
size_t			Vector_Size(Vector* _vector);

/**
* @brief this method activate the actionfunc on each item of a vector
*
* @params:
*	_vector: pointer to vector container
*	_actionFunc: the action function
*	_context: context to the action function
*
* @attention 	The action function return TRUE when the action is done
* @return index of some item if needed 0 if no index is needed and FOR_EACH_ERROR when error
*/

int VectorForEach(Vector* _vector,AdtItemAction _actionFunc,void* _context);

#endif /* VECTOR_H */
