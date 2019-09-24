#ifndef __VECTOR__H__
#define __VECTOR__H__

#include<stdio.h>
#include<stdlib.h>
#include "ADTErr.h"

#define VECTOR_CREATION_FAILED NULL
#define MEGIC_NUM_AVTICE 0xdefdef
#define MEGIC_NUM_NOT_ACTIVE 0xdeaddef

typedef struct Vector Vector;
typedef struct Vector* VectorPtr;

typedef enum {
	INCRESE_FLAG,
	DECRESE_FLAG
}ResizeFlag;

/*
This method creates the Vector container

params:
	_initialSize: initial size
	_extentionsBlockSize: extention size block for reallocation

returns pointer to vector when succes else return VECTOR_CREATION_FAILED
*/
extern VectorPtr VectorCreate(size_t _initialSize, size_t _extentionsBlockSize);

/*
This method creates the Vector from a binary file

params:
	_fileName: file name
	_extentionsBlockSize: extention size block for reallocation

returns pointer to vector when succes else return VECTOR_CREATION_FAILED
*/
extern VectorPtr VectorCreateFromBinary(char* const _fileName);

/*
This method destroys a vector

params:
	 _vectorPtr: pointer to vector container

ATTENTION: make sure the set to NULL _vectorPtr from the calling method after destroying
*/
extern void VectorDestroy(VectorPtr _vectorPtr);

/*
This method inserts an item into the top of the vector

params:
	_vectorPtr: pointer to vector container
	_item : an item to add

return ERR_OK when succes else return ERR_REALLOCATION_FAILED or ERR_NOT_INITIALIZED
*/

extern ADTErr VectorAdd(VectorPtr _vectorPtr, int _item);

/*This method deletes an item from the top of the vector

params:
	_vectorPtr: pointer to vector container
	_item : a place to return the deleted item

if _item == NULL no value will be returned

return ERR_OK when succes else return ERR_REALLOCATION_FAILED or ERR_NOT_INITIALIZED
*/
extern ADTErr VectorDelete(VectorPtr _vectorPtr, int* _item);

/*
This method get an item from the vector in specific index;

params:
	_vectorPtr: pointer to vector container
	_index: index of an item
	_item : a place to return the wanted item
	
return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_WRONG_INDEX or ERR_NULL_POINTER
*/
extern ADTErr VectorGet(const VectorPtr _vectorPtr,size_t _index, int* _item);

/*
This method get an item from the vector in specific index;

params:
	_vectorPtr: pointer to vector container
	_index: index of an item
	_item : an item to set

return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_WRONG_INDEX
*/
extern ADTErr VectorSet(VectorPtr _vectorPtr,size_t _index, int _item);
/*
This method return the current number of items

params:
	_vectorPtr: pointer to vector container
	_item : a place to return the number of items

return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_UNDERFLOW or ERR_NULL_POINTER
*/

extern ADTErr VectorItemsNum(const VectorPtr _vectorPtr, size_t* _numOfitems);

/*
prints the vector items into binary file

params:
	_vectorPtr: pointer to vector container
	_fileName: file name
return number of printed items when succes else return ERR_NOT_INITIALIZED or ERR_OPEN_FILE_FAILED
*/
extern int VectorPrintToBin(const VectorPtr _vectorPtr, char* const _fileName);

/*
This method copy a vector to other vector 

params:
	_vecSource: source vector
	_vecDest: destination vector

if _vecDest is NULL a new Vector will be created!

The vectors must be with the same size of items before the copy

returns pointer to vector when succes else return NULL
*/
Vector* VectorCopy(Vector* _vecSource,Vector* _vecDest);
/*
Method for debuggin uses. prints the vector items 

params:
	_vectorPtr: pointer to vector container
*/
extern void VectorPrint(const VectorPtr _vectorPtr);


#endif

