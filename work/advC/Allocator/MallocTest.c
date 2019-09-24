#include "mu_test.h"
#include "MyMalloc.h"

typedef struct Pair
{
	int index;
	long value;
	
}Pair;

UNIT(MyMalloc_InitSuccess)

	void* memBuff = malloc(40);	
	memBuff= MyMallocInit(memBuff,40); 
	ASSERT_NOT_EQUAL_PTR(NULL,memBuff);
	free(memBuff);

END_UNIT

UNIT(MyMalloc_Success)

	void* memBuff = malloc(40);	
	Pair *p1,*p2;
	
	memBuff= MyMallocInit(memBuff,40); 
	ASSERT_NOT_EQUAL_PTR(NULL,memBuff);
	p1 = MyMalloc(memBuff,sizeof(Pair));
	p2 = MyMalloc(memBuff,sizeof(Pair));
	ASSERT_THAT(p1);
	ASSERT_THAT(!p2);
	free(memBuff);
	
END_UNIT

UNIT(MyFree_Success)

	void* memBuff = malloc(sizeof(Pair)*5);	
	Pair *p1,*p2, *p3,*p4;
	
	memBuff= MyMallocInit(memBuff,sizeof(Pair)*5); 
	ASSERT_NOT_EQUAL_PTR(NULL,memBuff);
	p1 = MyMalloc(memBuff,sizeof(Pair));
	p2 = MyMalloc(memBuff,sizeof(Pair));
	p3 = MyMalloc(memBuff,sizeof(Pair));
	MyMallocPrint(memBuff);
	p4 = MyMalloc(memBuff,sizeof(Pair));
	
	ASSERT_THAT(p1 && p2 && p3);
	ASSERT_THAT(!p4);
	MyFree(p2);
	p4 = MyMalloc(memBuff,sizeof(Pair));
	ASSERT_THAT(p4);
	MyMallocPrint(memBuff);
	free(memBuff);
	
END_UNIT


TEST_SUITE(MyMalloc Module Unit Test)
	
	TEST(MyMalloc_InitSuccess)
	TEST(MyMalloc_Success)
	TEST(MyFree_Success)
	
END_SUITE
