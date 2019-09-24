#include <stdio.h>
#include "stack.h"
#include "DLlist.h"

typedef unsigned int Uint;
typedef char byte;

typedef enum
{
	LEFT=0,
	RIGHT

}Side;

typedef enum
{
	EXIT = 0,
	CYCLIC,
	FLIP

}MenuCase;

void PrintBin(Uint _num)
{
	
	int mask = 1;
	int item;
	Stack* stack = StackCreate(sizeof(Uint)*8,0);

	if(NULL == stack)
	{
		return;
	}

	while(_num!=0)
	{
		StackPush(stack,_num&mask);
		_num >>= mask;
	}

	while(!StackIsEmpty(stack))
	{
		StackPop(stack,&item);
		printf("%d",item);
	}
	printf("\n");
}

void CyclicShift(Uint _num, Side _side, Uint _shiftNum)
{

	int tempNum =_num;
	List* dlList = ListCreate();

	
	while(_num!=0)
	{
		ListPushTail(dlList,_num&1);
		_num >>=1;
	}

	switch(_side)
	{
		case LEFT:
		while(_shiftNum--)
		{
			ListPopTail(dlList,&tempNum);
			ListPushHead(dlList,tempNum);
		}
	
		break;
		case RIGHT:

			while(_shiftNum--)
			{
				ListPopHead(dlList,&tempNum);
				ListPushTail(dlList,tempNum);
			}
			break;
	}

	while(!ListIsEmpty(dlList))
		{
			ListPopTail(dlList,&tempNum);
			_num = (_num<<1) + tempNum;
		}

	PrintBin(_num);
}


void flip(Uint _num, size_t _from,size_t _to)
{
	
	Uint mask =1;
	Uint i=0;
	mask <<=_from;

	while(i< _to - _from)
	{
		mask = mask  | mask << 1;
		i++;
	}

	_num ^= mask;
	PrintBin(_num);
}

int main()
{
	int option;
	Uint from;
	Uint to;
	Uint shifts;
	Uint num;

	
	while(EXIT!=option)
	{

	puts("\n****************BITS******************\n");
	puts("Options:");
	puts("	1:CyclicShift");
	puts("	2:flip");
	puts("	0:Exit");
	puts("\n****************BITS******************\n");
		
		puts("Insert option:\n");
		scanf("%d",&option);

		switch(option)
		{
			case CYCLIC:
				puts("Insert number, how many shifts and direction(0:LEFT, 1:RIGHT):\n");
				scanf("%u %u %d",&num,&shifts,&option);
				puts("Before:");
				PrintBin(num);
				puts("After:");
				CyclicShift(num,option,shifts);
				break;

			case FLIP:
				puts("Insert number, from bit and to bit\n");
				scanf("%u %u %u",&num,&from,&to);
				puts("Before:");
				PrintBin(num);
				puts("After:");
				flip(num,from,to);
				break;

			case EXIT:
				option = EXIT;
				break;
		}	
	}

	return 1;
}
