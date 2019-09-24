#include "queue.h"
#include <stdlib.h>
#include <stddef.h>  /*size_t*/
#include <stdio.h>
#include "ADTItem.h"
#include "MyMalloc.h"

#define ACTIVE_MAGIC_NUM 			0xdefdef

#define IS_VALID(Q) 				((Q) && (Q)->m_magicNum==ACTIVE_MAGIC_NUM)
#define QUEUE_DATA(Q)				((Pair*)((Q)+1))

typedef struct 
{
	unsigned short 		m_size;
	size_t				m_offset;
	
}Pair;

struct Queue{
	
	int m_magicNum;
	size_t m_capacity;
	size_t m_nitems;
	size_t m_tail;
	size_t m_head;	
};

size_t Queue_AllocSize(size_t _capacity)
{
	return sizeof(Queue) + sizeof(Pair)*_capacity;
}

Queue*	Queue_Init(void* _memBuff, size_t _capacity)
{
	Queue* queue = (Queue*)_memBuff;

	if(0 == _capacity)
	{
		return NULL;
	}	
	
	queue->m_capacity =_capacity;
	queue->m_head = 0;
	queue->m_tail = 0;
	queue->m_nitems = 0;
	queue->m_magicNum = ACTIVE_MAGIC_NUM;
	
	return queue;
}

void Queue_Destroy(Queue* _queue)
{
	
	if(!IS_VALID(_queue))
	{
		return;
	}
	
	_queue->m_magicNum = -1;
}

Queue_Result Queue_Enque(Queue* _queue, size_t _size, size_t _offset)
{
	Pair* qeueuData;
	
	if(!IS_VALID(_queue))
	{
		return QUEUE_NOT_INITIALIZED;
	}
	
	if(_queue->m_capacity == _queue->m_nitems)
	{
		return QUEUE_OVERFLOW;
	}
	
	qeueuData = QUEUE_DATA(_queue);
	
	qeueuData[_queue->m_tail].m_size = _size;
	qeueuData[_queue->m_tail].m_offset = _offset;
	
	_queue->m_tail++;
	_queue->m_tail %= _queue->m_capacity;
	_queue->m_nitems++;

	return QUEUE_SUCCESS;
}

Queue_Result Queue_Deque(Queue* _queue, size_t _bufSize, size_t* _bytesRead, size_t* _offset)
{
	Pair* qeueuData;
	
	if(!IS_VALID(_queue))
	{
		return QUEUE_NOT_INITIALIZED;
	}
	
	if(!_bytesRead || !_offset)
	{
		return QUEUE_INVALID_ARGUMENT;
	}
		
	if(_queue->m_nitems==0)
	{
		return QUEUE_UNDERFLOW;
	}
	
	qeueuData = QUEUE_DATA(_queue);
	
	*_offset = qeueuData[_queue->m_head].m_offset;
	*_bytesRead = qeueuData[_queue->m_head].m_size;
	
	if(*_bytesRead > _bufSize)
	{
		return -1;
	}
	
	_queue->m_head++;
	_queue->m_head %= _queue->m_capacity;
	_queue->m_nitems--;

	return QUEUE_SUCCESS;
}


int	Queue_IsEmpty(const Queue* _queue)
{
	if(!IS_VALID(_queue))
	{
		return 0;
	}

	return _queue->m_nitems==0;
}

int Queue_IsFull(const Queue* _queue)
{
	if(!IS_VALID(_queue))
	{
		return 0;
	}

	return _queue->m_nitems == _queue->m_capacity;
}

/*
size_t	Queue_Capacity(const Queue* _queue)
{
	if(!IS_VALID(_queue))
	{
		return 0;
	}
	
	return _queue->m_capacity;
}

size_t	Queue_Size(const Queue* _queue)
{
	if(!IS_VALID(_queue))
	{
		return 0;
	}
	
	return _queue->m_nitems;
}
*/
