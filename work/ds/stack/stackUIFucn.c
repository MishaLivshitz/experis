
#include "ADTErr.h"
#include "stackUI.h"



static status IsLeftParenthese(char _ch)
{
	char* openParentheses = "{[(";
	
	while(*openParentheses!='\0')
	{
		if(_ch ==*openParentheses)
		{
			return TRUE;
		}
		openParentheses++;
	}
	return FALSE;
}

static status IsParenthesesMatch(char _stackChar,char _expChar)
{
	int isMatch=FALSE;
	
	switch(_stackChar)
	{
		case '{':
		isMatch = _expChar == '}';
		break;
		case '(':
		isMatch = _expChar == ')';
		break;
		case '[':
		isMatch= _expChar == ']';
		break;
	}
	return isMatch;
}

static status isNum(char _ch)
{
	if(_ch - '0' >= 0 && _ch - '0' < 10)
	{
		return TRUE;
	}
	return FALSE;
}

UTestERR TestStackCreateSucces()
{

	Stack* stack;
	stack=StackCreate(5, 10);
	if (NULL != stack)
	{
		puts("create stack test -> SUCCES!");
		return TEST_SUCCES;
	}
	puts("create stack test -> FAILED!\n");
	return TEST_FAILED;

}

UTestERR TestStackCreateInitSize()
{
	Stack* stack;
	stack=StackCreate(0, 10);
	if (NULL == stack)
	{
		puts("Initial size = 0 test -> SUCCES!");
		return TEST_SUCCES;
	}
	puts("Initial size = 0 test -> FAILED!\n");
	return TEST_FAILED;
}

UTestERR TestStackCreateBigMemAllocation()
{
	Stack* stack;
	stack=StackCreate(BIG_ALLOCATION_SIZE, 10);
	if (NULL == stack)
	{
		puts("Memory allocation failed test -> SUCCES!");
		return TEST_SUCCES;
	}
		
	puts("Memory allocation failed test -> FAILED!\n");
	return TEST_FAILED;
}

UTestERR TestStackPushOverflow()
{

	Stack* stack;
	ADTErr status;

	stack = StackCreate(1, 0);
	StackPush(stack,8);
	status = StackPush(stack,5);
	StackDestroy(stack);

	if(ERR_OVERFLOW == status)
	{
		puts("Overflow test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("Overflow test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestStackPushReallocFailed()
{

	Stack* stack;
	ADTErr status;

	stack = StackCreate(1, BIG_ALLOCATION_SIZE);
	StackPush(stack,8);
	status = StackPush(stack,8);
	StackDestroy(stack);

	if(ERR_REALLOCATION_FAILED == status)
	{
		puts("Memory reallocation failed test -> SUCCES!");
		
		return TEST_SUCCES;
	}

	puts("Memory reallocation failed test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestStackPushSucces()
{

	Stack* stack;
	int item = 8;
	int getItem;

	ADTErr status;
	stack = StackCreate(1, 2);
	StackPush(stack,item);

	StackTop(stack,&getItem);
	StackDestroy(stack);

	if(item == getItem)
	{
		puts("push test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("push test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestStackPopItem()
{
	Stack* stack;
	int item = 8;
	int getItem;

	ADTErr status;
	stack = StackCreate(1, 2);
	StackPush(stack,item);
	StackPop(stack,&getItem);
	StackDestroy(stack);

	if(item == getItem)
	{
		puts("pop item test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("pop item test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestPopItem()
{
	Stack* stack;
	int item = 8;
	int getItem;

	stack = StackCreate(1, 2);
	StackPush(stack,item);
	StackPop(stack,&getItem);
	StackDestroy(stack);
	
	if(item == getItem)
	{
		puts("Get item test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("Get item test -> FAILED!");
	return TEST_FAILED;
}

UTestERR TestStackTop()
{
	Stack* stack;
	int item = 8;
	int getItem;

	stack = StackCreate(1, 2);
	StackPush(stack,item);
	StackTop(stack,&getItem);
	StackDestroy(stack);
	
	if(item == getItem)
	{
		puts("Top item test -> SUCCES!");
		return TEST_SUCCES;
	}

	puts("Top item test -> FAILED!");
	return TEST_FAILED;
	
}

void TestNullStack()
{
	Stack* stack;
	UTestERR status = TEST_SUCCES;
	int item=5;
	int nItems;
	stack = NULL;
	
	if(ERR_NOT_INITIALIZED != StackPush(stack,item))
	{
		puts("StackPush null stack test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(ERR_NOT_INITIALIZED != StackPop(stack,&item))
	{
		puts("StackPop null stack test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(ERR_NOT_INITIALIZED != StackTop(stack,&item))
	{
		puts("StackTop null stack test -> FAILED!");
		status &=TEST_FAILED; 
	}

	if(ERR_NOT_INITIALIZED != StackIsEmpty(stack))
	{
		puts("StackIsEmpty null stack test -> FAILED!");
		status &=TEST_FAILED; 
	}
	
	if(status == TEST_SUCCES)
	{
		puts("TestNullStack -> SUCCES!");
	}
}

status CheckParentheses(Stack* _stack,char* _expression)
{
	int item;

	if(NULL != _stack)
	{	
		while(*_expression!='\0')
		{
			if(TRUE == IsLeftParenthese(*_expression))
			{
				StackPush(_stack,*_expression);
			}
			else
			{	
				StackPop(_stack,&item);
				if(FALSE==IsParenthesesMatch(item,*_expression))
				{	
					return FALSE;
				}
			}
		
		_expression++;
		}	
		if(StackIsEmpty(_stack))
		{
			StackDestroy(_stack);
			return TRUE;
		}
	}
	return ERR_NOT_INITIALIZED;
}

int PopItemsIntoString(Stack* _stack,char* _postFix,size_t index,char _inFixChar)
{
	int item,dummyItem;
	
	if(_inFixChar==')')
	{
		while(FALSE == StackIsEmpty(_stack))
		{
			StackTop(_stack,&item);
			if(item=='(')
			{
				return index;
			}
			StackPop(_stack,&item);
			_postFix[index++]=item;
		}
	}
	else
	{	
		while(FALSE == StackIsEmpty(_stack))
		{
			StackTop(_stack,&item);
			if(item=='(')
			{
				StackPop(_stack,&dummyItem);
				break;
			}
			if((_inFixChar == '+'||_inFixChar == '-') && item=='(')
			{
				break;
			}
			if((_inFixChar == '*'||_inFixChar == '/') && (item =='-' || item=='+' || item=='('))
			{
				break;
			}
		
			StackPop(_stack,&item);
			_postFix[index++]=item;
		}
		StackPush(_stack,_inFixChar);
		_postFix[index++]=' ';
	}

	return index;
}

int InfixToPostfix(Stack* _stack,char* _inFix, char* _postFix)
{
	int i,j,topItem;
	
	for(i=0,j=0;_inFix[i]!='\0';i++)
	{
		if(TRUE==isNum(_inFix[i]))
		{
			_postFix[j]=_inFix[i];
			j++;	
		}
		else
		{
			if(_inFix[i]== '(')
			{
				StackPush(_stack,_inFix[i]);
			}
			else
			{
				j=PopItemsIntoString(_stack,_postFix,j,_inFix[i]);
			}
		}
	}
	j=PopItemsIntoString(_stack,_postFix,j,')');
	_postFix[j]='\0';
	return TRUE;
}
