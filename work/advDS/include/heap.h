#ifndef __HEAP_H__
#define __HEAP_H__

/** 
 * @brief Create a Binary heap generic data type over a generic vector data type.
 * @author Author MuhammadZ (muhammadz@experis.co.il)
 * @date  modified 05.05.2019 - adjust to abridged DS syllabus 
 * @see https://en.wikipedia.org/wiki/Binary_heap 
 */ 

#include "ADTItem.h"
#include "vector.h"

typedef struct Heap Heap;

typedef enum Heap_Result {
	 HEAP_SUCCESS = 0
	,HEAP_NOT_INITIALIZED
	,HEAP_ALLOCATION_FAILED
	,HEAP_OVERFLOW
	,HEAP_UNDERFLOW
} Heap_Result;


/**  
 * @brief Apply a heap policy over a Vector container.  
 * @param[in] _vector - Vector that hold the elements, must be initialized
 * @param[in] _pfComp - A comparator to be used to compare elements 
 * @return Heap * - on success
 * @retval NULL on fail 
 *
 * @warning allocating and freeing the underlying vector is user responsibility. 
 * as long as vector is under the heap control, user should not access the vector directly
 */
Heap* Heap_Build(Vector* _vector, AdtItemCompare _pfComp);

/**  
 * @brief Deallocate a previously allocated heap
 * Frees the heap but not the underlying vector  
 * @param[in] _heap - Heap to be deallocated.  On success will be nulled.
 * @return Underlying vector
 */
Vector* Heap_Destroy(Heap* _heap);

/**  
 * @brief Add an element to the Heap preserving heap property.  
 * @param[in] _heap - Heap to insert element to.
 * @param[in] _element - Element to insert. can't be null
 * @return success or error code 
 * @retval HEAP_OK  on success
 * @retval HEAP_NOT_INITIALIZED  error, heap not initilized
 * @retval HEAP_ALLOCATION_FAILED error, heap could not reallocate underlying vector 
 */
Heap_Result Heap_Insert(Heap* _heap, AdtItem _element);

/**  
 * @brief Peek at element on top of heap without extracting it.  
 * @param[in] _heap - Heap to peek at.
 * @return pointer to element, can be null if heap is empty or on error
 */
const AdtItem Heap_Peek(const Heap* _heap);

/**  
 * @brief Extract element on top of heap and remove it.  
 * @param[in] _heap - Heap to extract from.
 * @return pointer to element, can be null if heap is empty. 
 */
AdtItem Heap_Extract(Heap* _heap);

/**  
 * @brief Get the current size (number of elements) in the heap.  
 * @param[in] _heap - the Heap.
 * @return number of elements or zero if empty. 
 */
size_t Heap_Size(const Heap* _heap);

/**  
 * @brief Iterate over all elements  in the heap from top to bottom.
 * @details The user provided ActionFunction _act will be called for each element. 
 * iteration will stop at the first element wehere _act(e) returns zero
 * @param[in] _heap - Heap to iterate over.
 * @param[in] _act - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
 */
size_t Heap_ForEach(const Heap* _heap, AdtItemAction _act, void* _context);


/**  
 * @brief Sort a given vector of elments using a heap sort.
 * @param[in] _vector - vector to sort.
 * @param[in] _pfComp - comparator
 */
void Heap_Sort(Vector* _vec, AdtItemCompare _pfComp);


#endif /* HEAP_H */
