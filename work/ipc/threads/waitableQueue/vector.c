#include "vector.h"


struct Vector {
	int m_megicNum;
	int* m_items;
	size_t m_originalSize;
	size_t m_size;
	size_t m_nitems;
	size_t m_blockSize;
};

static ADTErr VectorReallocation(const VectorPtr _vectorPtr, ResizeFlag _resizeFlag)
{
	
	int* tempIntPtr;
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

	tempIntPtr = (int*)realloc(_vectorPtr->m_items,sizeof(int)*newSize);

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
	
	vector->m_items = (int*)calloc(_initialSize+1,sizeof(int));
	if(NULL==vector->m_items)
	{
		free(vector);
		return VECTOR_CREATION_FAILED;
	}
	vector->m_megicNum = MEGIC_NUM_AVTICE;
	vector->m_size = _initialSize + 1;
	vector->m_originalSize = _initialSize + 1;
	vector->m_nitems = 0;
	vector->m_blockSize = _extentionsBlockSize;

	return vector;
}	

VectorPtr VectorCreateFromBinary(char* const _fileName)
{
	FILE *fp;
	VectorPtr vec;
	size_t count=0;
	int tempItem;
	fp = fopen(_fileName,"rb");	
	
	if(NULL == fp)
	{
		return NULL;
	}
	
	for(;fread(&tempItem, sizeof(int), 1, fp); count++);

	if(NULL == (vec=VectorCreate(count,count/2 + 1)))
	{
		return NULL;
	}
	
	rewind(fp);
	fread(vec->m_items,sizeof(int),count,fp);
	vec->m_nitems = count;

	return vec;
}

ADTErr VectorAdd(VectorPtr _vectorPtr, int _item)
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


ADTErr VectorDelete(VectorPtr _vectorPtr, int* _item)
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
		*_item = _vectorPtr->m_items[_vectorPtr->m_nitems];
	}
	
	--_vectorPtr->m_nitems;
	if((_vectorPtr->m_size - _vectorPtr->m_nitems) >= _vectorPtr->m_blockSize * 2)
	{
		if(ERR_REALLOCATION_FAILED==VectorReallocation(_vectorPtr,DECRESE_FLAG))
		{
			return ERR_REALLOCATION_FAILED;
		}
	}

	return ERR_OK;
}

ADTErr VectorGet(const VectorPtr _vectorPtr,size_t _index, int* _item)
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

ADTErr VectorSet(VectorPtr _vectorPtr,size_t _index, int _item)
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

ADTErr VectorItemsNum(const VectorPtr _vectorPtr, size_t* _numOfitems)
{

	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(NULL == _numOfitems)
	{
		return ERR_NULL_POINTER;
	}

	*_numOfitems = _vectorPtr->m_nitems;
	
	return ERR_OK;
}

void VectorDestroy(VectorPtr _vectorPtr)
{

	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return;
	}
	
	_vectorPtr->m_megicNum = MEGIC_NUM_NOT_ACTIVE;
	free(_vectorPtr->m_items);
	_vectorPtr->m_items = NULL;
	free(_vectorPtr);

	return;
}

int VectorPrintToBin(const VectorPtr _vectorPtr,char* const _fileName)
{
	FILE *fp;
	size_t sizeWritten;

	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return ERR_NOT_INITIALIZED;
	}

	fp = fopen(_fileName,"wb");	
	
	if(NULL == fp)
	{
		return ERR_OPEN_FILE_FAILED;
	}
	
	sizeWritten = fwrite(_vectorPtr->m_items,sizeof(int),_vectorPtr->m_nitems,fp);
	fclose(fp);
	return sizeWritten;
}

void VectorPrint(const VectorPtr _vectorPtr){

	int i;

	if(NULL ==_vectorPtr || MEGIC_NUM_AVTICE != _vectorPtr->m_megicNum)
	{
		return;
	}

	if(0==_vectorPtr->m_nitems)
	{
		printf("[]\n");
		return;
	}

	printf("[");
	for(i=1;i<_vectorPtr->m_nitems;i++)
	{	
		printf("%d,",_vectorPtr->m_items[i]);
		
	}
	printf("%d]\n",_vectorPtr->m_items[i]);
	return;
}

Vector* VectorCopy(Vector* _vecSource,Vector* _vecDest)
{
	size_t newNumOfItems=0;
	if(NULL ==_vecSource || MEGIC_NUM_AVTICE != _vecSource->m_megicNum)
	{
		return NULL;
	}
	
	if(NULL==_vecDest)
	{
		_vecDest = VectorCreate(_vecSource->m_nitems,_vecSource->m_nitems/2);	
	
		if(NULL!=_vecDest)
		{
			while(newNumOfItems<_vecSource->m_nitems)
			{
				VectorAdd(_vecDest,_vecSource->m_items[++newNumOfItems]);
			}
			return _vecDest;
		}
	}
	else if(_vecSource->m_nitems == _vecDest->m_nitems)
	{
		while(newNumOfItems<_vecSource->m_nitems)
			{
				++newNumOfItems;
				VectorSet(_vecDest,newNumOfItems,_vecSource->m_items[newNumOfItems]);
			}
			return _vecDest;
	}
	
	
	return NULL;
}
