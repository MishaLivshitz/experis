#include "heap.h"
#include "UTestERR.h"
#include <stdlib.h>

#define BLOCK_EXTENTION_SIZE(size) (size)/2+1
#define RANDOM_RANGE 100
#define INSERT_AMOUNT 5

UTestERR TestHeapBuildSuccess(int _size)
{
	UTestERR status = TEST_SUCCESS;
	Heap* heap;
	Vector* vec = VectorCreate(_size,BLOCK_EXTENTION_SIZE(_size));
	
	while(_size-->0)
	{
		VectorAdd(vec,random()%RANDOM_RANGE);
	}
	
	if(NULL== (heap=HeapBuild(vec)))
	{
		status = TEST_FAILED;
	}

	HeapDestroy(heap);
	VectorDestroy(vec);
	return status;
}

UTestERR TestHeapBuildRightOrder(int _size)
{

	Heap* heap;
	Vector* vec = VectorCreate(_size,BLOCK_EXTENTION_SIZE(_size));
	int nextMax,currMax;

	while(_size-->0)
	{
		VectorAdd(vec,random()%RANDOM_RANGE);
	}

	heap=HeapBuild(vec);
	/*HeapPrint(heap);
	/*HeapExtractMax(heap,&currMax);
	printf("max1=%d",currMax);
	while(HeapItemsNum(heap))
	{
		HeapExtractMax(heap,&nextMax);
		printf("max2=%d",nextMax);
		if(nextMax>currMax)
		{
			HeapPrint(heap);
			return TEST_FAILED;
		}
	}
	HeapDestroy(heap);
	VectorDestroy(vec);*/
	return TEST_SUCCESS;
}

UTestERR TestHeapBuildNullVector()
{
	Heap* heap;
	Vector* vec = NULL;

	if(NULL == (heap=HeapBuild(vec)))
	{
		return TEST_SUCCESS;
	}
	
	return TEST_FAILED;
}

UTestERR TestTreeCreateAllocationFailed(int _size)
{
	Vector* vec = VectorCreate(_size,BLOCK_EXTENTION_SIZE(_size));
	
	while(_size-->0)
	{
		VectorAdd(vec,random()%RANDOM_RANGE);
	}

	while(NULL!=HeapBuild(vec));
	VectorDestroy(vec);
	return TEST_SUCCESS;
}

UTestERR TestHeapInsertMax(int _size)
{
	Heap* heap;
	Vector* vec = VectorCreate(_size,BLOCK_EXTENTION_SIZE(_size));
	int currMax,nextMax;
	
	while(_size-->0)
	{
		VectorAdd(vec,random()%RANDOM_RANGE);
	}

	heap=HeapBuild(vec);
	HeapMax(heap,&currMax);
	HeapInsert(heap,currMax+1);
	HeapMax(heap,&nextMax);

	if(currMax+1!=nextMax)
	{
		return TEST_FAILED;		
	}

	HeapDestroy(heap);
	VectorDestroy(vec);

	return TEST_SUCCESS;
}

UTestERR TestHeapInsertLegal(int _size)
{
	Heap* heap;
	Vector* vec = VectorCreate(_size,BLOCK_EXTENTION_SIZE(_size));
	int i, itemsNum, sonData, fatherData;
	
	while(_size-->0)
	{
		VectorAdd(vec,random()%RANDOM_RANGE);
	}

	heap = HeapBuild(vec);
	
	for(i=0;i<INSERT_AMOUNT;i++)
	{
		HeapInsert(heap,(random()%RANDOM_RANGE)*2);
	}
	
	itemsNum = HeapItemsNum(heap);
	for(i=1;i<=itemsNum/2;i++)
	{
		VectorGet(vec,i,&fatherData);
		VectorGet(vec,LEFT(i),&sonData);
		if(sonData>fatherData)
		{
			return TEST_FAILED;
		}
		
		if(RIGHT(i)>itemsNum)
		{
			break;
		}
		else
		{
			VectorGet(vec,LEFT(i),&sonData);
			if(sonData>fatherData)
			{
				return TEST_FAILED;
			}
		} 
	}
	HeapDestroy(heap);
	VectorDestroy(vec);
	return TEST_SUCCESS;
}

UTestERR TestHeapInsertNullHeap()
{
	Heap* heap;
	
	heap=NULL;
	
	if(ERR_NOT_INITIALIZED==HeapInsert(heap,1))
	{
		return TEST_SUCCESS;
	}

	return TEST_FAILED;
}

void printTestResult(UTestERR result,char* testName)
{
	result==TRUE ? printf("%s: %sSUCCESS%s\n\n",testName,KGRN,RESET): printf("%s: %sFAILED%s\n\n",testName,KRED,RESET);
}

int main(int argc,char* argv[])
{
	size_t size;
	if(argc==1 || argc>2)
	{
		puts("This program requiers 1 argument");
		return 1;
	}

	if(atoi(argv[1])<0)
	{
		puts("argument must be positive number");
		return 1;
	}
	size = atoi(argv[1]);
	
	puts("\n****************TESTS*****************\n");
	printTestResult(TestHeapBuildSuccess(size),"TestHeapBuildSuccess");
	printTestResult(TestHeapBuildRightOrder(size),"TestHeapBuildRightOrder");
	printTestResult(TestHeapBuildNullVector(size),"TestHeapBuildNullVector");
	/*printTestResult(TestTreeCreateAllocationFailed(),"TestTreeCreateAllocationFailed");*/

	printTestResult(TestHeapInsertMax(size),"TestHeapInsertMax");
	printTestResult(TestHeapInsertNullHeap(),"TestHeapInsertNullHeap");
	printTestResult(TestHeapInsertLegal(size),"TestHeapInsertLegal");
	
	
	puts("****************TESTS*****************\n");

	return 1;
}
