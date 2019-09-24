#include "vector.h"
#include <string.h>
#include "UTestERR.h"
#include "sort.h"
#define BIG_ALLOCATION_SIZE 100000000000000000
#define TEST_NAME_LEN 100 
#define VEC_SIZE 10
#define RAND_RANGE 100


/* gcc -ansi -pedantic -I ../include/ *.c -g */

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


UTestERR TestVectorCreateFromBinary()
{
	VectorPtr vector;
	size_t size;
	vector = VectorCreateFromBinary("file.bin");
	VectorItemsNum(vector,&size);
	if (size == 10)
	{
		return TEST_SUCCESS;
	}

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

	vector = VectorCreate(1, 0);
	VectorAdd(vector,8);
	status = VectorAdd(vector,5);
	VectorDestroy(vector);

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

	vector = VectorCreate(1, BIG_ALLOCATION_SIZE);
	VectorAdd(vector,8);
	status = VectorAdd(vector,8);
	VectorDestroy(vector);

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
	int getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,item);
	VectorGet(vector,1,&getItem);
	VectorDestroy(vector);

	if(item == getItem)
	{
		puts("Insert test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("insert test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestVectorPrintToBin()
{

	VectorPtr vector;
	int item = 8;
	size_t size = 10;
	size_t returnedSize = 10*sizeof(int);

	vector = VectorCreate(size, size);

	while(size-->0)
	{
		VectorAdd(vector,item*2);
	}
	
	returnedSize = returnedSize - VectorPrintToBin(vector,"file.bin");
	VectorDestroy(vector);
	
	if(returnedSize)
	{
		puts("Print to bin -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Print to bin -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestVectorDeletePopItem()
{
	VectorPtr vector;
	int item = 8;
	int getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,item);
	VectorDelete(vector,&getItem);
	VectorDestroy(vector);

	if(item == getItem)
	{
		puts("Remove and pop test -> SUCCES!");
		return TEST_SUCCESS;
	}

	puts("Remove and pop test -> FAILED!");
	return TEST_FAILED;
}

/*Check if the deleted item returns */
UTestERR TestVectorDeleteResize()
{
	VectorPtr vector;
	int item = 8;
	int getItem;
	size_t numOfItems;

	vector = VectorCreate(1, 1);
	VectorAdd(vector,item);
	VectorAdd(vector,item);
	VectorAdd(vector,item);
	VectorDelete(vector,&getItem);
	VectorItemsNum(vector,&numOfItems);
	VectorDestroy(vector);

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
	int getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,item);
	VectorGet(vector,1,&getItem);
	VectorDestroy(vector);
	
	if(item == getItem)
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
	int getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,item);
	if(ERR_WRONG_INDEX == VectorGet(vector,0,&getItem) && ERR_WRONG_INDEX == VectorGet(vector,2,&getItem))
	{
		puts("Wrong index test -> SUCCES!");
		VectorDestroy(vector);
		return TEST_SUCCESS;
	}

	puts("Wrong index  -> FAILED!");
	VectorDestroy(vector);
	return TEST_FAILED;
}


UTestERR TestVectorSetItem()
{
	VectorPtr vector;
	int item = 8;
	int getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,item);
	VectorSet(vector,1,++item);
	VectorGet(vector,1,&getItem);
	VectorDestroy(vector);
	
	if(item == getItem)
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
	VectorAdd(vector,item++);
	statusZeroIndex = VectorSet(vector,0,item);
	statusOverIndex = VectorSet(vector,2,item);
	VectorDestroy(vector);

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
	VectorAdd(vector,item);
	VectorItemsNum(vector,&getItem);
	VectorDestroy(vector);
	
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
	size_t nItems;
	vector = NULL;
	
	if(ERR_NOT_INITIALIZED != VectorAdd(vector,1))
	{
		puts("VectorAdd null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(ERR_NOT_INITIALIZED != VectorDelete(vector,&item))
	{
		puts("VectorDelete null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}
	if(ERR_NOT_INITIALIZED != VectorGet(vector,1,&item))
	{
		puts("VectorDelete null vector test -> FAILED!");
		status &=TEST_FAILED; 
	}

	if(ERR_NOT_INITIALIZED != VectorSet(vector,1,item))
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
		puts("	7:  TestVectorPrintToBin");
		puts("	8:  TestVectorCreateFromBinary");
		puts("	9:  TestNullVector");
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
				strcpy(testName,"TestVectorPrintToBin");
				TestVectorPrintToBin();
				break;

			case 8:
				strcpy(testName,"TestVectorCreateFromBinary");
				TestVectorCreateFromBinary();
				break;

			case 9:
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
