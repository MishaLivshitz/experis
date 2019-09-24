#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

#define MAGIC_NUM_ACTIVE 0xdefdef
#define FATHER(I) (I)/2
#define LEFT(I) (I)*2
#define RIGHT(I) (I)*2+1
#define CMP_FUNC(H)					((H)->m_cmpFunc)		
#define MAX_LEFT_FATHER(H,X,Y) 		((H)->m_cmpFunc((X),(Y))) ? MAX_LEFT: MAX_FATHER
#define MAX_RIGHT_FATHER(H,X,Y) 	((H)->m_cmpFunc((X),(Y))) ? MAX_RIGHT: MAX_FATHER
#define MAX_LEFT_RIGHT(H,X,Y) 		((H)->m_cmpFunc((X),(Y))) ? MAX_LEFT: MAX_RIGHT
#define IS_VALID(H) 				((H) && (H)->m_magicNum == MAGIC_NUM_ACTIVE && (H)->m_items)

typedef enum
{
	MAX_FATHER,
	MAX_LEFT,
	MAX_RIGHT
}MaxNode;

struct Heap
{
	int m_magicNum;
	Vector* m_items;
	size_t m_heapSize;
	AdtItemCompare m_cmpFunc;
};

static Heap_Result resultsLUT[] = {
	HEAP_SUCCESS,
	HEAP_NOT_INITIALIZED,
	HEAP_NOT_INITIALIZED,
	HEAP_ALLOCATION_FAILED,
	HEAP_UNDERFLOW,
	HEAP_OVERFLOW,
	HEAP_NOT_INITIALIZED
};

static void swap(Vector* _vec,int _a, int _b)
{
	AdtItem itemSon;
	AdtItem itemFather;
	
	Vector_Get(_vec,_a,&itemSon); 
	Vector_Get(_vec,_b,&itemFather);
	Vector_Set(_vec,_a,itemFather);
	Vector_Set(_vec,_b,itemSon);
	
}

static MaxNode FindMaxNode(Heap* _heap, int _fatherIndex)
{

	AdtItem itemSonLeft;
	AdtItem itemSonRight;
	AdtItem itemFather;
	MaxNode maxNode;
	
	Vector_Get(_heap->m_items,LEFT(_fatherIndex),&itemSonLeft);
	Vector_Get(_heap->m_items,_fatherIndex,&itemFather);
	maxNode = MAX_LEFT_FATHER(_heap,itemSonLeft,itemFather);

	if(RIGHT(_fatherIndex) <= _heap->m_heapSize)
	{
		Vector_Get(_heap->m_items,RIGHT(_fatherIndex),&itemSonRight);
		if(MAX_FATHER == maxNode)
		{
			maxNode = MAX_RIGHT_FATHER(_heap,itemSonRight,itemFather);
		}
		else
		{
			maxNode = MAX_LEFT_RIGHT(_heap,itemSonLeft,itemSonRight);
		}
	}
	
	return maxNode;
}

static void Heapify(Heap* _heap,int _fatherIndex)
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
			swap(_heap->m_items,_fatherIndex,LEFT(_fatherIndex));
			Heapify(_heap, LEFT(_fatherIndex));
			break;

		case MAX_RIGHT:
			swap(_heap->m_items,_fatherIndex,RIGHT(_fatherIndex));
			Heapify(_heap, RIGHT(_fatherIndex));;
			break;
	}
	
	return;
}

static void BubbleUp(Heap* _heap,int _newIndex)
{
	AdtItem itemFather;
	AdtItem itemSon;
	
	Vector_Get(_heap->m_items,FATHER(_newIndex),&itemFather); 
	Vector_Get(_heap->m_items,_newIndex,&itemSon); 
	if(_newIndex==1 || _heap->m_cmpFunc(itemFather,itemSon))
	{
		return;
	}

	swap(_heap->m_items,FATHER(_newIndex),_newIndex);
	BubbleUp(_heap,FATHER(_newIndex));
	
	return;
}
Heap* Heap_Build(Vector* _vector, AdtItemCompare _pfComp)
{

	Heap* heap;
	size_t itemsNum;
	
	itemsNum = Vector_Size(_vector);
	if(NULL == (heap=(Heap*)malloc(sizeof(Heap))))
	{
		return NULL;
	}

	
	heap->m_items = _vector;
	heap->m_heapSize = itemsNum;
	heap->m_cmpFunc = _pfComp;
	
	while(FATHER(itemsNum))
	{
		Heapify(heap, FATHER(itemsNum--));
	}
	
	heap->m_magicNum = MAGIC_NUM_ACTIVE;
	
	return heap;
}

Vector* Heap_Destroy(Heap* _heap)
{
	Vector* oldItems;
	
	if(!IS_VALID(_heap))
	{
		return NULL;
	}
	
	_heap->m_magicNum = -1;
	oldItems = _heap->m_items;
	free(_heap);
	
	return oldItems;
}

Heap_Result Heap_Insert(Heap* _heap, AdtItem _element)
{
	
	Vector_Result status;
	if(!IS_VALID(_heap))
	{
		return HEAP_NOT_INITIALIZED;
	}
	
	status = Vector_Add(_heap->m_items,_element);

	if(VECTOR_SUCCESS != status)
	{
		return resultsLUT[status];
	}
	
	++_heap->m_heapSize;
	BubbleUp(_heap, _heap->m_heapSize);
	
	return HEAP_SUCCESS;
}

const AdtItem Heap_Peek(const Heap* _heap)
{
	AdtItem returnedData = NULL;
	
	if(!IS_VALID(_heap))
	{
		return NULL;
	}
	
	Vector_Get(_heap->m_items,1,&returnedData);
	
	return returnedData;
}

AdtItem Heap_Extract(Heap* _heap)
{
	AdtItem returnedData = NULL;
	
	if(!IS_VALID(_heap))
	{
		return NULL;
	}
	
	swap(_heap->m_items,1,_heap->m_heapSize);
	Vector_Delete(_heap->m_items,&returnedData);
	if(returnedData)
	{
		--_heap->m_heapSize;
		Heapify(_heap, 1);
	}

	return returnedData;
}

size_t Heap_Size(const Heap* _heap)
{
	return IS_VALID(_heap) ? _heap->m_heapSize: 0;
}

size_t Heap_ForEach(const Heap* _heap, AdtItemAction _act, void* _context)
{
	
	if(!IS_VALID(_heap) || !_act)
	{
		return 0;
	}
	
	return VectorForEach(_heap->m_items,_act,_context);
}

void Heap_Sort(Vector* _vec, AdtItemCompare _pfComp)
{
	Heap* heap;

	if(NULL == _vec || Vector_Size(_vec) == 0)
	{
		return;
	}
	
	heap = Heap_Build(_vec, _pfComp);
	
	if(NULL == heap)
	{
		return;
	}
	
	while(heap->m_heapSize)
	{
		swap(heap->m_items,1,heap->m_heapSize);
		--heap->m_heapSize;
		Heapify(heap, 1);
	}
	
	Heap_Destroy(heap);
}
