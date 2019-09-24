#ifndef __MYMALLOC_H_
#define __MYMALLOC_H_
/**
 * @brief : 	Continuous memmory allocator
 * Allocates chunks of different sizes from specified user buffer.
 * Uses "FirstFit" match method
 *
 * @author : Alex Katz  (alexanderk@experis.co.il)
 * 	Created:	17/01/2012
 * 	Updated:	20/01/2019	32/64 bit + documentation
 */

#include <stddef.h>

/**
 * @brief  :	Initializes the memmory allocator
 * @params :	_membuf - the memory buffer to manage
 * 				_nBytes - size of the memory buffer
 *
 * returns:
 * 		NULL on error, aligned memory buffer on success
 */
void*	MyMallocInit(void* _membuf, size_t _nBytes);

/**
 * @brief  :	Allocate memory chunk of specified size.
 * @params :	_membuf - the memory buffer returned from MyMallocInit
 * 				_nBytes - the size of the chunk
 * returns:
 * 		NULL on error, chunk of requested size (at least) on success
 */
void*	MyMalloc(void* _membuf, size_t _nBytes);

/**
 * @brief  :	Free previously allocated memory chunck
 * @params :	_membuf - the memory chunk returned from MyMalloc
 */
void	MyFree(void* _ptr);

#ifdef  DEBUG
/* Debugging support functions */
void	MyMallocPrint(void* _membuf);
#endif /* DEBUG */

#endif /* __MYMALLOC_H_ */
