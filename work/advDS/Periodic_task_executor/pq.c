#include "heap.h"
#include "vector.h"
#include "pq.h"
#include <assert.h>
#include <stdlib.h>
#define DEFALUT_PQ_SIZE 10

#define HEAP(P) 	(P->m_heap)

struct PrioQ
{
	Heap* m_heap;
};


PrioQ* PrioQ_Create(AdtItemCompare _itemCmp)
{
	PrioQ* priQ;
	Vector* vec;
	
	
	priQ = (PrioQ*)calloc(1,sizeof(PrioQ));
	
	if(!priQ)
	{
		return NULL;
	}
	
	vec = Vector_Create(DEFALUT_PQ_SIZE,DEFALUT_PQ_SIZE/2);
	
	if(!vec)
	{
		free(priQ);
		return NULL;
	}
	
	HEAP(priQ) = Heap_Build(vec, _itemCmp);
	
	if(!HEAP(priQ))
	{
		free(vec);
		free(priQ);
		return NULL;
	}
	
	return priQ;
}

void PrioQ_Destroy(PrioQ* _pq , AdtItemDestroy _destroyer)
{
	assert(HEAP(_pq));
	Vector_Destroy(Heap_Destroy(HEAP(_pq)),_destroyer);
	free(_pq);
}

PQ_Result PrioQ_Enqueue(PrioQ* _pq, AdtItem _item)
{
	Heap_Result status;
	
	assert(_pq);
	status = Heap_Insert(HEAP(_pq), _item);
	assert(status == HEAP_SUCCESS);
	
	return PQ_SUCCESS;
}

PQ_Result PrioQ_Dequeue(PrioQ* _pq, AdtItem* _item)
{
	
	assert(_pq);
	
	*_item = Heap_Extract(HEAP(_pq));
	assert(*_item!=NULL);
	
	return PQ_SUCCESS;
}

size_t PrioQ_Size(const PrioQ* _pq)
{
	assert(_pq);
	
	return Heap_Size(HEAP(_pq));
}
