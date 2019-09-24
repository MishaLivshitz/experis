#include "mu_test.h"
#include "hash_map.h"
#include <stdio.h>

#ifdef DEBUG
#define PRINT(x,y) printf("{KEY:%d,VAL:%d}\n",x,y)
#else
#define PRINT(x,y)
#endif /*DEBUG*/

size_t XorHash(const int* _key)
{
		return (*_key)^0x0101010101010101;
}

int EqualKey(const int* _firstKey,const int* _secondKey,int* _context)
{
	return *_firstKey == *_secondKey;
}

void KeyDestroy(void* _key)
{
	return;
}

void ValDestroy(void* _val)
{
	return;
}

int PrintInt(const int* _key, int* _val,void* _context)
{
		PRINT(*_key,*_val);
		return 1;
}

UNIT(HashMap_CreateSuccess)

	HashMap* map = HashMap_Create(1,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);
	ASSERT_NOT_EQUAL_PTR(NULL,map);

END_UNIT


UNIT(HashMap_InsertSuccess)

	int key = 5;
	int value = 10;
	int* returnedVal;
	HashMap* map;
	size_t size = 2;

	map=HashMap_Create(size,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);
	HashMap_Insert(map,&key,&value);
	HashMap_Find(map,&key,(void*)&returnedVal);
	ASSERT_EQUAL_INT(value,*returnedVal);
	ASSERT_THAT(HashMap_Insert(map,&key,&value) == MAP_KEY_DUPLICATE_ERROR);
	HashMap_Destroy(map,KeyDestroy,ValDestroy);

END_UNIT

UNIT(HashMap_ForEachTest)

	int keys[] = {7,10,25};
	int values[] = {5,5,8};
	size_t i;
	HashMap* map;
	size_t size;

	size = sizeof(keys)/sizeof(*keys);
	map=HashMap_Create(size,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);

	for(i=0;i<size;i++)
	{
		HashMap_Insert(map,&keys[i],&values[i]);
	}

	ASSERT_THAT(MAP_OVERFLOW_ERROR==HashMap_Insert(map,&keys[i],&values[i]));
	ASSERT_EQUAL_INT(size,HashMap_ForEach(map,(KeyValueActionFunction)PrintInt,NULL));

	HashMap_Destroy(map,KeyDestroy,ValDestroy);

END_UNIT

UNIT(HashMap_RemoveSuccess)

	int keys[] = {80,25};
	int values[] = {1,5};
	size_t i;
	int* returnedKey;
	int* returnedVal;
	HashMap* map;
	size_t size;

	size = sizeof(keys)/sizeof(*keys);
	map = HashMap_Create(size,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);

	for(i=0;i<size;i++)
	{
		HashMap_Insert(map,&keys[i],&values[i]);
	}

	HashMap_Remove(map,&keys[0],(void*)&returnedKey,(void*)&returnedVal);
	HashMap_ForEach(map,(KeyValueActionFunction)PrintInt,NULL);
	ASSERT_THAT(size-1==HashMap_Size(map));
	ASSERT_EQUAL_PTR(&keys[0],returnedKey);
	ASSERT_EQUAL_INT(keys[0],*returnedKey);
	ASSERT_EQUAL_PTR(&values[0],returnedVal);
	ASSERT_EQUAL_INT(values[0],*returnedVal);
	ASSERT_THAT(HashMap_Find(map,&keys[0],(void*)&returnedVal) == MAP_KEY_NOT_FOUND_ERROR);
	HashMap_Destroy(map,KeyDestroy,ValDestroy);

END_UNIT

UNIT(HashMap_RehashSuccess)

	int keys[] = {7,10,25,12};
	int values[] = {5,5,8,40};
	size_t i;
	HashMap* map;
	size_t size;

	size = sizeof(keys)/sizeof(*keys) - 1;
	map = HashMap_Create(size,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);

	for(i=0;i<size;i++)
	{
		HashMap_Insert(map,&keys[i],&values[i]);
	}
	
	ASSERT_THAT(MAP_OVERFLOW_ERROR == HashMap_Insert(map,&keys[i],&values[i]));
	HashMap_Rehash(map,++size);
	ASSERT_EQUAL_INT(HashMap_ForEach(map,(KeyValueActionFunction)PrintInt,NULL),size-1);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(map,&keys[i],&values[i]));
	ASSERT_EQUAL_INT(size,HashMap_ForEach(map,(KeyValueActionFunction)PrintInt,NULL));

	HashMap_Destroy(map,KeyDestroy,ValDestroy);

END_UNIT

UNIT(HashMap_NotInitTest)

	size_t size = 2;

	ASSERT_THAT(HashMap_Create(size,(HashFunction)XorHash,NULL)==NULL);
	ASSERT_THAT(HashMap_Create(size,NULL,(KeyEqualityFunction)EqualKey)==NULL);
	ASSERT_THAT(HashMap_Create(0,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey)==NULL);
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Insert(NULL,NULL,NULL));
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Remove(NULL,NULL,NULL,NULL));
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Find(NULL,NULL,NULL));
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Rehash(NULL,5));
	ASSERT_THAT(0 == HashMap_Capacity(NULL));
	ASSERT_THAT(0 == HashMap_Size(NULL));
	ASSERT_THAT(0 == HashMap_ForEach(NULL,NULL,NULL));

END_UNIT

UNIT(HashMap_KeyNotFoundOrNull)

	int keys[] = {7,10,25,12};
	int values[] = {5,5,8,40};
	size_t i;
	HashMap* map;
	int* returnedVal;
	int* returnedKey;
	size_t size;

	size = sizeof(keys)/sizeof(*keys);
	map = HashMap_Create(size,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);

	for(i=0;i<size;i++)
	{
		HashMap_Insert(map,&keys[i],&values[i]);
	}
	HashMap_ForEach(map,(KeyValueActionFunction)PrintInt,(void*)0);
	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == HashMap_Find(map,(void*)&keys[i],(void*)&returnedVal));
	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == HashMap_Remove(map,(void*)&keys[i],(void*)&returnedKey,(void*)&returnedVal));
	ASSERT_THAT(MAP_KEY_NULL_ERROR == HashMap_Find(map,NULL,(void*)&returnedVal));
	ASSERT_THAT(MAP_KEY_NULL_ERROR == HashMap_Remove(map,NULL,(void*)&returnedKey,(void*)&returnedVal));

	HashMap_Destroy(map,KeyDestroy,ValDestroy);

END_UNIT

UNIT(HashMap_FindSuccess)

	int keys[] = {7,10,25,12};
	int values[] = {5,5,8,40};
	size_t i;
	HashMap* map;
	int* returnedVal;
	size_t size;

	size = sizeof(keys)/sizeof(*keys);
	map = HashMap_Create(size,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);

	for(i=0;i<size;i++)
	{
		HashMap_Insert(map,&keys[i],&values[i]);
	}

	ASSERT_THAT(MAP_SUCCESS == HashMap_Find(map,(void*)&keys[size-1],(void*)&returnedVal));
	ASSERT_EQUAL_INT(*returnedVal,values[size-1]);

	HashMap_Destroy(map,KeyDestroy,ValDestroy);

END_UNIT

UNIT(HashMap_StatisticsTest)

	int keys[] = {7,10,25,12};
	int values[] = {5,5,8,40};
	size_t i;
	HashMap* map;
	size_t maxCollisions;
	float avgCollisions;
	size_t size;

	size = sizeof(keys)/sizeof(*keys);
	map = HashMap_Create(size,(HashFunction)XorHash,(KeyEqualityFunction)EqualKey);

	for(i=0;i<size;i++)
	{
		HashMap_Insert(map,&keys[i],&values[i]);
	}
	HashMap_ForEach(map,(KeyValueActionFunction)PrintInt,NULL);
	HashMap_Statistics(map,&maxCollisions,&avgCollisions);
	ASSERT_EQUAL_INT(1,maxCollisions);
	ASSERT_THAT(avgCollisions == 0.25);
	HashMap_Destroy(map,KeyDestroy,ValDestroy);


END_UNIT

TEST_SUITE(Test generic hash map)

	TEST(HashMap_CreateSuccess)
	TEST(HashMap_InsertSuccess)
	TEST(HashMap_ForEachTest)
	TEST(HashMap_RemoveSuccess)
	TEST(HashMap_RehashSuccess)
	TEST(HashMap_NotInitTest)
	TEST(HashMap_KeyNotFoundOrNull)
	TEST(HashMap_FindSuccess)
	TEST(HashMap_StatisticsTest)

END_SUITE
