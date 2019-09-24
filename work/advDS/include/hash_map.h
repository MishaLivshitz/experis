#ifndef HASHMAP_H
#define HASHMAP_H

/**
 *  @file hash_map.h
 *  @brief Generic Hash map of key-value pairs implemented with open addressing.
 *
 *  @details  The hash map (sometimes called dictionary or associative array)
 *  is a set of distinct keys (or indexes) mapped (or associated) to values.
 *  size of allocated table will be the nearest prime number greater than requested capacity.
 *
 *  @author Muhammad Zahalqa  (MuhammadZ@experis.co.il)
 * 			Alex Katz - adjust to abridged syllabus
 *
 *  @bug No known bugs!
 */

#include <stddef.h>  /* size_t */

typedef struct HashMap HashMap;

typedef enum Map_Result {
	MAP_SUCCESS = 0,
	MAP_UNINITIALIZED_ERROR, 		/**< Uninitialized map error 	*/
	MAP_KEY_NULL_ERROR, 			/**< Key was null 				*/
	MAP_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 		*/
	MAP_KEY_NOT_FOUND_ERROR, 		/**< Key not found 				*/
	MAP_ALLOCATION_ERROR, 			/**< Allocation error 	 		*/
	MAP_OVERFLOW_ERROR				/**< Map is full error			*/
} Map_Result;


typedef size_t (*HashFunction)(const void* _key);

typedef int (*KeyEqualityFunction)(const void* _firstKey, const void* _secondKey);
typedef int	(*KeyValueActionFunction)(const void* _key, void* _value, void* _context);

/**
 * @brief Create a new hash map with given capcity and key characteristics.
 * @param [in] _capacity - Expected max capacity
 * 						  actual capacity will rounded to nearest larger prime number.
 * @param [in]	_hashFunc - hashing function for keys
 * @param [in]	_keysEqualFunc - equality check function for keys.
 * @return newly created map or null on failure
 */
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, KeyEqualityFunction _keysEqualFunc);


/**
 * @brief destroy hash map and set *_map to null
 * @param [in] _map : map to be destroyed
 * @param [optional] _keyDestroy : pointer to function to destroy keys
 * @param [optional] _valDestroy : pointer to function to destroy values
 * @details optionally destroy all keys and values using user provided functions
 */
void HashMap_Destroy(HashMap* _map, void (*_keyDestroy)(void*), void (*_valDestroy)(void*));

/**
 * @brief Adjust map capacity and rehash all key/value pairs
 * @param [in] _map - exisiting map
 * @param [in] _newCapacity - new capacity shall be rounded to nearest larger prime number.
 * @return MAP_SUCCESS or MAP_ALLOCATION_ERROR
 */
Map_Result HashMap_Rehash(HashMap *_map, size_t _newCapacity);

/**
 * @brief Insert a key-value pair into the hash map.
 * complexity(?)
 * @param [in] _map - Hash map to insert to, must be initialized
 * @param [in] _key - key to serve as index
 * @param [in] _value - the value to associate with the key
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_DUPLICATE_ERROR	if key alread present in the map
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_UNINITIALIZED_ERROR
 *
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value);


/**
 * @brief Remove a key-value pair from the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the map
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to foind key
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 *
 * @warning key must be unique and distinct
 */
Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void* *_pKey, void* *_pValue);


/**
 * @brief Find a value by key
 * complexty(?)
 * @param[in] _map - Hash map to use, must be initialized
 * @param[in] _searchKey - key to serve as index for search
 * @param[out] _pValue - pointer to variable that will get the value assoiciated with the search key.
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 *
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue);


/**
 * @brief Get number of key-value pairs inserted into the hash map / size of the hash table
 * 
 * @warning complexity can be O(?)
 */
size_t HashMap_Size(const HashMap* _map);
size_t HashMap_Capacity(const HashMap* _map);

/** @brief Retrieve statistics
 * @param [out] _averageCollisions == all collisions/all operations
 * @param [out] _maxCollisionsEver : max colisions in one operation
 */
Map_Result HashMap_Statistics(const HashMap* _map, size_t *_maxCollisionsEver, float *_averageCollisions);

/**
 * @brief Iterate over all key-value pairs in the map and call a function for each pair
 * The user provided KeyValueActionFunction will be called for each element.
 * Iteration will stop if the called function returns a zero for a given pair
 *
 * @param[in] _map - Hash map to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
 */
size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context);

#endif /* HASHMAP_H */
