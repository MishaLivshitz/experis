#include "mu_test.h"
#include "heap.h"
#include <stdlib.h>

#define VEC_SIZE 10
#define BLOCK_EXTENTION_SIZE(size) (size)/2+1
#define RANDOM_RANGE 100
#define INSERT_AMOUNT 5

#define FATHER(I) (I)/2
#define LEFT(I) (I)*2
#define RIGHT(I) (I)*2+1

#ifdef DEBUG
#define PRINT(x) printf("%d ",x)
#else
#define PRINT(x,y)
#endif /*DEBUG*/

void IntDestroy(int* _item)
{
	return;
}

int IsGreater(const int* _firstKey,const int* _secondKey,int* _context)
{
	return *_firstKey > *_secondKey;
}

void KeyDestroy(void* _key)
{
	return;
}

int PrintInt(const int* _val ,void* _context)
{
		PRINT(*_val);
		return 1;
}

UNIT(heap_BuildSuccess)

	Heap* heap;
	
	int arr[] = {23,43,5,26,87,4,2,97,12};
	size_t size = sizeof(arr)/sizeof(*arr);
	Vector* vec = Vector_Create(size, BLOCK_EXTENTION_SIZE(size));
	int i;
	
	for(i=0;i<size;i++)
	{
		Vector_Add(vec,&arr[i]);
	}

	heap=Heap_Build(vec,(AdtItemCompare)IsGreater);
	ASSERT_NOT_EQUAL_PTR(NULL,heap);
	Heap_Destroy(heap);
	Vector_Destroy(vec,(AdtItemDestroy)KeyDestroy);
	
END_UNIT

UNIT(Heap_BuildRightOrder)

	Heap* heap;
	int arr[] = {23,43,5,26,87,4,2,97,12};
	size_t size = sizeof(arr)/sizeof(*arr);
	Vector* vec = Vector_Create(size, BLOCK_EXTENTION_SIZE(size));
	int i;
	int* currMax;
	int* nextMax;
	
	for(i=0;i<size;i++)
	{
		Vector_Add(vec,&arr[i]);
	}

	heap=Heap_Build(vec,(AdtItemCompare)IsGreater);

	currMax = Heap_Extract(heap);
	ASSERT_EQUAL_INT(97,*currMax);
	
	while(Heap_Size(heap))
	{
		nextMax = Heap_Extract(heap);
		ASSERT_THAT(IsGreater(currMax,nextMax,NULL));
		currMax = nextMax ;
	}
	
	Heap_Destroy(heap);
	Vector_Destroy(vec,(AdtItemDestroy)KeyDestroy);
	
END_UNIT

UNIT(Heap_BuildNullVector)

	ASSERT_EQUAL_PTR(NULL ,Heap_Build(NULL,NULL));
	
END_UNIT


UNIT(Heap_InsertMaxTest)

	Heap* heap;
	int arr[] = {23,43,5,26,87,4,2,97,12};
	size_t size = sizeof(arr)/sizeof(*arr);
	Vector* vec = Vector_Create(size, BLOCK_EXTENTION_SIZE(size));
	int i;
	int* currMax;
	int* newMax;
	
	for(i=0;i<size;i++)
	{
		Vector_Add(vec,&arr[i]);
	}

	heap=Heap_Build(vec,(AdtItemCompare)IsGreater);
	
	currMax = Heap_Peek(heap);
	*currMax+=1;
	Heap_Insert(heap,currMax);
	newMax = Heap_Peek(heap);

	ASSERT_EQUAL_INT(*currMax, *newMax);
	
	Heap_Destroy(heap);
	Vector_Destroy(vec,(AdtItemDestroy)KeyDestroy);

END_UNIT


UNIT(Heap_InsertLegal)

	Heap* heap;
	int arr[] = {23,43,5,26,87,4,2,97,12};
	size_t size = sizeof(arr)/sizeof(*arr),itemsNum;
	Vector* vec = Vector_Create(size, BLOCK_EXTENTION_SIZE(size));
	int i;
	int* sonData;
	int* fatherData;
	
	for(i=0;i<size-3;i++)
	{
		Vector_Add(vec,&arr[i]);
	}

	heap=Heap_Build(vec,(AdtItemCompare)IsGreater);
	
	while(i<size)
	{
		Heap_Insert(heap,&arr[i++]);
	}
	
	itemsNum = Heap_Size(heap);
	ASSERT_EQUAL_INT(size,itemsNum);
	
	for(i=1;i<=itemsNum/2;i++)
	{
		Vector_Get(vec,i,(AdtItem)&fatherData);
		Vector_Get(vec,LEFT(i),(AdtItem)&sonData);
		
		ASSERT_THAT(!IsGreater(sonData,fatherData,NULL));
		if(RIGHT(i)>itemsNum)
		{
			break;
		}
		else
		{
			Vector_Get(vec,LEFT(i),(AdtItem)&sonData);
			ASSERT_THAT(!IsGreater(sonData,fatherData,NULL));
		} 
	}
	
	Heap_Destroy(heap);
	Vector_Destroy(vec,(AdtItemDestroy)KeyDestroy);
	
END_UNIT

UNIT(Heap_SortTest)

	int arr[] = {23,43,5,26,87,4,2,97,12};
	size_t size = sizeof(arr)/sizeof(*arr);
	Vector* vec = Vector_Create(size, BLOCK_EXTENTION_SIZE(size));
	int i;
	int numOfItems;
	int *currItem,*prevItem;
	
	for(i=0;i<size;i++)
	{
		Vector_Add(vec,&arr[i]);
	}
	
	Heap_Sort(vec,(AdtItemCompare)IsGreater);
	numOfItems = Vector_Size(vec);
	Vector_Get(vec,numOfItems,(AdtItem)&currItem);
	
	while(--numOfItems)
	{
		Vector_Get(vec,numOfItems,(AdtItem)&prevItem);
		ASSERT_THAT(!IsGreater(prevItem,currItem,NULL));
		*currItem=*prevItem;
	}
	
	Vector_Destroy(vec,(AdtItemDestroy)KeyDestroy);

END_UNIT

TEST_SUITE(Test Generic heap test)
	
	TEST(heap_BuildSuccess)
	TEST(Heap_BuildRightOrder)
	TEST(Heap_BuildNullVector)
	TEST(Heap_InsertMaxTest)
	TEST(Heap_InsertLegal)
	TEST(Heap_SortTest)

END_SUITE
