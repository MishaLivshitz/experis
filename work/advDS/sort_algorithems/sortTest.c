#include "vector.h"
#include <string.h>
#include "UTestERR.h"
#include "sort.h"
#include <time.h>

#define NUM_OF_ALGS 10
#define FUNC_NAME_LEN 50
#define VEC_SIZE 10
#define RAND_RANGE 10000
#define ITERATIONS_NUM 5
/*gcc -ansi -pedantic -I ../include/ ../vector/vector.c *.c -g*/
typedef UTestERR(*FuncPtr)(time_t* _time,Vector* _vec);

UTestERR CheckDecsending(Vector* _vec)
{
	int currItem,prevItem;
	size_t numOfItems;
	
	VectorItemsNum(_vec,&numOfItems);
	VectorGet(_vec,numOfItems,&currItem);
	while(--numOfItems)
	{
		VectorGet(_vec,numOfItems,&prevItem);
		if(prevItem>currItem)
		{
			return TEST_FAILED;
		}
		currItem=prevItem;
	}

	return TEST_SUCCESS;
}

UTestERR TestShakeSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;
	
	*_algTimes = clock();
	if(ERR_OK!=ShakeSort(_vec))
	{
		return TEST_FAILED;
	}
	*_algTimes = (clock() - *_algTimes);
	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestQuickSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;
	size_t numOfItems;

	VectorItemsNum(_vec,&numOfItems);

	*_algTimes = clock();
	if(ERR_OK!=QuickSort(_vec,1,numOfItems))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;
	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestInsertionSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;
	
	*_algTimes = clock();
	if(ERR_OK!=InsertionSort(_vec))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;
	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestShellSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;

	*_algTimes = clock();
	if(ERR_OK!=ShellSort(_vec))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;

	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestSelectionSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;

	*_algTimes = clock();
	if(ERR_OK!=SelectionSort(_vec))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;

	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestMergeSortInPlace(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;

	*_algTimes = clock();
	if(ERR_OK!=MergeSortRec(_vec,TRUE))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;
	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestMergeSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;

	*_algTimes = clock();
	if(ERR_OK!=MergeSortRec(_vec,FALSE))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;

	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestCountingSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;

	*_algTimes = clock();
	
	if(ERR_OK!=CountingSort(_vec,RAND_RANGE,ZERO_EXTRACTOR))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;
	
	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestRadixSort(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;

	*_algTimes = clock();

	if(ERR_OK!=RadixSort(_vec,DECIMAL_BASE))
	{
		return TEST_FAILED;
	}
	*_algTimes = clock() - *_algTimes;
	
	testStatus = CheckDecsending(_vec);

	return testStatus;
}

UTestERR TestMergeSortIterative(time_t* _algTimes,Vector* _vec)
{
	UTestERR testStatus;

	*_algTimes = clock();
	
	if(ERR_OK!=MergeSortIterative(_vec,FALSE))
	{
		return TEST_FAILED;
	}
	
	*_algTimes = clock() - *_algTimes;
	
	testStatus = CheckDecsending(_vec);

	return testStatus;
}

void printTestResult(UTestERR result)
{
	result==TRUE ? printf("Test:%sSUCCESS%s",KGRN,RESET): printf("Test:%sFAILED%s\n\n",KRED,RESET);
}

int main(int argc,char* argv[])
{
	
	size_t i,j,k,numOfItems=VEC_SIZE;
	FuncPtr function[NUM_OF_ALGS];
	char funcNames[NUM_OF_ALGS][FUNC_NAME_LEN];
	time_t algTime;
	VectorPtr vector;

	function[0]=TestShakeSort;
	function[1]=TestQuickSort;
	function[2]=TestInsertionSort;
	function[3]=TestShellSort;
	function[4]=TestSelectionSort;
	function[5]=TestMergeSortInPlace;
	function[6]=TestMergeSort;
	function[7]=TestMergeSortIterative;
	function[8]=TestCountingSort;
	function[9]=TestRadixSort;

	strcpy(funcNames[0],"ShakeSort");
	strcpy(funcNames[1],"QuickSort");
	strcpy(funcNames[2],"InsertionSort");
	strcpy(funcNames[3],"ShellSort");
	strcpy(funcNames[4],"SelectionSort");
	strcpy(funcNames[5],"MergeSortInPlace");
	strcpy(funcNames[6],"MergeSort");
	strcpy(funcNames[7],"MergeSortIterative");
	strcpy(funcNames[8],"CountingSort");
	strcpy(funcNames[9],"RadixSort");

	puts("\n****************TESTS*****************\n");
	
	for(j=0;j<NUM_OF_ALGS;j++)
	{
		printf("\n\n%s:\n",funcNames[j]);
		for(i=0;i<ITERATIONS_NUM;i++,numOfItems*=10)
		{	
			vector=VectorCreate(numOfItems, numOfItems/2);
			for(k=0;k<numOfItems;k++)
			{
				VectorAdd(vector,rand() % RAND_RANGE);
			}
			
			printTestResult(function[j](&algTime,vector));
			printf(" - Items: %7ld Time: %10lu\n",numOfItems,algTime);
			VectorDestroy(vector);
		}
		numOfItems=VEC_SIZE;
	}

	puts("****************TESTS*****************\n");

	

	return 1;
}
