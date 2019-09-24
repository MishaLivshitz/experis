#include "stack.h"


Stack* StackCreate(size_t _size, size_t _blockSize)
{
	return VectorCreate(_size,_blockSize);
}

void StackDestroy(Stack* _stack)
{
	VectorDestroy(_stack);
}

ADTErr StackPush(Stack* _stack, int _item)
{
	return VectorAdd(_stack,_item);
}

void StackPrint(Stack* _stack)
{
	VectorPrint(_stack);
}

ADTErr StackTop(Stack* _stack, int* _item)
{
	size_t numOfItems;
	ADTErr status;

	status = VectorItemsNum(_stack,&numOfItems);
	if(ERR_OK != status)
	{
		return status;
	}

	VectorGet(_stack,numOfItems,_item);
	return ERR_OK;
}

int StackIsEmpty(Stack* _stack)
{
	size_t numOfItems;
	ADTErr status;
	status = VectorItemsNum(_stack,&numOfItems);
	if(status == ERR_OK)
	{
		return numOfItems==0;
	}
	return status;
}

ADTErr StackPop(Stack* _stack, int* _item)
{
	return VectorDelete(_stack,_item);
}
