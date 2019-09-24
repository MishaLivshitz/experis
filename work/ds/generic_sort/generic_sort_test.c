#include <stdio.h>
#include <stddef.h>
#include "generic_sort.h"

#define 	ASIZE(A) sizeof(A)/sizeof(*(A))

int IntIsLess(const void* _a,const void* _b)
{
	return *(int*)_a> *(int*)_b;
}

int CharIsLess(const void* _a,const void* _b)
{
	return *(char*)_a> *(char*)_b;
}

int main()
{
	int arrInt[] = {4,6,3,2,8,0,7,9,1200,10,11}; 
	size_t sizeInt = ASIZE(arrInt);

	char arrChar[] = {'m','i','c','h','a','e','l'}; 
	size_t sizeChar = ASIZE(arrChar);
	int i;

	Sort(arrInt,sizeInt,sizeof(int),IntIsLess);

	for(i=0;i<sizeInt;i++)
	{
		printf("%d ",arrInt[i]);
	}
	printf("\n");

	Sort(arrChar,sizeChar,sizeof(char),CharIsLess);

	for(i=0;i<sizeChar;i++)
	{
		printf("%c ",arrChar[i]);
	}
	printf("\n");

	return 1;
}
