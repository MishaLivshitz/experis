#include "search.h"


ADTErr LinearSearch(Vector* _vec,int _itemToSearch, size_t* _index)
{

	size_t numOfItems;
	int currItem;
	ADTErr status;

	if(NULL == _index)
	{
		return ERR_NULL_POINTER;
	}

	if(ERR_OK != (status = VectorItemsNum(_vec,&numOfItems)))
	{
		return status;
	}

	while(ERR_OK==VectorGet(_vec,numOfItems--,&currItem))
	{
		if(_itemToSearch == currItem)
		{
			status = ERR_OK;
			*_index = ++numOfItems;
			return ERR_OK;
		}
	}

	return ERR_NOT_FOUND;
}

ADTErr BinarySearch(Vector* _vec,int _itemToSearch, size_t* _index)
{

	size_t numOfItems;
	int currItem;
	size_t midIndex = 1;
	ADTErr status;

	if(NULL == _index)
	{
		return ERR_NULL_POINTER;
	}

	if(ERR_OK != (status = VectorItemsNum(_vec,&numOfItems)))
	{
		return status;
	}
	
	midIndex = numOfItems/2;
	
	while(numOfItems)
	{		
		VectorGet(_vec,midIndex,&currItem);
		if(_itemToSearch == currItem)
		{
			status = ERR_OK;
			*_index = midIndex;
			return ERR_OK;
		}

		numOfItems/=2;
		midIndex = _itemToSearch > currItem ? midIndex + numOfItems/2: midIndex - numOfItems/2; 
	}

	return ERR_NOT_FOUND;
}
