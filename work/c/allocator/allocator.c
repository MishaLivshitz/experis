#include "allocator.h"
#include <assert.h>


typedef struct node
{
	void *m_next;
	
}Node;

struct memPool
{
	Node m_head;
	size_t m_unitSize;
};

static void InitPool(MemPool_t* _pool,size_t _unitSize,size_t _numOfNodes)
{
	void* curr;

	assert(NULL!=_pool);

	_pool->m_head.m_next = _pool + 1;
	_pool->m_unitSize = _unitSize;
	curr = _pool->m_head.m_next;
	
	while(_numOfNodes - 1)
	{
		((Node*)curr)->m_next = (byte*)curr + _unitSize;
		curr = ((Node*)curr)->m_next;
		--_numOfNodes;
	}

	((Node*)curr)->m_next = NULL;
	
}

MemPool_t* CreatePool(size_t _unitSize,size_t _numOfNodes)
{

	size_t memSize;	
	MemPool_t* pool;
	
	if(0 == _unitSize || 0 == _numOfNodes )
	{
		return NULL;
	}

	if(_unitSize < sizeof(Node))
	{
		_unitSize = sizeof(Node);
	}

	memSize = _unitSize*_numOfNodes;

	if(NULL == (pool = (MemPool_t*)calloc(1,sizeof(MemPool_t) + memSize)))
	{
		return NULL;
	}

	InitPool(pool,_unitSize,_numOfNodes);
	
	return pool;
}

void* MyMalloc(MemPool_t* _pool)
{
	void* newMem = NULL;
	
	if(NULL == _pool || NULL == _pool->m_head.m_next)
	{
		return NULL;
	}

	newMem = _pool->m_head.m_next;
	_pool->m_head.m_next=((Node*)(_pool->m_head.m_next))->m_next;

	return newMem;
}

void MyFree(MemPool_t* _pool ,void* _node)
{

	if(NULL == _pool)
	{
		return;
	}

	if(_pool->m_head.m_next == (_pool + 1))
	{
		return;
	}

	((Node*)_node)->m_next = _pool->m_head.m_next;
	_pool->m_head.m_next = _node;

	return;
}

void DestroyPool(MemPool_t* _pool)
{
	
	if(NULL==_pool)
	{
		return;
	}

	free(_pool);
}
