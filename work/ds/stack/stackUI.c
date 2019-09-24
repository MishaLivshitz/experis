#include "stack.h"
#include "stackUI.h"
#include <string.h>


int main()
{
	Stack* stackPtr;
	int option;
	int exitFlag = FALSE;
	size_t size,blockSize;
	char testName[TEST_NAME_LEN];
	char expression[EXPRESSION_LEN],newExpression[EXPRESSION_LEN]={0};
	UTestERR testStatus=TEST_SUCCES;
	while(FALSE==exitFlag)
	{
	
		puts("Test options:\n");
		puts("	1: Test StackCreate");
		puts("	2: Test StackPush");
		puts("	3: Test StackPop");
		puts("	4: Test StackTop");
		puts("	5: Test NullStack");
		puts("	6: Check Parentheses");
		puts("	7: Infix to postfix");
		puts("	0: Quit");

		puts("\nInsert your selection and press Enter:\n");
		scanf("%d",&option);
		switch(option)
		{
			case TEST_CREATE:
				strcpy(testName,"TestStackCreate");
				testStatus &= TestStackCreateSucces();
				testStatus &= TestStackCreateInitSize();
				testStatus &= TestStackCreateBigMemAllocation();
			break;

			case TEST_PUSH:
				strcpy(testName,"TestStackPush");
				testStatus &= TestStackPushOverflow();
				testStatus &= TestStackPushReallocFailed();
				testStatus &= TestStackPushSucces();
			break;

			case TEST_POP:
				strcpy(testName,"TestStackPop");
				testStatus &= TestStackPopItem();
			break;
			
			case TEST_TOP:
				strcpy(testName,"TestStackTop");
				testStatus &= TestStackTop();
			break;

			case TEST_NULL:
				strcpy(testName,"TestNullStack");
				TestNullStack();
				continue;

			case CHECK_PARENTHESES:
				printf("Insert avg. stack size and extension block size:");
				scanf("%lu %lu",&size,&blockSize);
				printf("Insert expression '(,[,{,),],}':\n");
				scanf("%s",expression);
				stackPtr = StackCreate(size,blockSize);
				if(TRUE == CheckParentheses(stackPtr,expression))
				{
					puts("\nLegal parentheses\n");
				}
				else
				{
					puts("\nIllegal parentheses\n");
				}
				StackDestroy(stackPtr);
				stackPtr=NULL;
				continue;

			case INFIX_TO_POSTFIX:
				printf("Insert avg. stack size and extension block size:");
				scanf("%lu %lu",&size,&blockSize);
				printf("Insert mathematical expression:\n");
				scanf("%s",expression);
				stackPtr = StackCreate(size,blockSize);
				InfixToPostfix(stackPtr,expression,newExpression);
				StackDestroy(stackPtr);
				printf("Post fix= %s\n",newExpression);
				continue;

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
		if(TEST_SUCCES == testStatus)
		{
			printf("\n%s test - SUCCES!\n\n",testName);
		}
		else
		{
			printf("\n%s test - FAILED!\n\n",testName);
		}
		testStatus=TEST_SUCCES;
	}
	return 1;
}
