#include "vector.h"
#include <stdlib.h>
#include <stddef.h> 	/*size_t*/

#define MAGIC_NUM_AVTICE 0xdefdef

#define IS_VALID(V)		((V)&&(V)->m_magicNum == MAGIC_NUM_AVTICE)
struct Vector {
	int m_magicNum;
	AdtItem* m_items;
	size_t m_originalSize;
	size_t m_size;
	size_t m_nitems;
	size_t m_blockSize;
};

typedef enum {
	INCREASE_FLAG,
	DECREASE_FLAG
}ResizeFlag;

static Vector_Result VectorReallocation(Vector* _vector, ResizeFlag _resizeFlag)
{
	
	AdtItem* tempIntPtr;
	size_t newSize;
	
	if(INCREASE_FLAG==_resizeFlag)
	{
		newSize = _vector->m_size + _vector->m_blockSize;
	}
	else
	{
		newSize = _vector->m_size - _vector->m_blockSize;
		if( newSize < _vector->m_originalSize)
		{
			return VECTOR_SUCCESS;
		}
	}

	tempIntPtr = (AdtItem*)realloc(_vector->m_items,sizeof(void*)*newSize);

	if(NULL==tempIntPtr)
	{
		return VECTOR_BAD_ALLOC;
	}
	_vector->m_items = tempIntPtr;
	_vector->m_size = newSize;
	
	return VECTOR_SUCCESS;
}

Vector*	Vector_Create(size_t _initialSize, size_t _extendSize)
{
	Vector* vector = NULL;

	if(_initialSize==0)
	{
		return NULL;
	}
	
	vector = (Vector*)calloc(1,sizeof(Vector));
	if(NULL == vector)
	{
		return NULL;
	}
	
	vector->m_items = (void**)calloc(_initialSize + 1,sizeof(void*));
	if(NULL==vector->m_items)
	{
		free(vector);
		return NULL;
	}
	
	vector->m_magicNum = MAGIC_NUM_AVTICE;
	vector->m_size = _initialSize + 1;
	vector->m_originalSize = _initialSize + 1;
	vector->m_nitems = 0;
	vector->m_blockSize = _extendSize;

	return vector;
}	

void Vector_Destroy(Vector* _vector, AdtItemDestroy _destroyFunc)
{

	AdtItem item;

	if(!IS_VALID(_vector))
	{
		return;
	}

	while(VECTOR_SUCCESS == Vector_Delete(_vector,&item))
	{	
		if(_destroyFunc)
		{			
			_destroyFunc(item);
		}
	}

	_vector->m_magicNum = -1;
	free(_vector->m_items);
	free(_vector);

	return;
}

Vector_Result Vector_Add(Vector* _vector, AdtItem _value)
{
	if(!IS_VALID(_vector))
	{
		return VECTOR_NOT_INITIALIZED;
	}
	
	if(_vector->m_nitems==_vector->m_size-1)
	{
		if(_vector->m_blockSize==0)
		{
			return VECTOR_OVERFLOW;
		}
	
		if(VECTOR_BAD_ALLOC==VectorReallocation(_vector,INCREASE_FLAG))
		{
			return VECTOR_BAD_ALLOC;
		}
	}
	
	if(NULL == _vector->m_items)
	{
		return VECTOR_BAD_ALLOC;
	}

	_vector->m_items[++_vector->m_nitems]=_value;

	return VECTOR_SUCCESS;
}

Vector_Result Vector_Delete(Vector* _vector, AdtItem *_pValue)
{

	if(!IS_VALID(_vector))
	{
		return VECTOR_NOT_INITIALIZED;
	}
	
	if(0 == _vector->m_size || 0 == _vector->m_nitems)
	{
		return VECTOR_UNDERFLOW;
	}

	if(NULL != _pValue)
	{
		*_pValue = _vector->m_items[_vector->m_nitems];
	}
	
	_vector->m_nitems--;

	if((_vector->m_size - _vector->m_nitems) >= _vector->m_blockSize * 2)
	{
		if(VECTOR_BAD_ALLOC==VectorReallocation(_vector,DECREASE_FLAG))
		{
			return VECTOR_BAD_ALLOC;
		}
	}

	return VECTOR_SUCCESS;
}

Vector_Result Vector_Get(Vector* _vector, size_t _index, AdtItem *_pValue)
{

	if(!IS_VALID(_vector))
	{
		return VECTOR_NOT_INITIALIZED;
	}

	if(NULL == _pValue)
	{
		return VECTOR_NOT_INITIALIZED;
	}

	if(0==_index || _index > _vector->m_nitems)
	{
		return VECTOR_WRONG_INDEX;
	}

	*_pValue = _vector->m_items[_index];

	return VECTOR_SUCCESS;
}

Vector_Result Vector_Set(Vector* _vector, size_t _index, AdtItem _value)
{
	
	if(!IS_VALID(_vector))
	{
		return VECTOR_NOT_INITIALIZED;
	}
	if(0==_index || _index > _vector->m_nitems)
	{
		return VECTOR_WRONG_INDEX;
	}
	
	_vector->m_items[_index] = _value;

	return VECTOR_SUCCESS;
}

size_t Vector_Size(Vector* _vector)
{

	if(!IS_VALID(_vector))
	{
		return 0;
	}

	return _vector->m_nitems;
}

size_t Vector_Capacity(Vector* _vector)
{
	
	if(!IS_VALID(_vector))
	{
		return 0;
	}

	return _vector->m_size;

}

int VectorForEach(Vector* _vector,AdtItemAction _actionFunc, AdtItem _context)
{
	size_t numOfItems;
	size_t i;
	
	if(!IS_VALID(_vector))
	{
		return VECTOR_NOT_INITIALIZED;
	}

	numOfItems=Vector_Size(_vector);

	for(i=0;i<numOfItems;i++)
	{	
		
		if(!_actionFunc(_vector->m_items[i+1],_context))
		{
			break;
		}
	}

	return i;	
}
