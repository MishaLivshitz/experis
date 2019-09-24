#include "mu_test.h"
#include "vector.h"
#include <string.h>
#include "sort.h"
#include <stdio.h>

#define BIG_ALLOCATION_SIZE 100000000000000000
#define TEST_NAME_LEN 100 
#define VEC_SIZE 10
#define RAND_RANGE 100


/* gcc -ansi -pedantic -I ../include/ *.c -g */

void MyDestroyInt(int* item)
{	
	free(item);
}

int PrintInt(int* _item ,int* _context)
{
	printf("%d ",*_item);
	return 0;
}
UNIT(Vector_CreateInitSize)
	
	Vector* vector;
	vector=Vector_Create(0, 10);
	ASSERT_EQUAL_PTR(vector,NULL);
	
END_UNIT

UNIT(Vector_CreateBigMemAllocation)

	Vector* vector;
	vector=Vector_Create(BIG_ALLOCATION_SIZE, 10);
	ASSERT_EQUAL_PTR(vector,NULL);

END_UNIT

UNIT(Vector_AddOverflow)

	Vector* vector;
	int* item = malloc(sizeof(int));
	Vector_Result status;
	*item = 8;

	vector = Vector_Create(1, 0);
	Vector_Add(vector,item);
	status = Vector_Add(vector,item);
	ASSERT_THAT(VECTOR_OVERFLOW == status);
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT


UNIT(Vector_AddReallocFailed)

	Vector* vector;
	Vector_Result status;
	int* item = malloc(sizeof(int));
	*item = 10;

	vector = Vector_Create(1, BIG_ALLOCATION_SIZE);
	Vector_Add(vector,item);
	status = Vector_Add(vector,item);	
	ASSERT_THAT(VECTOR_BAD_ALLOC == status);
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);

END_UNIT

UNIT(Vector_AddSucces)

	Vector* vector;
	int* item = malloc(sizeof(int));
	void* getItem;
	*item = 10;

	vector = Vector_Create(1, 2);
	Vector_Add(vector,item);
	Vector_Get(vector,1,&getItem);
	ASSERT_EQUAL_INT(*item, *(int*)getItem);
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);

END_UNIT

UNIT(Vector_DeletePopItem)

	Vector* vector;
	int* item = malloc(sizeof(int));
	void* getItem;

	*item = 10;

	vector = Vector_Create(1, 2);
	Vector_Add(vector,item);
	Vector_Delete(vector,&getItem);
	ASSERT_EQUAL_INT(*item, *(int*)getItem);
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);

END_UNIT


UNIT(Vector_DeleteResize)

	Vector* vector;
	int* getItem;
	size_t numOfItems;
	int size = 3;
	
	
	vector = Vector_Create(1, 1);
	while(--size>=0)
	{
		int* item =  malloc(sizeof(int));
		*item=size;
		Vector_Add(vector,item);
	}
	
	numOfItems = Vector_Size(vector);
	ASSERT_EQUAL_INT(numOfItems, 3);
	
	Vector_Delete(vector,(void*)&getItem);
	free(getItem);
	
	numOfItems = Vector_Size(vector);
	ASSERT_EQUAL_INT(numOfItems, 2);
	
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT

UNIT(Vector_GetItem)

	Vector* vector;
	int* item = malloc(sizeof(int));
	int* getItem;

	vector = Vector_Create(1, 2);
	Vector_Add(vector,item);
	Vector_Get(vector,1,(void*)&getItem);
	
	ASSERT_EQUAL_INT(*item, *getItem);
	
	free(getItem);
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);

END_UNIT	

UNIT(Vector_GetWrongIndex)

	Vector* vector;
	int* item = malloc(sizeof(int));
	void* getItem;
	
	*item = 8;

	vector = Vector_Create(1, 2);
	Vector_Add(vector,item);
	
	ASSERT_THAT(VECTOR_SUCCESS == Vector_Get(vector,1,(void*)&getItem));
	ASSERT_THAT(VECTOR_WRONG_INDEX == Vector_Get(vector,0,(void*)&getItem));
	ASSERT_THAT(VECTOR_WRONG_INDEX == Vector_Get(vector,2,(void*)&getItem));
	
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);
END_UNIT


UNIT(Vector_SetItem)

	Vector* vector;
	int* item = malloc(sizeof(int));
	int* getItem;

	*item = 8;
	vector = Vector_Create(1, 2);
	Vector_Add(vector,item);
	(*item)++;
	
	Vector_Set(vector,1,item);
	Vector_Get(vector,1,(void*)&getItem);
	
	ASSERT_EQUAL_INT(*item, *getItem);
	
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);

END_UNIT


UNIT(Vector_SetWrongIndex)

	Vector* vector;
	int* item = malloc(sizeof(int));
	
	*item = 8;

	vector = Vector_Create(1, 2);
	Vector_Add(vector,item);
	
	ASSERT_THAT(VECTOR_WRONG_INDEX == Vector_Set(vector,0,item));
	ASSERT_THAT(VECTOR_WRONG_INDEX == Vector_Set(vector,2,item));
	
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT


UNIT(Vector_SizeCheck)

	Vector* vector;
	int* item = malloc(sizeof(int));
	size_t numOfItems;
		
	vector = Vector_Create(1, 2);
	Vector_Add(vector,item);
	
	numOfItems = Vector_Size(vector);
	ASSERT_EQUAL_INT(1, numOfItems);
	
	Vector_Destroy(vector,(AdtItemDestroy)MyDestroyInt);
	
END_UNIT


UNIT(Vector_NullVector)

	Vector* vector;
	int item = 5;
	int* getItem;
	
	vector = NULL;
	
	ASSERT_THAT(VECTOR_NOT_INITIALIZED == Vector_Add(vector,&item));
	ASSERT_THAT(VECTOR_NOT_INITIALIZED == Vector_Delete(vector,(void*)&getItem));
	ASSERT_THAT(VECTOR_NOT_INITIALIZED == Vector_Get(vector,1,(void*)&getItem));
	ASSERT_THAT(VECTOR_NOT_INITIALIZED == Vector_Set(vector,1,&item));
	ASSERT_THAT(0 == Vector_Size(vector));
	
END_UNIT

TEST_SUITE(Dynamic Vector Module Unit Test)
	
	TEST(Vector_CreateInitSize)
	TEST(Vector_CreateBigMemAllocation)
	TEST(Vector_AddOverflow)
	TEST(Vector_AddReallocFailed)
	TEST(Vector_AddSucces)
	TEST(Vector_DeletePopItem)
	TEST(Vector_DeleteResize)
	TEST(Vector_GetItem)
	TEST(Vector_GetWrongIndex)
	TEST(Vector_SetItem)
	TEST(Vector_SetWrongIndex)
	TEST(Vector_SizeCheck)
	TEST(Vector_NullVector)

END_SUITE

