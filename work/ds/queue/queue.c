#include "queue.h"
#define ACTIVE_MEGIC_NUM 0xdefdef
#define INACTIVE_MEGIC_NUM 0xdeaddef

struct queue{
	
	int m_megic_num;
	int* m_vec;
	size_t m_size;
	size_t m_nitems;
	size_t m_tail;
	size_t m_head;	
};


Queue* QueueCreate(size_t _size)
{
	Queue* queue;
	
	if(0 == _size)
	{
		return NULL;
	}	

	if(NULL == (queue = (Queue*)malloc(sizeof(Queue))))
	{
		return NULL;
	}
	
	if(NULL == (queue->m_vec = (int*)malloc(sizeof(int)*_size)))
	{
		free(queue);
		return NULL;	
	}

	queue->m_size =_size;
	queue->m_nitems = 0;
	queue->m_tail = 0;
	queue->m_head = 0;
	queue->m_megic_num = ACTIVE_MEGIC_NUM;
	
	return queue;
}

void QueueDestroy(Queue* _queue)
{
	if(NULL==_queue || _queue->m_megic_num!=ACTIVE_MEGIC_NUM)
	{
		return;
	}
	_queue->m_megic_num = INACTIVE_MEGIC_NUM;
	free(_queue->m_vec);
	_queue->m_vec = NULL;
	free(_queue);
}

ADTErr QueueInsert(Queue* _queue, int _item)
{
	if(NULL==_queue || _queue->m_megic_num!=ACTIVE_MEGIC_NUM)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_queue->m_size==_queue->m_nitems)
	{
		return ERR_OVERFLOW;
	}

	_queue->m_vec[_queue->m_tail++] = _item;
	_queue->m_tail %= _queue->m_size;
	_queue->m_nitems++;

	return ERR_OK;
}

ADTErr QueueRemove(Queue* _queue, int* _item)
{

	if(NULL==_queue || _queue->m_megic_num!=ACTIVE_MEGIC_NUM)
	{
		return ERR_NOT_INITIALIZED;
	}
		
		if(_queue->m_nitems==0)
		{
			return ERR_UNDERFLOW;
		}

	*_item = _queue->m_vec[_queue->m_head++];
	_queue->m_head %= _queue->m_size;
	_queue->m_nitems--;

	return ERR_OK;

}

int QueueIsEmpty(Queue* _queue)
{
	if(NULL==_queue || _queue->m_megic_num!=ACTIVE_MEGIC_NUM)
	{
		return FALSE;
	}

	return _queue->m_nitems==0;
	
}
int QueuePrint(Queue* _queue)
{
	int headIndex;
	int numOfItems;
	int numOfPrintedItems=0;

	if(NULL==_queue || _queue->m_megic_num!=ACTIVE_MEGIC_NUM)
	{
		return ERR_NOT_INITIALIZED;
	}
	numOfItems = _queue->m_nitems;
	if(0 < numOfItems)
	{
		headIndex = _queue->m_head;
		while(numOfItems>0)
		{
			numOfPrintedItems += printf("%d ",_queue->m_vec[headIndex]);
			headIndex = ++headIndex % _queue->m_size;
			--numOfItems;
		}
	}

	printf("\n");
	return numOfPrintedItems/2;
}
