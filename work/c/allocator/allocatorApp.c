#include "alocator.h"
#define SIZE 10

UTestERR TestPoolCreateSuccess()
{
	UTestERR status = TEST_SUCCESS;
	MemPool_t* pool;

	if(NULL == (pool=CreatePool(sizeof(int),SIZE)))
	{
		status = TEST_FAILED;
	}

	DestroyPool(pool);
	return status;
}

UTestERR TestPoolCreateFailedZeroMem()
{
	MemPool_t* pool;

	if(NULL == (pool=CreatePool(0,SIZE)))
	{
		return TEST_SUCCESS;
	}

	DestroyPool(pool);
	return TEST_FAILED;
}

UTestERR TestPoolCreateFailedBigMemAllocation()
{
	MemPool_t* pool;

	if(NULL == (pool=CreatePool(1,BIG_ALLOCATION_SIZE)))
	{
		return TEST_SUCCESS;
	}

	DestroyPool(pool);
	return TEST_FAILED;
}

UTestERR TestMyAllocSuccess()
{
	MemPool_t* pool;
	int* numArr;
	
	pool = CreatePool(sizeof(int),1);

	if(NULL == (numArr=MyMalloc(pool)))
	{
		return TEST_FAILED;
	}

	if(NULL != (numArr=MyMalloc(pool)))
	{
		return TEST_FAILED;
	}
	
	DestroyPool(pool);
	return TEST_SUCCESS;
}

UTestERR TestMyFreeSuccess()
{
	MemPool_t* pool;
	int* num,*num1;
	
	pool = CreatePool(sizeof(int),1);

	if(NULL == (num=MyMalloc(pool)))
	{
		return TEST_FAILED;
	}

	if(NULL != (num1=MyMalloc(pool)))
	{
		return TEST_FAILED;
	}

	MyFree(pool,num);

	if(NULL == (num=MyMalloc(pool)))
	{
		return TEST_FAILED;
	}
	
	DestroyPool(pool);
	return TEST_SUCCESS;
}

void printTestResult(UTestERR result,char* testName)
{
	result==TRUE ? printf("%s: %sSUCCESS%s\n\n",testName,KGRN,RESET): printf("%s: %sFAILED%s\n\n",testName,KRED,RESET);
}

int main()
{

	puts("\n****************TESTS*****************\n");
	printTestResult(TestPoolCreateSuccess(),"TestPoolCreateSuccess");
	printTestResult(TestPoolCreateFailedZeroMem(),"TestPoolCreateFailedZeroMem");
	printTestResult(TestPoolCreateFailedBigMemAllocation(),"TestPoolCreateFailedBigMemAllocation");

	printTestResult(TestMyAllocSuccess(),"TestMyAllocSuccess");
	printTestResult(TestMyFreeSuccess(),"TestMyFreeSuccess");
	puts("****************TESTS*****************\n");

	return 1;
}
