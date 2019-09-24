#include "genericVector.h"
#include <string.h>
#include "UTestERR.h"
#include "sort.h"
#define BIG_ALLOCATION_SIZE 100000000000000000
#define TEST_NAME_LEN 100 
#define VEC_SIZE 10
#define RAND_RANGE 100


/* gcc -ansi -pedantic -I ../include/ *.c -g */

int MyDestroyInt(void* item,void* context)
{	
	printf("%d\n",*(int*)item);
	return 0;
}

UTestERR TestVectorCreateInitSize()
{
	VectorPtr vector;
	vector=VectorCreate(0, 10);
	if (NULL == vector)
	{
		puts("Initial size = 0 test -> SUCCES!");
		return TEST_SUCCESS;
	}
	puts("Initial size = 0 test -> FAILED!\n");
	return TEST_FAILED;
}

UTestERR TestVectorCreateBigMemAllocation()
{
	VectorPtr vector;
	vector=VectorCreate(BIG_ALLOCATION_SIZE, 10);
	if (NULL == vector)
	{
		puts("Memory allocation failed test -> SUCCES!");
		return TEST_SUCCESS;
	}
		
	puts("Memory allocation failed test -> FAILED!\n");
	return TEST_FAILED;
}

UTestERR TestVectorAddOverflow()
{

	VectorPtr vector;
	ADTErr status;
	int item1 = 8;

	vector = VectorCreate(1, 0);
	VectorAdd(vector,&item1);
	status = VectorAdd(vector,&item1);

	VectorDestroy(vector,MyDestroyInt,NULL);

	if(ERR_OVERFLOW == status)
	{
		puts("Overflow test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Overflow test -> FAILED!");
	return TEST_FAILED;
}


UTestERR TestVectorAddReallocFailed()
{

	VectorPtr vector;
	ADTErr status;
	int item1 = 8;
	int item2 = 5;

	vector = VectorCreate(1, BIG_ALLOCATION_SIZE);
	VectorAdd(vector,&item1);
	status = VectorAdd(vector,&item2);
	VectorDestroy(vector,MyDestroyInt,NULL);

	if(ERR_REALLOCATION_FAILED == status)
	{
		puts("Memory reallocation failed test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Memory reallocation failed test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestVectorAddSucces()
{

	VectorPtr vector;
	int item = 8;
	int* getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,&item);
	VectorAdd(vector,&item);
	VectorAdd(vector,&item);
	VectorGet(vector,1,(void*)&getItem);
	VectorDestroy(vector,MyDestroyInt,NULL);
	if(item == *getItem)
	{
		puts("Insert test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("insert test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestVectorDeletePopItem()
{
	VectorPtr vector;
	int item = 8;
	int* getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,&item);
	VectorDelete(vector,(void*)&getItem);
	VectorDestroy(vector,MyDestroyInt,NULL);

	if(item == *getItem)
	{
		puts("Remove and pop test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Remove and pop test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestVectorDeleteResize()
{
	VectorPtr vector;
	int item = 8;
	int* getItem;
	size_t numOfItems;

	vector = VectorCreate(1, 1);
	VectorAdd(vector,&item);
	VectorAdd(vector,&item);
	VectorAdd(vector,&item);
	VectorDelete(vector,(void*)&getItem);
	VectorItemsNum(vector,&numOfItems);
	VectorDestroy(vector,MyDestroyInt,NULL);

	if(numOfItems == 2)
	{
		puts("New num of items test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("New num of items test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestVectorGetPopItem()
{
	VectorPtr vector;
	int item = 8;
	int* getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,&item);
	VectorGet(vector,1,(void*)&getItem);
	VectorDestroy(vector,MyDestroyInt,NULL);
	
	if(item == *getItem)
	{
		puts("Get item test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Get item test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestVectorGetWrongIndex()
{
	VectorPtr vector;
	int item = 8;
	void* getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,&item);
	if(ERR_WRONG_INDEX == VectorGet(vector,0,(void*)&getItem) && ERR_WRONG_INDEX == VectorGet(vector,2,(void*)&getItem))
	{
		puts("Wrong index test -> SUCCES!");
		VectorDestroy(vector,MyDestroyInt,NULL);
		return TEST_SUCCESS;
	}

	puts("Wrong index  -> FAILED!");
	VectorDestroy(vector,MyDestroyInt,NULL);
	return TEST_FAILED;
}


UTestERR TestVectorSetItem()
{
	VectorPtr vector;
	int item = 8;
	int* getItem;

	vector = VectorCreate(1, 2);
	item++;
	VectorAdd(vector,&item);
	VectorSet(vector,1,&item);
	VectorGet(vector,1,(void*)&getItem);
	VectorDestroy(vector,MyDestroyInt,NULL);
	
	if(item == *getItem)
	{
		puts("Set item test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Set item test -> FAILED!");
	return TEST_FAILED;
}


UTestERR TestVectorSetWrongIndex()
{
	VectorPtr vector;
	int item = 8;
	
	ADTErr statusZeroIndex;
	ADTErr statusOverIndex;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,&item);
	item++;
	statusZeroIndex = VectorSet(vector,0,&item);
	statusOverIndex = VectorSet(vector,2,&item);
	VectorDestroy(vector,MyDestroyInt,NULL);
	if(ERR_WRONG_INDEX == statusZeroIndex && ERR_WRONG_INDEX == statusOverIndex)
	{
		puts("Wrong index test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Wrong index  -> FAILED!");
	return TEST_FAILED;
}


UTestERR TestVectorItemsNum()
{
	VectorPtr vector;
	int item = 8;
	size_t getItem;
		
	vector = VectorCreate(1, 2);
	VectorAdd(vector,&item);
	VectorItemsNum(vector,&getItem);
	VectorDestroy(vector,MyDestroyInt,NULL);
	
	if(1 == getItem)
	{
		puts("Num of items test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Num of items  -> FAILED!");
	return TEST_FAILED;
}

void TestNullVector()
{
	VectorPtr vector;
	UTestERR status = TEST_SUCCESS;
	int item=5;
	int* getItem;
	size_t nItems;
	vector = NULL;
	
	if(ERR_NOT_INITIALIZED != VectorAdd(vector,&item))
	{
		puts("VectorAdd null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(ERR_NOT_INITIALIZED != VectorDelete(vector,(void*)&getItem))
	{
		puts("VectorDelete null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}
	if(ERR_NOT_INITIALIZED != VectorGet(vector,1,(void*)&getItem))
	{
		puts("VectorDelete null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}

	if(ERR_NOT_INITIALIZED != VectorSet(vector,1,&item))
	{
		puts("VectorDelete null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}

	if(ERR_NOT_INITIALIZED != VectorItemsNum(vector,&nItems))
	{
		puts("VectorDelete null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(status == TEST_SUCCESS)
	{
		puts("TestNullVector -> SUCCES!");
	}
}

int main()
{
	int option;
	int exitFlag = FALSE;
	char testName[TEST_NAME_LEN];
	UTestERR testStatus=TEST_SUCCESS;
	while(FALSE==exitFlag)
	{
	
		puts("Test options:\n");
		puts("	1:  TestVectorCreate");
		puts("	2:  TestVectorAdd");
		puts("	3:  TestVectorDelete");
		puts("	4:  TestVectorGet");
		puts("	5:  TestVectorSet");
		puts("	6:  TestVectorNumOfItems");
		puts("	7:  TestNullVector");
		puts("	0:  Quit");

		puts("\nInsert your selection and press Enter:\n");
		scanf("%d",&option);
		getchar();
		switch(option)
		{
			case 1:
				strcpy(testName,"TestVectorCreate");
				testStatus &= TestVectorCreateInitSize();
				testStatus &= TestVectorCreateBigMemAllocation();
				break;

			case 2:
				strcpy(testName,"TestVectorAdd");
				testStatus &= TestVectorAddOverflow();
				testStatus &= TestVectorAddReallocFailed();
				testStatus &= TestVectorAddSucces();
				break;

			case 3:
				strcpy(testName,"TestVectorDelete");
				testStatus &= TestVectorDeletePopItem();
				testStatus &= TestVectorDeleteResize();
				break;

			case 4:
				strcpy(testName,"TestVectorGet");
				testStatus &= TestVectorGetPopItem();
				testStatus &= TestVectorGetWrongIndex();
				break;
			
			case 5:
				strcpy(testName,"TestVectorSet");
				testStatus &= TestVectorSetItem();
				testStatus &= TestVectorSetWrongIndex();
				break;
			
			case 6:
				strcpy(testName,"TestVectorNumOfItems");
				testStatus &= TestVectorItemsNum();
				break;

			case 7:
				strcpy(testName,"TestNullVector");
				TestNullVector();
			continue;

			case 0:
			exitFlag=TRUE;
			break;
			default:
			puts("Please choose valid options");
		}
		if(exitFlag)
		{	
			puts("GOOD BYE!");
			break;
		}
		if(TEST_SUCCESS == testStatus)
		{
			printf("\n%s test - SUCCES!\n\n",testName);
		}
		else
		{
			printf("\n%s test - FAILED!\n\n",testName);
		}
		testStatus=TEST_SUCCESS;
	}
	return 1;
}
