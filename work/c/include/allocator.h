#ifndef __POOL_H
#define __POOL_H
#endif
#include<stdio.h>
#include<stdlib.h>
#include "ADTErr.h"
#include "UTestERR.h"

#define MAGIC_NUM_ACTIVE 0xdefdef
#define MAGIC_NUM_INACTIVE 0xdeaddef

/*gcc -ansi -pedantic -I ../include/ allocator.c allocatorApp.c -g*/

typedef struct memPool MemPool_t;
typedef char byte;



/*
This method creates a pool

params:
	_nodeSize: size of each node
	_numOfNodes: number of wanted nodes

return pointer to pool if success else return NULL
*/
MemPool_t* CreatePool(size_t _nodeSize,size_t _numOfNodes);

/*
This method destroy a pool
	params:
		_pool: pointer to pool
*/
void DestroyPool(MemPool_t* _pool);

/*
This method allocates memory from the pool to the user

	params:
		_pool: pointer to pool

return pointer to new node if succes else return NULL

*/
void* MyMalloc(MemPool_t* _pool);

/*
This method free memory and return it to the pool

	params:
		_pool: pointer to pool
		_node: the pointer to the freed memory
*/

void MyFree(MemPool_t* _pool ,void* _node);
