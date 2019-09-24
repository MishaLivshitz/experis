/*
	This module responsible for implementing heap functionality
	Author: Michael Livshitz
	Date: 15/04/19

	gcc -ansi -pedantic -I ../include/ ../vector/vector.c *.c -g*/



#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "ADTErr.h"
#define FATHER(i) (i)/2-1
#define LEFT(i) (i)*2+1
#define RIGHT(i) (i)*2+2
#define MAX_LEFT_FATHER(x,y) (x)>(y)? MAX_LEFT:MAX_FATHER
#define MAX_RIGHT_FATHER(x,y) (x)>(y)? MAX_RIGHT:MAX_FATHER
#define MAX_LEFT_RIGHT(x,y) (x)>(y)? MAX_LEFT:MAX_RIGHT
#define MAGIC_NUM_ACTIVE 0xdefdef
#define MAGIC_NUM_INACTIVE 0xdeaddef

typedef enum
{
	MAX_FATHER,
	MAX_LEFT,
	MAX_RIGHT
}MaxNode;

typedef struct heap Heap;


/*
This method builds an heap from a given vector
	params:
		_vec: Vector pointer

return ERR_OK if success else return ERR_ALLOCATION_FAILED or ERR_NOT_INITIALIZED
*/

Heap* HeapBuild(Vector* _vec);

/*
This method destory an heap. The user is responsible to destroy the vector
	params:
		_heap: Heap pointer
*/
void HeapDestroy(Heap* _heap);

/*
This method insert an item to the heap

params:
		_heap: Heap pointer
		_data: data to insert

return ERR_OK if success else return ERR_NOT_INITIALIZED or ERR_REALLOCATION_FAILED
*/

ADTErr HeapInsert(Heap* _heap,int _data);

/*
This method return the max element of the heap via pointer

params:
		_heap: Heap pointer
		_data: a place to return data

return ERR_OK if success else return ERR_NOT_INITIALIZED
*/
ADTErr HeapMax(Heap* _heap,int* _data);

/*
This method return the max element of the heap via pointer and removes it from the heap

params:
		_heap: Heap pointer
		_data: a place to return data

if _data == NULL no value will be returned

return ERR_OK if success else return ERR_NOT_INITIALIZED
*/
ADTErr HeapExtractMax(Heap* _heap,int* _data);

/*
This method return the number of the items in the heap
params:
		_heap: Heap pointer

return number of items if success else ERR_NOT_INITIALIZED
*/

int HeapItemsNum(Heap* _heap);

/*
This method prints the heap elements
params:
		_heap: Heap pointer
*/
void HeapPrint(Heap* _heap);
