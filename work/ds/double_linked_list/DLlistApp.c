#include "DLlist.h"
#include "UTestERR.h"
#define MAX_NODES 10

UTestERR TestListCreate()
{
	UTestERR status = TEST_SUCCESS;
	List* list = ListCreate(MAX_NODES);
	
	if(!ListIsEmpty(list))
	{
		status = TEST_FAILED;
	}

	if(0 < ListCountItems(list))
	{
		status = TEST_FAILED;
	}

	ListDestroy(list);
	return status;
}

UTestERR TestListDestroy()
{
	UTestERR status = TEST_SUCCESS;
	size_t data = 0;
	List* list = ListCreate(MAX_NODES);

	ListPushHead(list,data++);	
	ListPushHead(list,data++);
	ListPushHead(list,data++);
	ListDestroy(list);

	if(!ListIsEmpty(list))
	{
		status = TEST_FAILED;
	}

	ListDestroy(list);

	return status;
}

UTestERR TestNullList()
{
	
	int data = 1;
	List* list = ListCreate(MAX_NODES);
	ListDestroy(list);

	if(ERR_NOT_INITIALIZED != ListPushHead(list,data))
	{
		return TEST_FAILED;
	}

	if(ERR_NOT_INITIALIZED != ListPopHead(list,&data))
	{
		return TEST_FAILED;
	}

	if(ERR_NOT_INITIALIZED != ListPushTail(list,data))
	{
		return TEST_FAILED;
	}

	if(ERR_NOT_INITIALIZED != ListPopTail(list,&data))
	{
		return TEST_FAILED;
	}

	if(0 != ListCountItems(list))
	{
		return TEST_FAILED;
	}

	if(!ListIsEmpty(list))
	{
		return TEST_FAILED;
	}
	
	return TEST_SUCCESS;
}

UTestERR TestListPushPopHead()
{
	
	int data[] = {1,2,3,4};
	int i,returnedData;
	size_t size = sizeof(data)/sizeof(int);
	List* list = ListCreate(MAX_NODES);
	
	for(i=0;i<size;i++)
	{
		ListPushHead(list,data[i]);
	}

	while(--i>=0)
	{	
		ListPopHead(list,&returnedData);
		if(data[i]!=returnedData)
		{
			ListDestroy(list);
			return TEST_FAILED;
		}
	}

	ListDestroy(list);
	return TEST_SUCCESS;
}

UTestERR TestListPushPopTail()
{
	
	int data[] = {1,2,3,4};
	int i,returnedData;
	size_t size = sizeof(data)/sizeof(int);
	List* list = ListCreate(MAX_NODES);
	
	for(i=0;i<size;i++)
	{
		ListPushTail(list,data[i]);
	}

	while(--i>=0)
	{	
		ListPopTail(list,&returnedData);
		if(data[i]!=returnedData)
		{
			ListDestroy(list);
			return TEST_FAILED;
		}
	}

	ListDestroy(list);
	return TEST_SUCCESS;
}


UTestERR TestListPushHeadPopTail()
{
	
	int data[] = {1,2,3,4};
	int i,returnedData;
	size_t size = sizeof(data)/sizeof(int);
	List* list = ListCreate(MAX_NODES);
	
	for(i=0;i<size;i++)
	{
		ListPushHead(list,data[i]);
	}
	
	i=0;
	while(i<size)
	{	
		ListPopTail(list,&returnedData);
		if(data[i++]!=returnedData)
		{
			ListDestroy(list);
			return TEST_FAILED;
		}
	}

	ListDestroy(list);
	return TEST_SUCCESS;
}

UTestERR TestListPushTailPopHead()
{
	
	int data[] = {1,2,3,4};
	int i,returnedData;
	size_t size = sizeof(data)/sizeof(int);
	List* list = ListCreate(MAX_NODES);
	
	for(i=0;i<size;i++)
	{
		ListPushTail(list,data[i]);
	}
	
	i=0;
	while(i<size)
	{	
		ListPopHead(list,&returnedData);
		if(data[i++]!=returnedData)
		{
			ListDestroy(list);
			return TEST_FAILED;
		}
	}

	ListDestroy(list);
	return TEST_SUCCESS;
}

UTestERR TestListIsEmpty()
{
	int data[] = {1,2,3,4};
	int i;
	size_t size = sizeof(data)/sizeof(int);
	List* list = ListCreate(MAX_NODES);
	
	for(i=0;i<size;i++)
	{
		ListPushTail(list,data[i]);
	}

	if(ListIsEmpty(list))
	{
		return TEST_FAILED;	
	}

	return TEST_SUCCESS;
}

UTestERR TestListCountItems()
{
	int data[] = {1,2,3,4};
	int i;
	size_t size = sizeof(data)/sizeof(int);
	List* list = ListCreate(MAX_NODES);
	
	for(i=0;i<size;i++)
	{
		ListPushTail(list,data[i]);
	}
	
	if(ListCountItems(list) != size)
	{
		return TEST_FAILED;	
	}

	return TEST_SUCCESS;
}

UTestERR TestListPopEmptyList()
{
	List* list = ListCreate(MAX_NODES);

	if (ERR_EMPTY != ListPopHead(list,NULL))
	{
		return TEST_FAILED;
	}
	
	if (ERR_EMPTY != ListPopTail(list,NULL))
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}


void printTestResult(UTestERR result,char* testName)
{
	result==TRUE ? printf("%s: %sSUCCESS%s\n\n",testName,KGRN,RESET): printf("%s: %sFAILED%s\n\n",testName,KRED,RESET);
}

int main()
{

	puts("\n****************TESTS*****************\n");
	printTestResult(TestListCreate(),"TestListCreate");
	printTestResult(TestListDestroy(),"TestListDestroy");
	printTestResult(TestNullList(),"TestNullList");

	printTestResult(TestListPushPopHead(),"TestListPushPopHead");
	printTestResult(TestListPushPopTail(),"TestListPushPopTail");
	printTestResult(TestListPushHeadPopTail(),"TestListPushHeadPopTail");
	printTestResult(TestListPushTailPopHead(),"TestListPushTailPopHead");
	printTestResult(TestListPopEmptyList(),"TestListPopEmptyList");

	printTestResult(TestListIsEmpty(),"TestListIsEmpty");
	printTestResult(TestListCountItems(),"TestListCountItems");
	puts("****************TESTS*****************\n");

	return 1;
}
