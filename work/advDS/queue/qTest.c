#include "mu_test.h"
#include "queue.h"
#include <string.h>

#define BIG_ALLOCATION_SIZE 1000000000000
#define TEST_NAME_LEN 100

void DestroyChar(char* _item)
{
	free(_item);
}

UNIT(Queue_CreateSucces)

	Queue* queue;
	queue=Queue_Create(5);
	
	ASSERT_THAT(NULL != queue);
	
	Queue_Destroy(queue,(AdtItemDestroy)DestroyChar);
END_UNIT	


UNIT(Queue_CreateInitSize)

	Queue* queue;
	queue=Queue_Create(0);
	ASSERT_EQUAL_PTR(NULL,queue);
	
END_UNIT


UNIT(Queue_CreateBigMemAllocation)

	Queue* queue;
	queue=Queue_Create(BIG_ALLOCATION_SIZE);
	ASSERT_EQUAL_PTR(NULL,queue);
	
END_UNIT

UNIT(Queue_InsertOverflow)

	Queue* queue;
	
	char* ch= malloc(sizeof(char));
	
	*ch = 'm';
	
	queue = Queue_Create(1);
	Queue_Enque(queue,ch);
	
	ASSERT_EQUAL_INT(QUEUE_OVERFLOW, Queue_Enque(queue,ch));
	
	Queue_Destroy(queue,(AdtItemDestroy)DestroyChar);
	
END_UNIT


UNIT(Queue_InsertSucces)

	Queue* queue;
	char* ch= malloc(sizeof(char));
	char* getItem;

	*ch = 'm';
	queue = Queue_Create(1);
	ASSERT_EQUAL_INT(QUEUE_SUCCESS,Queue_Enque(queue,ch));
	Queue_Deque(queue,(AdtItem)&getItem);
	ASSERT_EQUAL_INT(ch,getItem);
	free(getItem);
	Queue_Destroy(queue,(AdtItemDestroy)DestroyChar);
	
END_UNIT


UNIT(Queue_RemoveItem)

	Queue* queue;
	char* ch = malloc(sizeof(char));
	char* getItem;
	
	*ch = 'm';
	queue = Queue_Create(1);	
	Queue_Enque(queue,ch);
	
	ASSERT_EQUAL_INT(Queue_Deque(queue,(AdtItem)&getItem),QUEUE_SUCCESS);
	ASSERT_EQUAL_INT(*ch,*getItem);
	
	free(getItem);
	Queue_Destroy(queue,(AdtItemDestroy)DestroyChar);
	
END_UNIT

UNIT(Queue_IsEmptyCheck)

	Queue* queue;
	char* ch;

	queue = Queue_Create(1);
	Queue_Enque(queue,ch);
	
	ASSERT_THAT(!Queue_IsEmpty(queue));
	Queue_Deque(queue,(AdtItem)&ch);
	ASSERT_THAT(Queue_IsEmpty(queue));
	
	Queue_Destroy(queue,(AdtItemDestroy)DestroyChar);

END_UNIT

UNIT(NullQueue)

	Queue* queue;
	char* ch = malloc(sizeof(char));
	char* getItem;
	queue = NULL;
	
	ASSERT_THAT(QUEUE_NOT_INITIALIZED == Queue_Enque(queue,ch));
	ASSERT_THAT(QUEUE_NOT_INITIALIZED == Queue_Deque(queue,(AdtItem)&getItem));
	ASSERT_EQUAL_INT(0 ,Queue_IsEmpty(queue));
	ASSERT_EQUAL_INT(0 ,Queue_IsFull(queue));
	ASSERT_EQUAL_INT(0 ,Queue_Size(queue));
	free(ch);
	
END_UNIT

TEST_SUITE(Generic Queue Module Unit Test)
	
	TEST(Queue_CreateSucces)
	TEST(Queue_CreateInitSize)
	TEST(Queue_CreateBigMemAllocation)
	TEST(Queue_InsertOverflow)
	TEST(Queue_RemoveItem)
	TEST(Queue_IsEmptyCheck)
	TEST(NullQueue)

END_SUITE
