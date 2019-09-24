#ifndef __VECTOR__H__
#define __VECTOR__H__

#include<stdio.h>
#include<stdlib.h>
#include "ADTErr.h"

#define VECTOR_CREATION_FAILED NULL
#define MEGIC_NUM_AVTICE 0xdefdef
#define MEGIC_NUM_NOT_ACTIVE 0xdeaddef

#define FOR_EACH_ERROR -1

typedef struct Vector Vector;
typedef struct Vector* VectorPtr;
typedef int (*CallBackPtr)(void* item,void* context);
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
VectorPtr VectorCreate(size_t _initialSize, size_t _extentionsBlockSize);

/*
This method destroys a vector

params:
	 _vectorPtr: pointer to vector container
	 _action: pointer to a function from the user
	 _context: for user uses;

*/
void VectorDestroy(VectorPtr _vectorPtr,CallBackPtr _action,void* _context);

/*
This method inserts an item into the top of the vector

params:
	_vectorPtr: pointer to vector container
	_item : an item to add

return ERR_OK when succes else return ERR_REALLOCATION_FAILED or ERR_NOT_INITIALIZED
*/

ADTErr VectorAdd(VectorPtr _vectorPtr, void* _item);

/*This method deletes an item from the top of the vector

params:
	_vectorPtr: pointer to vector container
	_item : a place to return the deleted item

if _item == NULL no value will be returned

return ERR_OK when succes else return ERR_REALLOCATION_FAILED or ERR_NOT_INITIALIZED
*/
ADTErr VectorDelete(VectorPtr _vectorPtr, void** _item);

/*
This method get an item from the vector in specific index;

params:
	_vectorPtr: pointer to vector container
	_index: index of an item
	_item : a place to return the wanted item
	
return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_WRONG_INDEX or ERR_NULL_POINTER
*/
ADTErr VectorGet(const VectorPtr _vectorPtr,size_t _index, void** _item);

/*
This method get an item from the vector in specific index;

params:
	_vectorPtr: pointer to vector container
	_index: index of an item
	_item : an item to set

return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_WRONG_INDEX
*/
ADTErr VectorSet(VectorPtr _vectorPtr,size_t _index, void* _item);
/*
This method return the current number of items

params:
	_vectorPtr: pointer to vector container
	_item : a place to return the number of items

return ERR_OK when succes else return ERR_NOT_INITIALIZED or ERR_UNDERFLOW or ERR_NULL_POINTER
*/

ADTErr VectorItemsNum(const Vector* _vectorPtr, size_t* _numOfitems);

/*
This method copy a vector to other vector 

params:
	_vecSource: source vector
	_vecDest: destination vector

if _vecDest is NULL a new Vector will be created!

The vectors must be with the same size of items before the copy

returns pointer to vector when succes else return NULL
*/

Vector* VectorCopy(Vector* _vecSource, Vector* _vecDest);

/*
this method activate the actionfunc on each item of a vector

params:
	_vec: pointer to vector container
	 _actionFunc: the action function

The action function return TRUE when the action is done
return index of some item if needed 0 if no index is needed and FOR_EACH_ERROR when error
*/
int VectorForEach(VectorPtr _vec,CallBackPtr _actionFunc,void* _context);

/*
Method for debuggin uses. prints the vector items 

params:
	_vectorPtr: pointer to vector container
*/
void VectorPrint(const VectorPtr _vectorPtr,CallBackPtr _actionFunc,void* _context);


#endif

