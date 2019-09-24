#include "mu_test.h"
#include "list.h"
#include "list_itr.h"
#include <stdlib.h>
#include <stdio.h>


typedef enum
{
	 SIZE
	,VALUE
	,EMPTY
}Context_type;

void DestroyInt(int* item)
{
	free(item);
}

int FindInt(int* _item, int* _context)
{
	return *_item == *_context;
}

List* SetUp(void* _context, Context_type _cType)
{
	int dataArr[] = {1,2,3,4};
	int i;
	int* data; 
	size_t size = sizeof(dataArr)/sizeof(*dataArr);
	List* list = List_Create();
	
	for(i=0;i<size;i++)
	{
		data = malloc(sizeof(int));
		*data = dataArr[i];
		List_PushTail(list,data);
	}
	
	switch(_cType)
	{
		case VALUE:
			*(int*)_context = dataArr[2];
			break;
			
		case SIZE:
			*(int*)_context = size;
			break;
			
		default:
			break;
	}
	
	return list;
}

UNIT(List_CreateSuccess)

	List* list = List_Create();
	
	ASSERT_THAT(NULL != list);

	List_Destroy(list,(AdtItemDestroy)DestroyInt);

END_UNIT


UNIT(List_DestroySuccess)

	int dataArr[] ={1,2,3};
	int size = sizeof(dataArr)/sizeof(*dataArr);
	int* data; 
	List* list = List_Create();

	while(--size>=0)
	{
		data = malloc(sizeof(int));
		*data=dataArr[size];
		List_PushHead(list,data);
	}
	
	List_Destroy(list,(AdtItemDestroy)DestroyInt);
	ASSERT_THAT(List_IsEmpty(list));
	List_Destroy(list,(AdtItemDestroy)DestroyInt);

END_UNIT

UNIT(List_NotInitialized)

	int* data = malloc(sizeof(int));
	List* list = List_Create();
	
	ASSERT_THAT(LIST_UNDERFLOW == List_PopHead(list,NULL));
	ASSERT_THAT(LIST_UNDERFLOW == List_PopTail(list,NULL));
	
	List_PushHead(list,(AdtItem)data);
	ASSERT_THAT(LIST_INVALID_ARGUMENT == List_PopTail(list,NULL));
	ASSERT_THAT(LIST_INVALID_ARGUMENT == List_PopHead(list,NULL));
	List_Destroy(list,(AdtItemDestroy)DestroyInt);

	ASSERT_THAT(LIST_NOT_INITIALIZED == List_PushHead(list,data));
	ASSERT_THAT(LIST_NOT_INITIALIZED == List_PopHead(list,(AdtItem)&data));
	ASSERT_THAT(LIST_NOT_INITIALIZED == List_PushTail(list,data));	
	ASSERT_THAT(LIST_NOT_INITIALIZED == List_PopTail(list,(AdtItem)&data));
	ASSERT_THAT(-1 == List_Size(list));
	ASSERT_THAT(List_IsEmpty(list));

END_UNIT


UNIT(List_PushPopHead)

	int dataArr[] = {1,2,3,4};
	int i;
	int* returnedData;
	int* data; 
	size_t size = sizeof(dataArr)/sizeof(*dataArr);
	List* list = List_Create();
	
	for(i=0;i<size;i++)
	{
		data = malloc(sizeof(int));
		*data = dataArr[i];
		List_PushHead(list,data);
	}

	while(--i>=0)
	{	
		List_PopHead(list,(AdtItem)&returnedData);
		ASSERT_THAT(dataArr[i]==*returnedData);
	}

	List_Destroy(list,(AdtItemDestroy)DestroyInt);
	
END_UNIT

UNIT(List_PushPopTail)
	
	int dataArr[] = {1,2,3,4};
	int i;
	int* returnedData;
	int* data; 
	size_t size = sizeof(dataArr)/sizeof(*dataArr);
	List* list = List_Create();
	
	for(i=0;i<size;i++)
	{
		data = malloc(sizeof(int));
		*data = dataArr[i];
		List_PushTail(list,data);
	}

	while(--i>=0)
	{	
		List_PopTail(list,(AdtItem)&returnedData);
		ASSERT_THAT(dataArr[i]==*returnedData);
	}

	List_Destroy(list,(AdtItemDestroy)DestroyInt);
	
END_UNIT


UNIT(List_PushHeadPopTail)

	int dataArr[] = {1,2,3,4};
	int i;
	int* returnedData;
	int* data; 
	size_t size = sizeof(dataArr)/sizeof(*dataArr);
	List* list = List_Create();
	
	for(i=0;i<size;i++)
	{
		data = malloc(sizeof(int));
		*data = dataArr[i];
		List_PushHead(list,data);
	}
	
	for(i=0;i<size;i++)
	{	
		List_PopTail(list,(AdtItem)&returnedData);
		ASSERT_THAT(dataArr[i]==*returnedData);
	}

	List_Destroy(list,(AdtItemDestroy)DestroyInt);

END_UNIT


UNIT(List_PushTailPopHead)
	
	int dataArr[] = {1,2,3,4};
	int i;
	int* returnedData;
	int* data; 
	size_t size = sizeof(dataArr)/sizeof(*dataArr);
	List* list = List_Create();
	
	for(i=0;i<size;i++)
	{
		data = malloc(sizeof(int));
		*data = dataArr[i];
		List_PushTail(list,data);
	}
	
	for(i=0;i<size;i++)
	{	
		List_PopHead(list,(AdtItem)&returnedData);
		ASSERT_THAT(dataArr[i]==*returnedData);
	}

	List_Destroy(list,(AdtItemDestroy)DestroyInt);

END_UNIT


UNIT(List_IsEmptyCheck)

	
	List* list = SetUp(NULL,EMPTY);

	ASSERT_THAT(!List_IsEmpty(list));
	
	List_Destroy(list,(AdtItemDestroy)DestroyInt);
	
END_UNIT

UNIT(List_SizeCheck)

	int size;
	List* list = SetUp(&size,SIZE);
	
	ASSERT_EQUAL_INT(List_Size(list), size);
	List_Destroy(list,(AdtItemDestroy)DestroyInt);
	
END_UNIT

UNIT(List_FindFirst)

	int val;
	ListItr itr;
	List* list = SetUp(&val,VALUE);

	itr = ListItr_FindFirst(ListItr_Begin(list),ListItr_End(list),(AdtItemPredicate)FindInt,(AdtItem)&val);
	ASSERT_EQUAL_INT(*(int*)ListItr_Get(itr),val);
	
	List_Destroy(list,(AdtItemDestroy)DestroyInt);

END_UNIT

UNIT(List_InsertMiddle)

	ListItr itr;
	int size;
	List* list = SetUp(&size,SIZE);
	int* newData = malloc(sizeof(int));
	size_t i;
	
	*newData = 5;
	
	for(i=0,itr = ListItr_Begin(list);i<size/2;i++)
	{
		itr = ListItr_Next(itr);
	}
	
	itr = ListItr_Insert(itr,(AdtItem)newData);
	
	ASSERT_EQUAL_INT(*(int*)ListItr_Get(itr),*newData);
	ASSERT_EQUAL_INT(size+1,List_Size(list));
	
	for(i=0,itr = ListItr_Begin(list);i<size/2;i++)
	{
		itr = ListItr_Next(itr);
	}
	
	ASSERT_EQUAL_INT(*(int*)ListItr_Get(itr),*newData);
	
	List_Destroy(list,(AdtItemDestroy)DestroyInt);

END_UNIT


UNIT(List_RemoveMiddle)

	ListItr itr;
	int size;
	List* list = SetUp(&size,SIZE);
	int removedData;
	size_t i;
	
	for(i=0,itr = ListItr_Begin(list);i<size/2;i++)
	{
		itr = ListItr_Next(itr);
	}
	
	removedData = *(int*)ListItr_Get(itr);
	
	ASSERT_EQUAL_INT(*(int*)ListItr_Remove(itr),removedData);
	ASSERT_EQUAL_INT(size-1,List_Size(list));

	List_Destroy(list,(AdtItemDestroy)DestroyInt);

END_UNIT


TEST_SUITE(Generic DLlist Module Unit Test)
	
	TEST(List_CreateSuccess)
	TEST(List_DestroySuccess)
	TEST(List_NotInitialized)
	TEST(List_PushPopHead)
	TEST(List_PushPopTail)
	TEST(List_PushHeadPopTail)
	TEST(List_PushTailPopHead)
	TEST(List_IsEmptyCheck)
	TEST(List_SizeCheck)
	TEST(List_FindFirst)
	TEST(List_InsertMiddle)
	TEST(List_RemoveMiddle)
	
END_SUITE

