#include "stack.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

#define MAGIC_NUM_ACTIVE 0xaccacc

#define VEC(S)	(S)->m_vec
#define IS_VALID(S) ((S) && (S)->m_magicNum == MAGIC_NUM_ACTIVE)

struct Stack
{
	int m_magicNum;
	Vector* m_vec;
};

Stack*	Stack_Create(size_t _initialSize, size_t _extendSize)
{
	Stack* stack;
	
	stack = (Stack*)calloc(1,sizeof(Stack));
	if(!stack)
	{
		return NULL;
	}
	
	VEC(stack) = Vector_Create(_initialSize, _extendSize);
	if(!VEC(stack))
	{
		free(stack);
		return NULL;
	}
	
	stack->m_magicNum = MAGIC_NUM_ACTIVE;
	
	return stack;
}

void Stack_Destroy(Stack* _stack, AdtItemDestroy _destroyFunc)
{
	if(!IS_VALID(_stack))
	{
		return;
	}
	
	Vector_Destroy(VEC(_stack), _destroyFunc);
	_stack->m_magicNum = -1;
	free(_stack);
}

Stack_Result Stack_Push(Stack* _stack, AdtItem _value)
{
	if(!IS_VALID(_stack))
	{
		return STACK_NOT_INITIALIZED;
	}
	
	return Vector_Add(VEC(_stack),_value);
}
Stack_Result Stack_Pop(Stack* _stack, AdtItem *_pValue)
{
	if(!IS_VALID(_stack))
	{
		return STACK_NOT_INITIALIZED;
	}
	
	return Vector_Delete(VEC(_stack),_pValue);
}
Stack_Result Stack_Top(const Stack* _stack, AdtItem *_pValue)
{
	size_t numOfItems;
	
	if(!IS_VALID(_stack))
	{
		return STACK_NOT_INITIALIZED;
	}

	numOfItems = Vector_Size(VEC(_stack));
	
	if(!numOfItems)
	{
		return STACK_UNDERFLOW;
	}

	return Vector_Get(VEC(_stack),numOfItems,_pValue);
}

int	Stack_IsEmpty(const Stack* _stack)
{
	size_t numOfItems;
	
	if(!IS_VALID(_stack))
	{
		return 1;
	}
	
	numOfItems = Vector_Size(VEC(_stack));

	return numOfItems==0;
	
}
size_t	Stack_Capacity(const Stack* _stack)
{
	if(!IS_VALID(_stack))
	{
		return 0;
	}
	
	return Vector_Capacity(VEC(_stack));
}

size_t	Stack_Size(const Stack* _stack)
{
	if(!IS_VALID(_stack))
	{
		return 0;
	}
	
	return Vector_Size(VEC(_stack));
}

int StackForEach(Stack* _stack,AdtItemAction _actionFunc,void* _context)
{
	if(!IS_VALID(_stack))
	{
		return -1;
	}
	
	return VectorForEach(VEC(_stack),_actionFunc,_context);
}
