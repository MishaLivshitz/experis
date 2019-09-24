#include "heap.h"


struct heap
{
	Vector* m_vec;
	size_t m_heapSize;
};

static void swap(Vector* _vec,int _a, int _b)
{
	int itemSon;
	int itemFather;
	
	VectorGet(_vec,_a,&itemSon); 
	VectorGet(_vec,_b,&itemFather);
	VectorSet(_vec,_a,itemFather);
	VectorSet(_vec,_b,itemSon);
	
}

static MaxNode FindMaxNode(Heap* _heap, int _fatherIndex)
{

	int itemSonLeft;
	int itemSonRight;
	int itemFather;
	MaxNode maxNode;
	
	VectorGet(_heap->m_vec,LEFT(_fatherIndex),&itemSonLeft);
	VectorGet(_heap->m_vec,_fatherIndex,&itemFather);
	maxNode = MAX_LEFT_FATHER(itemSonLeft,itemFather);

	if(RIGHT(_fatherIndex) < _heap->m_heapSize)
	{
		VectorGet(_heap->m_vec,RIGHT(_fatherIndex),&itemSonRight);
		if(MAX_FATHER == maxNode)
		{
			maxNode = MAX_RIGHT_FATHER(itemSonRight,itemFather);
		}
		else
		{
			maxNode = MAX_LEFT_RIGHT(itemSonLeft,itemSonRight);
		}
	}
	
	return maxNode;
}

static void heapify(Heap* _heap,int _fatherIndex)
{
	
	if(LEFT(_fatherIndex) > _heap->m_heapSize)
	{
		return;
	}
	
	switch(FindMaxNode(_heap,_fatherIndex))
	{
		case MAX_FATHER:
			break;

		case MAX_LEFT:
			swap(_heap->m_vec,_fatherIndex,LEFT(_fatherIndex));
			heapify(_heap, LEFT(_fatherIndex));
			break;

		case MAX_RIGHT:
			swap(_heap->m_vec,_fatherIndex,RIGHT(_fatherIndex));
			heapify(_heap, RIGHT(_fatherIndex));;
			break;
	}
	return;
}

static void BubbleUp(Heap* _heap,int _newIndex)
{
	int itemFather;
	int itemSon;
	
	VectorGet(_heap->m_vec,FATHER(_newIndex),&itemFather); 
	VectorGet(_heap->m_vec,_newIndex,&itemSon); 
	if(_newIndex==1 || itemFather>itemSon)
	{
		return;
	}

	swap(_heap->m_vec,FATHER(_newIndex),_newIndex);
	BubbleUp(_heap,FATHER(_newIndex));
	
	return;
}
Heap* HeapBuild(Vector* _vec)
{

	Heap* heap;
	int i,num;
	size_t itemsNum;
	
	if(ERR_OK != VectorItemsNum(_vec,&itemsNum) || NULL == (heap=(Heap*)malloc(sizeof(Heap))))
	{
		return NULL;
	}

	heap->m_vec = _vec;
	heap->m_heapSize = itemsNum;
	VectorGet(heap->m_vec,FATHER(itemsNum),&num); 
	printf("items=%d index=%ld",num,FATHER(itemsNum));
	while(FATHER(itemsNum))
	{
		heapify(heap, FATHER(itemsNum--));
	}
	HeapPrint(heap);
	
	return heap;
}

void HeapDestroy(Heap* _heap)
{
	size_t itemsNum;
	if(NULL == _heap || ERR_OK != VectorItemsNum(_heap->m_vec,&itemsNum))
	{
		return;
	}
	
	_heap->m_vec = NULL;
	free(_heap);
}

ADTErr HeapInsert(Heap* _heap,int _data)
{
	ADTErr status;

	if(NULL == _heap )
	{
		return ERR_NOT_INITIALIZED;
	}

	status = VectorAdd(_heap->m_vec,_data);
	if(ERR_OK==status)
	{
		++_heap->m_heapSize;
		BubbleUp(_heap, _heap->m_heapSize);
	}
	
	return status;
}

ADTErr HeapMax(Heap* _heap,int* _data)
{
	
	if(NULL == _heap)
	{
		return ERR_NOT_INITIALIZED;
	}

	return VectorGet(_heap->m_vec,1,_data);
}

ADTErr HeapExtractMax(Heap* _heap,int* _data)
{
	ADTErr status;

	if(NULL == _heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	swap(_heap->m_vec,1,_heap->m_heapSize);
	HeapPrint(_heap);
	status = VectorDelete(_heap->m_vec,_data);
	if(ERR_OK == status || ERR_REALLOCATION_FAILED==status)
	{
		--_heap->m_heapSize;
		heapify(_heap, 1);
	}

	return status;
}

int HeapItemsNum(Heap* _heap)
{
	if(NULL == _heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return _heap->m_heapSize;
}

void HeapPrint(Heap* _heap)
{
	if(NULL == _heap)
	{
		return;
	}

	VectorPrint(_heap->m_vec);
}
