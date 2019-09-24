#include "queue.h"
#include <string.h>
#define BIG_ALLOCATION_SIZE 1000000000000
#define TEST_NAME_LEN 100

typedef enum
{
	EXIT = 0,
	CREATE,
	INSERT,
	REMOVE,
	IS_EMPTY,
	PRINT,
	NULL_POINTER
}MenuCase;


typedef enum
{
	TEST_SUCCES = TRUE,
	TEST_FAILED = FALSE
}UTestERR;


UTestERR TestQueueCreateSucces()
{

	Queue* queue;
	queue=QueueCreate(5);
	if (NULL != queue)
	{
		puts("create queue test -> SUCCES!");
		return TEST_SUCCES;
	}
	puts("create queue test -> FAILED!\n");
	return TEST_FAILED;

}

UTestERR TestQueueCreateInitSize()
{
	Queue* queue;
	queue=QueueCreate(0);
	if (NULL == queue)
	{
		puts("Initial size = 0 test -> SUCCES!");
		return TEST_SUCCES;
	}
	puts("Initial size = 0 test -> FAILED!\n");
	return TEST_FAILED;
}

UTestERR TestQueueCreateBigMemAllocation()
{
	Queue* queue;
	queue=QueueCreate(BIG_ALLOCATION_SIZE);
	if (NULL == queue)
	{
		puts("Memory allocation failed test -> SUCCES!");
		return TEST_SUCCES;
	}
		
	puts("Memory allocation failed test -> FAILED!\n");
	return TEST_FAILED;
}


UTestERR TestQueueInsertOverflow()
{

	Queue* queue;
	ADTErr status;

	queue = QueueCreate(1);
	QueueInsert(queue,8);
	status = QueueInsert(queue,5);
	QueueDestroy(queue);

	if(ERR_OVERFLOW == status)
	{
		puts("Overflow test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("Overflow test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestQueueInsertSucces()
{

	Queue* queue;
	int item = 8;
	int getItem;
	ADTErr status;

	queue = QueueCreate(1);
	status = QueueInsert(queue,item);
	QueueDestroy(queue);

	if(ERR_OK == status)
	{
		puts("push test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("push test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestQueueRemoveItem()
{
	Queue* queue;
	int item = 8;
	int getItem;
	ADTErr status;
	
	queue = QueueCreate(1);	
	QueueInsert(queue,item);
	status = QueueRemove(queue,&item);
	QueueDestroy(queue);
	if(status == ERR_OK)
	{
		puts("remove item test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("remove item test -> FAILED!");
	return TEST_FAILED;
}

void TestNullQueue()
{
	Queue* queue;
	UTestERR status = TEST_SUCCES;
	int item=5;
	int nItems;
	queue = NULL;
	
	if(ERR_NOT_INITIALIZED != QueuePrint(queue))
	{
		puts("QueuePrint null queue test -> FAILED!");
		status &=TEST_FAILED; 
	}

	if(ERR_NOT_INITIALIZED != QueueInsert(queue,item))
	{
		puts("QueuePop null queue test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(ERR_NOT_INITIALIZED != QueueRemove(queue,&item))
	{
		puts("QueueTop null queue test -> FAILED!");
		status &=TEST_FAILED; 
	}

	if(FALSE != QueueIsEmpty(queue))
	{
		puts("QueueIsEmpty null queue test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(status == TEST_SUCCES)
	{
		puts("TestNullQueue -> SUCCES!");
	}
}

void TestQueueIsEmpty()
{
	Queue* queue;
	int item = 8;
	int getItem;
	ADTErr status;

	queue = QueueCreate(1);
	QueueInsert(queue,item);
	!QueueIsEmpty(queue) ? puts("is not empty test -> SUCCES!"):puts("remove item test -> FAILED!");
	status = QueueRemove(queue,&item);
	QueueIsEmpty(queue) ? puts("is empty test -> SUCCES!"):puts("remove item test -> FAILED!");
	QueueDestroy(queue);
}

void TestQueuePrint()
{
	Queue* queue;
	int MaxnumOfItems = 5;
	int item = MaxnumOfItems;
	queue = QueueCreate(MaxnumOfItems);
	while(item>0)
	{
		QueueInsert(queue,item--);
	}
	QueuePrint(queue) == MaxnumOfItems ? puts("print test -> SUCCES!"):puts("print test -> FAILED!");

}

int main()
{
	
	Queue* queue;
	int option,size,item;
	int exitFlag = FALSE;
	char testName[TEST_NAME_LEN];
	UTestERR testStatus=TEST_SUCCES;

	while(FALSE==exitFlag)
	{

		puts("Test options:\n");
		puts("	1: Test create queue");
		puts("	2: Test insert item");
		puts("	3: Test remove item");
		puts("	4: Test is empty");
		puts("	5: Test print queue");
		puts("	6: Test null Test");
		puts("	0: Quit");

		puts("\nInsert your selection and press Enter:\n");
		scanf("%d",&option);
		switch(option)
		{
			case CREATE:
				strcpy(testName,"TestQueueCreate");
				testStatus &= TestQueueCreateSucces();
				testStatus &= TestQueueCreateInitSize();
				testStatus &= TestQueueCreateBigMemAllocation();
				break;

			case INSERT:
				strcpy(testName,"TestQueueInsert");
				testStatus &= TestQueueInsertOverflow();
				testStatus &= TestQueueInsertSucces();
				break;

			case REMOVE:
				strcpy(testName,"TestQueueRemove");
				testStatus &= TestQueueRemoveItem();
				break;

			case IS_EMPTY:
				strcpy(testName,"TestQueueIsEmpty");
				TestQueueIsEmpty();
				continue;
				
			case PRINT:
				strcpy(testName,"TestQueueIsEmpty");
				TestQueuePrint();
				continue;

			case NULL_POINTER:
				strcpy(testName,"TestNullQueue");
				TestNullQueue();
				continue;
	
			case EXIT:
				exitFlag=TRUE;
				break;

			default:
				puts("Please choose valid option");
				break;
		}
		if(exitFlag)
		{	
			puts("GOOD BYE!");
			break;
		}
		
		if(TEST_SUCCES == testStatus)
		{
			printf("\n%s test - SUCCES!\n\n",testName);
		}
		else
		{
			printf("\n%s test - FAILED!\n\n",testName);
		}
		testStatus=TEST_SUCCES;
	}
}
