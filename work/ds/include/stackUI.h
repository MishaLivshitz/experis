#ifndef _STACKUI_H_
#define _STACKUI_H_
#include "stack.h"
#define BIG_ALLOCATION_SIZE 1000000000000
#define TEST_NAME_LEN 100 
#define EXPRESSION_LEN 50 
#define FALSE 0
#define TRUE 1

typedef enum
{
	TEST_SUCCES = TRUE,
	TEST_FAILED = FALSE
}UTestERR;

typedef enum
{
	TEST_CREATE=1,
	TEST_PUSH,
	TEST_POP,
	TEST_TOP,
	TEST_NULL,
	CHECK_PARENTHESES,
	INFIX_TO_POSTFIX,
	EXIT = 0
}MenuCase;

typedef int status;

UTestERR TestStackCreateSucces();

UTestERR TestStackCreateInitSize();

UTestERR TestStackCreateBigMemAllocation();

UTestERR TestStackPushOverflow();

UTestERR TestStackPushReallocFailed();

UTestERR TestStackPushSucces();

UTestERR TestStackPopItem();

UTestERR TestPopItem();

UTestERR TestStackTop();

void TestNullStack();

status CheckParentheses(Stack* _stack,char* _expression);

int PopItemsIntoString(Stack* _stack,char* _postFix,size_t index,char _inFixChar);

int InfixToPostfix(Stack* _stack,char* _inFix, char* _postFix);

#endif
