#include <stdio.h>
#include <string.h>
#include "strings.h"



int swapChar(char *a ,char *b)
{
	char temp = *a;
	*a=*b;
	*b=temp;
}

void FixSpaces(char *_str)
{
	char *tempStr = _str;

	while(*tempStr!='\0')
	{
		while(*tempStr==' ' && *(tempStr+1)==' ')
		{
			*tempStr = *(tempStr+1);
			tempStr++;
		}
		tempStr++;
	}

}

int ReverseStr(char *str)
{
	char *firstChar = str;
	char *lastChar = firstChar + strlen(firstChar)-1;

	while(firstChar<=lastChar)
	{
		swapChar(firstChar++,lastChar--);
	}

}

void ShiftStr(char *shiftStr,int shiftCount)
{
	int i;
	printf("%s\n",shiftStr);

	if(shiftStr[i+shiftCount]!=' '){
		for(i=0;i<=shiftCount;i++)
		{	
			shiftStr[i]=shiftStr[i+shiftCount];
			shiftStr[i+shiftCount]=' ';
		}
	}
	else
	{
		for(i=0;shiftStr[i+shiftCount+1]!='\0';i++)
		{	
			shiftStr[i]=shiftStr[i+shiftCount+1];
		}
		shiftStr[i]='\0';
	}
}

int SquezeStr(char *_str, char *_subStrToIgnore)
{

	int sizeOfSubStr = strlen(_subStrToIgnore);
	char *tempStr = _str;
	char *pSubStr=NULL;

	while(*tempStr!='\0')
	{	
		if(pSubStr=strstr(tempStr,_subStrToIgnore))
			{
				ShiftStr(pSubStr,sizeOfSubStr);
				tempStr=pSubStr;
			}
		else 
		{
			break;
		}
		tempStr++;
	}
}
char* Dec2Bin()
{
	int num,i=0,j;
	char arr[SIZE];
	char binArr[SIZE];
	printf("Please insert a number:");
	scanf("%d",&num);
	printf("\n%d",num);
	while(num>0)
	{
		if(num&1==1)
		{
			arr[i++]='1';
		}
		else
		{
			arr[i++]='0';
		}
		num/=2;
	}
	arr[i]='\0';
	for(j=0;i>=0;j++,i--)
	{
		binArr[j]=arr[i-1];
		printf("%c",binArr[j]);
	}
	binArr[j]='\0';
	return binArr;

}
