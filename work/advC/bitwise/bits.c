#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define HEX_BASE 16
#define INT_BITS 	sizeof(int) * 8
#define MAX_INT (1 << (INT_BITS)) -1

typedef unsigned long int ULint;
typedef unsigned char Uchar;

const char* hexChar= "0123456789ABCDEF";
 
void SwapVer1(ULint* _a, ULint* _b)
{
	*_a = *_a + *_b;
	*_b = *_a - *_b;
	*_a = *_a - *_b;	
}

void SwapVer2(ULint* _a, ULint* _b)
{
	*_a = *_a * *_b;
	*_b = *_a / *_b;
	*_a = *_a / *_b;	
}

void SwapVer3(ULint* _a, ULint* _b)
{
	*_a = *_a ^ *_b;
	*_b = *_a ^ *_b;
	*_a = *_a ^ *_b;	
}

void SwapCharVer1(Uchar* _a, Uchar* _b)
{
	*_a = *_a + *_b;
	*_b = *_a - *_b;
	*_a = *_a - *_b;
}

void integerToHex(ULint _num, Uchar* _str)
{
	size_t index;
	size_t end_str;
	
	for(index=0;_num>0;index++,_num>>=4)
	{
		_str[index] = hexChar[_num & (HEX_BASE-1)];
	}
	
	for(index = 0,end_str = strlen((char*)_str)-1; index<end_str; index++,end_str--)
	{
		SwapCharVer1(&_str[index],&_str[end_str]);
	}
	
}

int isNegative(int _num)
{
	return (_num >> (INT_BITS-1)) & 1;
}

int absNumVer1(int _num)
{
	return (int)sqrt(_num*_num);
}

int absNumVer2(int _num)
{
	int mask = (_num >> (INT_BITS-1));
	
	return (mask ^ (_num + mask));
}

int isPowOf2(int _num)
{
	
	return (_num & (_num-1)) == 0;
}

int SwapBits(int _num, size_t _first, size_t _second)
{
	int bitFirst = (_num >> _first) & 1;
	int bitSecond = (_num >> _second) & 1;
	unsigned int reminder;
	
	reminder = _num << (INT_BITS - _first);
	_num = bitSecond == 1 ? (_num >> _first) | 1: (_num >> _first) ^ 1;
	_num = _num << _first | reminder >> (INT_BITS - _first);
	
	reminder = _num << (INT_BITS - _second);
	_num = bitFirst == 1 ? (_num >> _second) | 1: (_num >> _second) ^ 1;
	_num = _num << _second | reminder >> (INT_BITS - _second);

	return _num;
	
}

int main()
{
	ULint x=10,y=20;
	
	Uchar hexStr[sizeof(ULint)*2+1]={0};
	printf("Before:X=%ld, Y=%ld\n",x,y);
	SwapVer3(&x,&y);
	printf("After:X=%ld, Y=%ld\n",x,y);
	integerToHex(42949672940,hexStr);
	printf("Hex:%s\n",hexStr);
	
	printf("is neg: %d\n", isNegative(-2));
	printf("abs: %d\n", absNumVer1(-5));
	printf("abs2: %d\n", absNumVer2(5));
	printf("isPowOf2: %d\n", isPowOf2(8));
	printf("swap %d\n",SwapBits(45,4,2));
	return 0;
}
