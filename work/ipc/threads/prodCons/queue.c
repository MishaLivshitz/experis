#include "queue.h"
#include <stdlib.h>
#include <stddef.h>  /*size_t*/
#include <stdio.h>
#include "ADTItem.h"

#define ACTIVE_MAGIC_NUM 0xdefdef

#define IS_VALID(Q) ((Q) && (Q)->m_magicNum==ACTIVE_MAGIC_NUM)

struct Queue{
	
	int m_magicNum;
	void** m_vec;
	size_t m_capacity;
	size_t m_nitems;
	size_t m_tail;
	size_t m_head;	
};

Queue*	Queue_Create(size_t _capacity)
{
	Queue* queue;
	
	if(0 == _capacity)
	{
		return NULL;
	}	

	if(NULL == (queue = (Queue*)calloc(1,sizeof(Queue))))
	{
		return NULL;
	}
	
	if(NULL == (queue->m_vec = (void**)calloc(_capacity,sizeof(void*))))
	{
		free(queue);
		return NULL;	
	}

	queue->m_capacity =_capacity;
	queue->m_magicNum = ACTIVE_MAGIC_NUM;
	
	return queue;
}

void Queue_Destroy(Queue* _queue, AdtItemDestroy _pIDF)
{

	AdtItem item;
	
	if(!IS_VALID(_queue))
	{
		return;
	}
	
	while(!Queue_IsEmpty(_queue))
	{	
		Queue_Deque(_queue, &item);
		if(_pIDF)
		{
			_pIDF(item);
		}
	}
	
	_queue->m_magicNum = -1;
	free(_queue);
}

Queue_Result Queue_Enque(Queue* _queue, AdtItem _item)
{
	if(!IS_VALID(_queue))
	{
		return QUEUE_NOT_INITIALIZED;
	}
	
	if(_queue->m_capacity==_queue->m_nitems)
	{
		return QUEUE_OVERFLOW;
	}

	_queue->m_vec[_queue->m_tail++] = _item;
	_queue->m_tail %= _queue->m_capacity;
	_queue->m_nitems++;

	return QUEUE_SUCCESS;
}

Queue_Result Queue_Deque(Queue* _queue, AdtItem *_pValue)
{

	if(!IS_VALID(_queue))
	{
		return QUEUE_NOT_INITIALIZED;
	}
		
	if(_queue->m_nitems==0)
	{
		return QUEUE_UNDERFLOW;
	}
	
	if(NULL != _pValue)
	{
		*_pValue = _queue->m_vec[_queue->m_head];
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



int QueueForEach(Queue* _queue,AdtItemAction _actionFunc,void* _context)
{
	int headIndex;
	int numOfItems;

	if(!IS_VALID(_queue))
	{
		return QUEUE_NOT_INITIALIZED;
	}
	headIndex = _queue->m_head;
	
	numOfItems = _queue->m_nitems;
	if(0 < numOfItems)
	{
		
		while(numOfItems>0)
		{
			if(_actionFunc(_queue->m_vec[headIndex],_context))
			{
				return headIndex;
			}
			headIndex = ++headIndex % _queue->m_capacity;
			--numOfItems;
		}
	}

	return headIndex;
}
