#include "genericVector.h"


struct Vector {
	int m_megicNum;
	void** m_items;
	size_t m_originalSize;
	size_t m_size;
	size_t m_nitems;
	size_t m_blockSize;
};

static ADTErr VectorReallocation(const VectorPtr _vectorPtr, ResizeFlag _resizeFlag)
{
	
	void** tempIntPtr;
	size_t newSize;
	
	if(INCRESE_FLAG==_resizeFlag)
	{
		newSize = _vectorPtr->m_size + _vectorPtr->m_blockSize;
	}
	else
	{
		newSize = _vectorPtr->m_size - _vectorPtr->m_blockSize;
		if( newSize < _vectorPtr->m_originalSize)
		{
			return ERR_REALLOCATION_FAILED;
		}
	}

	tempIntPtr = (void**)realloc(_vectorPtr->m_items,sizeof(void*)*newSize);

	if(NULL==tempIntPtr)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vectorPtr->m_items = tempIntPtr;
	_vectorPtr->m_size = newSize;
	return ERR_OK;
}

VectorPtr VectorCreate(size_t _initialSize, size_t _extentionsBlockSize)
{
	VectorPtr vector = NULL;

	if(_initialSize==0)
	{
		return VECTOR_CREATION_FAILED;
	}
	
	vector = (VectorPtr)calloc(1,sizeof(Vector));
	if(NULL == vector)
	{
		return VECTOR_CREATION_FAILED;
	}
	
	vector->m_items = (void**)calloc(_initialSize,sizeof(void*));
	if(NULL==vector->m_items)
	{
		free(vector);
		return VECTOR_CREATION_FAILED;
	}
	vector->m_megicNum = MEGIC_NUM_AVTICE;
	vector->m_size = _initialSize+1;
	vector->m_originalSize = _initialSize;
	vector->m_nitems = 0;
	vector->m_blockSize = _extentionsBlockSize;

	return vector;
}	

void VectorDestroy(VectorPtr _vectorPtr,CallBackPtr _destoryFunc,void* _context)
{

	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return;
	}

	VectorForEach(_vectorPtr,_destoryFunc,_context);
	_vectorPtr->m_megicNum = MEGIC_NUM_NOT_ACTIVE;
	_vectorPtr->m_items = NULL;
	free(_vectorPtr);

	return;
}

ADTErr VectorAdd(VectorPtr _vectorPtr, void* _item)
{
	if(NULL==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_vectorPtr->m_nitems==_vectorPtr->m_size-1)
	{
		if(_vectorPtr->m_blockSize==0)
		{
			return ERR_OVERFLOW;
		}
	
		if(ERR_REALLOCATION_FAILED==VectorReallocation(_vectorPtr,INCRESE_FLAG))
		{
			return ERR_REALLOCATION_FAILED;
		}
	}
	
	if(NULL == _vectorPtr->m_items)
	{
		return ERR_REALLOCATION_FAILED;
	}

	_vectorPtr->m_items[++_vectorPtr->m_nitems]=_item;

	return ERR_OK;
}


ADTErr VectorDelete(VectorPtr _vectorPtr, void** _item)
{

	if(NULL==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return ERR_NOT_INITIALIZED;
	}
	

	if(0 == _vectorPtr->m_size || 0 == _vectorPtr->m_nitems)
	{
		return ERR_UNDERFLOW;
	}

	if(NULL != _item)
	{
		*_item = _vectorPtr->m_items[_vectorPtr->m_nitems--];
	}
	
	if((_vectorPtr->m_size - _vectorPtr->m_nitems) >= _vectorPtr->m_blockSize * 2)
	{
		if(ERR_REALLOCATION_FAILED==VectorReallocation(_vectorPtr,DECRESE_FLAG))
		{
			return ERR_REALLOCATION_FAILED;
		}
	}

	return ERR_OK;
}

ADTErr VectorGet(const VectorPtr _vectorPtr,size_t _index, void** _item)
{

	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(NULL == _item)
	{
		return ERR_NULL_POINTER;
	}

	if(0==_index || _index > _vectorPtr->m_nitems)
	{
		return ERR_WRONG_INDEX;
	}

	*_item = _vectorPtr->m_items[_index];

	return ERR_OK;
}

ADTErr VectorSet(VectorPtr _vectorPtr,size_t _index, void* _item)
{
	
	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(0==_index || _index > _vectorPtr->m_nitems)
	{
		return ERR_WRONG_INDEX;
	}
	
	_vectorPtr->m_items[_index] = _item;

	return ERR_OK;
}

ADTErr VectorItemsNum(const Vector* _vectorPtr, size_t* _numOfitems)
{

	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(NULL == _numOfitems)
	{
		return ERR_NULL_POINTER;
	}

	if(0 == _vectorPtr->m_nitems)
	{
		return ERR_UNDERFLOW;
	}

	*_numOfitems = _vectorPtr->m_nitems;
	
	return ERR_OK;
}

void VectorPrint(const VectorPtr _vectorPtr,CallBackPtr _actionFunc, void* _context)
{
	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return;
	}

	VectorForEach(_vectorPtr,_actionFunc,_context);

	return;
}

int VectorForEach(VectorPtr _vec,CallBackPtr _actionFunc,void* _context)
{
	size_t numOfItems;
	void* item;
	size_t i;

	if(NULL ==_vec || MEGIC_NUM_AVTICE != _vec->m_megicNum || ERR_OK!=VectorItemsNum(_vec,&numOfItems))
	{
		return FOR_EACH_ERROR;
	}

	for(i=1;i<=numOfItems;i++)
	{	
		VectorGet(_vec,i,&item);
		if(_actionFunc(item,_context))
		{
			break;
		}
	}

	return i;	
}
