#include "mu_test.h"
#include "vector.h"
#include "ADTErr.h"
#define BIG_ALLOCATION_SIZE 100000000000000000

UNIT(VectorCreateInitSize)
	
	VectorPtr vector;
	vector=VectorCreate(0, 10);
	ASSERT_EQUAL_PTR(vector,NULL);
	
END_UNIT


UNIT(VectorCreateFromBinaryTest)

	VectorPtr vector;
	size_t size;
	vector = VectorCreateFromBinary("file.bin");
	VectorItemsNum(vector,&size);
	ASSERT_EQUAL_INT(size,10);

END_UNIT


UNIT(VectorCreateBigMemAllocation)

	VectorPtr vector;
	vector=VectorCreate(BIG_ALLOCATION_SIZE, 10);
	ASSERT_EQUAL_PTR(vector,NULL);

END_UNIT


UNIT(VectorAddOverflow)

	VectorPtr vector;
	ADTErr status;

	vector = VectorCreate(1, 0);
	VectorAdd(vector,8);
	status = VectorAdd(vector,5);
	ASSERT_THAT(ERR_OVERFLOW == status);
	VectorDestroy(vector);
	
END_UNIT

UNIT(VectorAddReallocFailed)

	VectorPtr vector;
	ADTErr status;

	vector = VectorCreate(1, BIG_ALLOCATION_SIZE);
	VectorAdd(vector,8);
	status = VectorAdd(vector,8);	
	ASSERT_THAT(ERR_REALLOCATION_FAILED == status);
	VectorDestroy(vector);

END_UNIT


UNIT(VectorAddSucces)

	VectorPtr vector;
	int item = 8;
	int getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,item);
	VectorGet(vector,1,&getItem);
	ASSERT_EQUAL_INT(item, getItem);
	VectorDestroy(vector);

END_UNIT


UNIT(VectorDeletePopItem)

	VectorPtr vector;
	int item = 8;
	int getItem;

	vector = VectorCreate(1, 2);
	VectorAdd(vector,item);
	VectorDelete(vector,&getItem);
	ASSERT_EQUAL_INT(item, getItem);
	VectorDestroy(vector);

END_UNIT


TEST_SUITE(Dynamic Vector Module Unit Test)
	
	TEST(VectorCreateInitSize)
	TEST(VectorCreateFromBinaryTest)
	TEST(VectorCreateBigMemAllocation)
	TEST(VectorAddOverflow)
	TEST(VectorAddReallocFailed)
	TEST(VectorAddSucces)
	TEST(VectorDeletePopItem)

END_SUITE

