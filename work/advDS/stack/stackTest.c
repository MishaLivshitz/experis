#include "mu_test.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define BIG_ALLOCATION_SIZE 100000000000000000

void MyDestroyInt(int* item)
{	
	free(item);
}

UNIT(Stack_CreateSucces)

	Stack* stack;
	stack=Stack_Create(5, 10);
	ASSERT_THAT(NULL != stack);
	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT


UNIT(Stack_CreateInitSize)

	Stack* stack;
	stack=Stack_Create(0, 10);
	ASSERT_EQUAL_PTR(NULL, stack);
	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT

UNIT(Stack_CreateBigMemAllocation)

	Stack* stack;
	stack=Stack_Create(BIG_ALLOCATION_SIZE, 10);
	ASSERT_EQUAL_PTR(NULL, stack);
	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);
END_UNIT

UNIT(Stack_PushOverflow)

	Stack* stack;
	int* item = malloc(sizeof(int));
	
	*item = 30;
	
	stack = Stack_Create(1, 0);
	Stack_Push(stack,item);
	ASSERT_THAT(STACK_OVERFLOW==Stack_Push(stack,item));

	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);

END_UNIT

UNIT(Stack_PushReallocFailed)

	Stack* stack;
	int* item = malloc(sizeof(int));
	
	*item = 30;
	
	stack = Stack_Create(1, BIG_ALLOCATION_SIZE);
	Stack_Push(stack,item);

	ASSERT_EQUAL_INT(STACK_BAD_ALLOC,Stack_Push(stack,item));
	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT

UNIT(Stack_PushSucces)

	Stack* stack;
	int* item = malloc(sizeof(int));
	int* getItem;
	
	*item = 30;

	stack = Stack_Create(1, 2);
	Stack_Push(stack,item);

	Stack_Top(stack,(AdtItem)&getItem);
	ASSERT_EQUAL_INT(*getItem,*item);
	
	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);
END_UNIT


UNIT(Stack_PopItem)

	Stack* stack;
	int* item = malloc(sizeof(int));
	int* getItem;
	
	*item = 30;

	
	stack = Stack_Create(1, 2);
	Stack_Push(stack,item);
	Stack_Pop(stack,(AdtItem)&getItem);
	ASSERT_EQUAL_INT(*getItem,*item);
	
	free(getItem);
	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT


UNIT(Stack_TopCheck)

	Stack* stack;
	int* item = malloc(sizeof(int));
	int* getItem;
	
	*item = 30;

	stack = Stack_Create(1, 2);
	Stack_Push(stack,item);
	Stack_Top(stack,(AdtItem)&getItem);

	ASSERT_EQUAL_INT(*getItem,*item);
	Stack_Destroy(stack,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT


UNIT(NullStack)

	Stack* stack;
	int* item = NULL;
	stack = NULL;
	
	ASSERT_THAT(STACK_NOT_INITIALIZED == Stack_Push(stack,item));
	ASSERT_THAT(STACK_NOT_INITIALIZED == Stack_Pop(stack,(AdtItem)&item));
	ASSERT_THAT(STACK_NOT_INITIALIZED == Stack_Top(stack,(AdtItem)&item));
	ASSERT_THAT(STACK_NOT_INITIALIZED == Stack_IsEmpty(stack));
	
END_UNIT



TEST_SUITE(Generic Stack Module Unit Test)
	
	TEST(Stack_CreateSucces)
	TEST(Stack_CreateInitSize)
	TEST(Stack_CreateBigMemAllocation)
	TEST(Stack_PushOverflow)
	TEST(Stack_PushReallocFailed)
	TEST(Stack_PushSucces)
	TEST(Stack_PopItem)
	TEST(Stack_TopCheck)
	TEST(NullStack)

END_SUITE
