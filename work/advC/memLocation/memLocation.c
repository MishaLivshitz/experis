#include <stdio.h>
#include <stdlib.h>

#define PRINT_ADDRESS(T,P) 	printf(#T ":\t%p\n",(void*)P)
#define PRINT_SIZEOF(T)		printf(#T ":\t%lu\n",sizeof(T))

typedef void (*fPtr)(int _a,int _b,int _c,int _d,int _e,int _f,int _g,int _h,int _i,int _j);

const int x;
const int x1=0;

short x2;
float x3 = 5; 

#pragma pack(push,2)
typedef struct 
{
	char ch;
	long l1;
	char ch2;
	
}s1;
#pragma pack(pop)


#pragma pack(push,4)
typedef struct 
{
	char ch;
	long l1;
	int ch2;
	
}s2;
#pragma pack(pop)


typedef struct 
{
	char ch;
	long l1;
	int ch2;
	
}s3;


void foo(int _a,int _b,int _c,int _d,int _e,int _f,int _g,int _h,int _i,int _j)
{
	int b=5;
	
	puts("STACK:");
	PRINT_SIZEOF(int);
	PRINT_ADDRESS(int,&_a);
	PRINT_ADDRESS(int,&_b);
	PRINT_ADDRESS(int,&_c);
	PRINT_ADDRESS(int,&_d);
	PRINT_ADDRESS(int,&_e);
	PRINT_ADDRESS(int,&_f);
	PRINT_ADDRESS(int,&_g);
	PRINT_ADDRESS(int,&_h);
	PRINT_ADDRESS(int,&_i);
	PRINT_ADDRESS(int,&_j);
	PRINT_ADDRESS(int,&b);
	
}


int main()
{
	void *arr = malloc(sizeof(int)*16);
	void *arr2 = malloc(sizeof(int)*10);
	s1 S1[2];
	s2 S2[2];
	s3 S3[2];
	foo(5,3,4,5,6,7,8,9,0,4);
	
	
	puts("\nHEAP:");
	PRINT_ADDRESS(int*,arr);
	PRINT_ADDRESS(int*,arr2);
	
	puts("\nDATA:");
	PRINT_ADDRESS(int,&x);
	PRINT_ADDRESS(int,&x1);
	PRINT_ADDRESS(short,&x2);
	PRINT_ADDRESS(float,&x3);
	
	puts("\nCODE:");
	PRINT_ADDRESS(fPtr,foo);
	PRINT_ADDRESS(fPtr,main);
	
	puts("\nSIZE:");
	PRINT_SIZEOF(s1);
	PRINT_SIZEOF(s2);
	PRINT_SIZEOF(s3);
	
	puts("S1:");
	PRINT_ADDRESS(char,&S1[0].ch);
	PRINT_ADDRESS(long,&S1[0].l1);
	PRINT_ADDRESS(char,&S1[0].ch2);
	
	PRINT_ADDRESS(char,&S1[1].ch);
	PRINT_ADDRESS(long,&S1[1].l1);
	PRINT_ADDRESS(char,&S1[1].ch2);
	
	puts("S2:");
	PRINT_ADDRESS(char,&S2[0].ch);
	PRINT_ADDRESS(long,&S2[0].l1);
	PRINT_ADDRESS(int,&S2[0].ch2);
	
	PRINT_ADDRESS(char,&S2[1].ch);
	PRINT_ADDRESS(long,&S2[1].l1);
	PRINT_ADDRESS(int,&S2[1].ch2);
	
	puts("S3:");
	PRINT_ADDRESS(char,&S3[0].ch);
	PRINT_ADDRESS(long,&S3[0].l1);
	PRINT_ADDRESS(int,&S3[0].ch2);
	
	PRINT_ADDRESS(char,&S3[1].ch);
	PRINT_ADDRESS(long,&S3[1].l1);
	PRINT_ADDRESS(int,&S3[1].ch2);
	return 1;
}
