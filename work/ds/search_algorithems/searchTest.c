#include "search.h"
#include "sort.h"
#include <string.h>
#include "UTestERR.h"
#define ALGS_NUM 2
#define FUNC_NAME_SIZE 50
#define VEC_SIZE 10
#define RAND_RANGE 1000
#define MIN_VALUE 100

typedef ADTErr(*FuncPtr)(Vector*,int,size_t*);


UTestERR TestSearchFound(Vector* _vec, FuncPtr _searchFunction)
{
	int item,itemCheck;
	size_t resIndex, checkIndex;
	
	checkIndex = rand()%VEC_SIZE+1;
	VectorGet(_vec,checkIndex,&item);

	if(ERR_NOT_FOUND==_searchFunction(_vec,item,&resIndex))
	{
		return TEST_FAILED;
	}
	
	VectorGet(_vec,resIndex,&itemCheck);	

	if(checkIndex!=resIndex || item!=itemCheck)
	{
		return TEST_FAILED;
	}
	
	return TEST_SUCCESS;
}

UTestERR TestSearchNotFound(Vector* _vec, FuncPtr _searchFunction)
{
	int item = 50;
	size_t resIndex;

	if(ERR_NOT_FOUND==_searchFunction(_vec,item,&resIndex))
	{
		return TEST_SUCCESS;
	}
	
	return TEST_FAILED;
}

UTestERR TestSearchError(Vector* _vec, FuncPtr _searchFunction)
{
	int item = 50;
	size_t resIndex;
	ADTErr status;

	if(ERR_OK==(status=_searchFunction(NULL,item,&resIndex)) || status == ERR_NOT_FOUND)
	{
		return TEST_FAILED;
	}

	if(ERR_OK==(status=_searchFunction(_vec,item,NULL)) || status == ERR_NOT_FOUND)
	{
		return TEST_FAILED;
	}
	
	return TEST_SUCCESS;
}


void printTestResult(UTestERR result,char* testNamePreFix,char* testNamePostFix)
{
	result==TRUE ? printf("%s%s: %sSUCCESS%s\n\n",testNamePreFix,testNamePostFix,KGRN,RESET): printf("%s%s: %sFAILED%s\n\n",testNamePreFix,testNamePostFix,KRED,RESET);
}

int main()
{

	FuncPtr functions[ALGS_NUM]={LinearSearch,BinarySearch};
	char* funcNames[ALGS_NUM] = {"TestLinearSearch","TestBinarySearch"};
	Vector* vec = NULL;
	Vector* tempVec = NULL;
	int i;

	vec = VectorCreate(VEC_SIZE,VEC_SIZE/2);
	if(NULL==vec)
	{
		exit(1);
	}

	for(i=0;i<VEC_SIZE;i++)
	{
		VectorAdd(vec,rand()%RAND_RANGE+MIN_VALUE);	
	}
	

	puts("\n****************TESTS*****************\n");
	for(i=0;i<ALGS_NUM;i++)
	{

		if(0==strcmp(funcNames[i],"TestBinarySearch"))
		{
			tempVec=VectorCopy(vec,tempVec);
			CountingSort(tempVec,RAND_RANGE+MIN_VALUE,ZERO_EXTRACTOR);
			printTestResult(TestSearchFound(tempVec,functions[i]),funcNames[i],"Found");
			printTestResult(TestSearchNotFound(tempVec,functions[i]),funcNames[i],"NotFound");
			printTestResult(TestSearchError(tempVec,functions[i]),funcNames[i],"Error");
			VectorDestroy(tempVec);
		}
		else
		{
			printTestResult(TestSearchFound(vec,functions[i]),funcNames[i],"Found");
			printTestResult(TestSearchNotFound(vec,functions[i]),funcNames[i],"NotFound");
			printTestResult(TestSearchError(vec,functions[i]),funcNames[i],"Error");
		}
	}

	puts("****************TESTS*****************\n");

	VectorDestroy(vec);

	return 1;
}
