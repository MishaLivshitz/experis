#ifndef __STACK_H_
#define __STACK_H_	

#include "vector.h"

/*
This header resopnsible for decleration of all needed method to implement stack based on vector.h
Author: Michael Livshitz
Date: 07/04/2019
*/


typedef Vector Stack;

/*
Create the stack

params:
		_size: size
		_blockSize: extending block size

returns pointer to stack when succes else return VECTOR_CREATION_FAILED
*/
extern Stack* StackCreate(size_t _size, size_t _blockSize);


/*
This method destroys a stack

params:
	 _stack: pointer to stack container
*/

extern void StackDestroy(Stack* _stack);

/*
This method pushs an item into the top of the stack

params:
	_stack: pointer to stack container
	_item : an item to add

return ERR_OK when succes else return ERR_REALLOCATION_FAILED
*/
extern ADTErr StackPush(Stack* _stack, int _item);

/*This method deletes an item from the top of the stack

params:
	_stack: pointer to stack container
	_item : a place to return the poped item

return ERR_OK when succes else return ERR_REALLOCATION_FAILED or ERR_NULL_POINTER
*/
extern ADTErr StackPop(Stack* _stack, int* _item);

/*This method returns the item from the top of the stack but not pops it

params:
	_stack: pointer to stack container
	_item : a place to return the poped item

return ERR_OK when succes else return ERR_NULL_POINTER or ERR_NOT_INITIALIZED
*/

extern ADTErr StackTop(Stack* _stack, int* _item);
/*
This method checks if the stack is empty

params:
	_stack: pointer to stack container

return TRUE if empty and FALSE or ERR_NOT_INITIALIZED otherwise
*/
extern int StackIsEmpty(Stack* _stack);

/*
Method for debuggin uses. prints the stack items

params:
	_stack: pointer to stack container
*/
extern void StackPrint(Stack* _stack);

#endif
