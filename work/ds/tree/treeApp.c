#include "tree.h"
#include "UTestERR.h"



UTestERR TestTreeCreateSuccess()
{
	UTestERR status = TEST_SUCCESS;
	Tree* tree;

	if(NULL== (tree=TreeCreate()))
	{
		status = TEST_FAILED;
	}

	TreeDestroy(tree);
	return status;
}

UTestERR TestTreeCreateFailed()
{
	while(NULL!=TreeCreate());

	return TEST_SUCCESS;
}

UTestERR TestTreeDestroy()
{
	UTestERR status = TEST_SUCCESS;
	int data = 0;
	Tree* tree = TreeCreate();

	TreeInsert(tree,data++);	
	TreeInsert(tree,data++);
	TreeInsert(tree,data++);

	TreeDestroy(tree);
	TreeDestroy(tree);

	return status;
}

UTestERR TestTreeInsertAllocationFailed()
{
	int data = 0;
	Tree* tree = TreeCreate();

	while(ERR_ALLOCATION_FAILED!=TreeInsert(tree,data++));

	return TEST_SUCCESS;
}

UTestERR TestTreeInsertExist()
{
	int data = 5;
	int i;
	size_t size = sizeof(data)/sizeof(int);
	Tree* tree = TreeCreate();

	TreeInsert(tree,data);
	if(ERR_EXIST==TreeInsert(tree,data))
	{
		return TEST_SUCCESS;
	}
	
	return TEST_FAILED;
}

UTestERR TestTreeInsertSuccess()
{
	int data[] = {10,5,8,4,2,1,20,12,14};
	int i;
	size_t size = sizeof(data)/sizeof(int);
	 
	Tree* tree = TreeCreate();
	
	for(i=0;i<size;i++)
	{
		TreeInsert(tree,data[i]);
	}

	for(i=0;i<size;i++)
	{
		if(!TreeIsDataFound(tree,data[i]))
		{
			return TEST_FAILED;
		}
	}

	return TEST_SUCCESS;
}

UTestERR TestTreeInsertLegal()
{
	int i;
	int num;
	int nextNum;
	FILE* file;
	int data[] = {10,5,8,4,2,50,20,12,14};
	size_t size = sizeof(data)/sizeof(int);
	UTestERR status = TEST_SUCCESS;
	Tree* tree = TreeCreate();
	
	for(i=0;i<size;i++)
	{
		TreeInsert(tree,data[i]);
	}

	TreePrint(tree,IN_ORDER);

	file = fopen(FILE_NAME,"r");
	fscanf(file, "%d", &num);
	while(!feof(file))
	{
		fscanf(file, "%d", &nextNum);
		if(num>nextNum)
		{
			status = TEST_FAILED;
			break;
		}
		num=nextNum;
	}
	
	fclose(file);
	return status;
}

UTestERR TestTreeInsertNullTree()
{
	int data = 1;
	Tree* tree = NULL;
	
	if(ERR_NOT_INITIALIZED != TreeInsert(tree,data))
	{
		return TEST_FAILED;
	}

	return TEST_SUCCESS;
}

UTestERR TestTreeIsDataFound()
{
	int data[] = {10,5,8,4};
	int i;
	size_t size = sizeof(data)/sizeof(int);
	Tree* tree = TreeCreate();
	
	for(i=0;i<size;i++)
	{
		TreeInsert(tree,data[i]);
	}
	
	if(TreeIsDataFound(tree,7))
	{
		return TEST_FAILED;
	}

	for(i=0;i<size;i++)
	{
		if(!TreeIsDataFound(tree,data[i]))
		{
			return TEST_FAILED;
		}
	}

	return TEST_SUCCESS;
}

UTestERR TestTreeIsDataFoundNullTree()
{
	int data = 1;
	Tree* tree = NULL;
	
	if(TreeIsDataFound(tree,data))
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
	printTestResult(TestTreeCreateSuccess(),"TestTreeCreateSuccess");
	/*printTestResult(TestTreeCreateFailed(),"TestTreeCreateFailed");*/
	printTestResult(TestTreeDestroy(),"TestTreeDestroy");

	/*printTestResult(TestTreeInsertAllocationFailed(),"TestTreeInsertAllocationFailed");*/
	printTestResult(TestTreeInsertExist(),"TestTreeInsertExist");
	printTestResult(TestTreeInsertNullTree(),"TestTreeInsertNullTree");
	printTestResult(TestTreeInsertSuccess(),"TestTreeInsertSuccess");
	printTestResult(TestTreeInsertLegal(),"TestTreeInsertLegal");

	printTestResult(TestTreeIsDataFound(),"TestTreeIsDataFound");
	printTestResult(TestTreeIsDataFoundNullTree(),"TestTreeIsDataFoundNullTree");
	
	puts("****************TESTS*****************\n");

	return 1;
}
