#include <stdio.h>
#include <string.h>
#define SIZE 3
#define NAME_SIZE 20
#define FALSE 0 
#define TRUE !FALSE
typedef int result;
typedef result (*FuncPtr_t)(int a, int b);

typedef struct pair
{
	FuncPtr_t function;
	char funcName[NAME_SIZE];
}Pair;


result sum(int _a,int _b)
{
	return _a+_b;
}

result sub(int _a,int _b)
{
	return _a-_b;
}

result mult(int _a,int _b)
{
	return _a*_b;
}


int main(int argc,char* argv[])
{

	Pair funcPair[SIZE];
	int option=1;
	int a,b;

	funcPair[0].function = sum;
	funcPair[1].function = sub;
	funcPair[2].function = mult;
	strcpy(funcPair[0].funcName,"sum");
	strcpy(funcPair[1].funcName,"sub");
	strcpy(funcPair[2].funcName,"mult");

	while(TRUE)
	{
		puts("Options:");
		puts("	1:sum");
		puts("	2:sub");
		puts("	3:mult");
		puts("	0:exit");
	
		puts("\nInsert an option:");
		scanf("%d",&option);
		if(!option)
		{
			break;
		}
		
		if(option>3)
		{
			puts("Invalid input, Try again");
			continue;
		}

		puts("\nInsert two numbers:");
		scanf("%d %d",&a,&b);
		printf("%s = %d\n",funcPair[option-1].funcName,funcPair[option-1].function(a,b));
	}
}
