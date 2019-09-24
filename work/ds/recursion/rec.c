#include<stdio.h>
#include<string.h>
#define SIZE 20
#define HANOY_SIZE 3
#define TRUE 1
#define FALSE !TRUE
#include "queue.h"


typedef enum
{
	FIND_MAX = 1,
	IS_PALINDROM,
	FIB,
	HANOY,
	EXIT = 0
}MenuCase;

int FindMax(int* _arr,int _n)
{
	if(_n==1)
	{
		return _arr[0];
	}

	tempMax=FindMax(_arr+1, _n-1);

	if(_arr[0]>tempMax)
	{
		tempMax=_arr[0];
	}

	return tempMax;
}


int IsPalindrom(char* _strStart,char* _strEnd)
{
	
	if(_strStart>=_strEnd)
	{
		return TRUE;
	}
	
	if(*_strStart!=*_strEnd)
	{
		return FALSE;
	}
	
	IsPalindrom(_strStart+1,_strEnd-1);
}

int Fib(int n)
{

	if(n==0)
	{
		return 0;
	}
	if(n==1)
	{
		return 1;
	}
	
	return Fib(n-1)+Fib(n-2);
}

void Hanoy(Queue* _from,Queue* _to,Queue* _via, int n)
{
	int itemFrom=0;
	
	if(n==1)
	{
		QueuePop(_from,&itemFrom);
		QueuePush(_to,itemFrom);

		return;
	}
	
	Hanoy(_from,_via,_to,n-1);
	Hanoy(_from,_to,_via,1);
	Hanoy(_via,_to,_from,n-1);

	return;
}

int main()
{
	int arr[SIZE]={5,9,4,1,0,2,13,8,6,2,5};
	Queue *from,*to,*via;
	int option;
	char str[SIZE];	
	int n,i;
	int exitFlag = FALSE;
	
	while(FALSE==exitFlag)
	{

		puts("Test options:\n");
		puts("	1: FindMax");
		puts("	2: IsPalindrom");
		puts("	3: Fib");
		puts("	4: Hanoy");
		puts("	0: Quit");

		puts("\nInsert your selection and press Enter:\n");
		scanf("%d",&option);
		switch(option)
		{
			case FIND_MAX:
				printf("Max=%d\n",FindMax(arr,SIZE));
				break;

			case IS_PALINDROM:
				puts("\nInsert a string:\n");
				scanf("%s",str);
				getchar();
				IsPalindrom(str,str+strlen(str)-1) ? printf("IsPalindrom=True\n"):printf("IsPalindrom=False\n");
				break;

			case FIB:
				printf("Insert the the index of the wanted Fibonaccui number:");
				scanf("%d",&n);
				printf("Fib(%d)=%d\n",n,Fib(n));
				break;

			case HANOY:
				printf("Insert the the number of plates:");
				scanf("%d",&n);
				from = QueueCreate(n,n);
				to = QueueCreate(n,n);
				via = QueueCreate(n,n);
				for(i=n;i>0;i--)
				{
					QueuePush(from,i);
				}
				printf("\nBefore Hanoy:\n");

				printf("from:");
				QueuePrint(from);

				printf("to:");
				QueuePrint(to);

				printf("via:");
				QueuePrint(via);

				Hanoy(from,to,via,n);
				printf("\nAfter Hanoy:\n");

				printf("from:");
				QueuePrint(from);
				QueueDestroy(from);

				printf("to:");
				QueuePrint(to);
				QueueDestroy(to);

				printf("via:");
				QueuePrint(via);
				QueueDestroy(via);

				from=NULL;
				to=NULL;
				via=NULL;
				break;

			case EXIT:
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
	}


}
