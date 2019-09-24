#include "mu_test.h"
#include "queue.h"
#include <string.h>
#include <pthread.h>
#include "sort.h"

#define QUEUE_CAPACITY		1000000

typedef struct Params
{
	WaitableQueue* 	m_queue;
	Vector* 		m_returnedValues;
	int				m_nItems;	
	int				m_status;
} Params;

void* EnqueThread(void* _params)
{
	Params* params = (Params*)_params;
	int* insertItem = NULL;
	int i;
	
	for(i=0; i < params->m_nItems; ++i)
	{
		insertItem = malloc(sizeof(int));		
		*insertItem = i;
		WaitableQueue_Enque(params->m_queue,(void*)insertItem);
	}
	
	return NULL;
}

void* EnqueThreadNegative(void* _params)
{
	Params* params = (Params*)_params;
	int i;
	int* insertItem = NULL;
	
	for(i=1; i <= params->m_nItems; ++i)
	{
		insertItem = malloc(sizeof(int));		
		*insertItem = -i;
		WaitableQueue_Enque(params->m_queue,(void*)insertItem);
	}
	
	return NULL;
}

void* DequeThread(void* _params)
{
	WaitableQueue_Result r;
	Params* params = (Params*)_params;
	int i;
	int* item = NULL;
	
	for(i=0; i < params->m_nItems && params->m_status; ++i)
	{
		r = WaitableQueue_Deque(params->m_queue, (void**)&item);
		if(r != QUEUE_SUCCESS) break;
		if(*item != i)
		{			
			params->m_status = 0;			
		}
		free(item);
	}
	
	return NULL;
}


void* DequeThreadToVec(void* _params)
{
	WaitableQueue_Result r;
	Params* params = (Params*)_params;
	int i;
	int* item = NULL;
	int countPos=0;
	int countNeg=-1;
	
	params->m_status = 1;
	params->m_returnedValues = VectorCreate(params->m_nItems, 0);
	if(!params->m_returnedValues)
	{
		params->m_status = 0;
		goto FAIL;
	}
	
	for(i=0; i < params->m_nItems && params->m_status; ++i)
	{
		r = WaitableQueue_Deque(params->m_queue, (void**)&item);
		if(r != QUEUE_SUCCESS)
		{
			params->m_status = 0;			
			break;
		}
		
		if(*item < 0)
		{
			if(*item > countNeg)
			{
				params->m_status = 0;
			}
		
			countNeg = *item;				
		}
		else 
		{
			if(*item < countPos)
			{
				params->m_status = 0;							
			}
			
			countPos = *item;
		}
		
		VectorAdd(params->m_returnedValues, *item);
		free(item);
	}

FAIL:
	return NULL;
}

void* DequeCountingThread(void* _params)
{
	WaitableQueue_Result r;
	Params* params = (Params*)_params;
	int i;
	int countPos=0;
	int countNeg=-1;
	int* item = NULL;
	
	for(i=0; i < params->m_nItems && params->m_status; ++i)
	{
		r = WaitableQueue_Deque(params->m_queue, (void**)&item);
		if(r != QUEUE_SUCCESS)
		{
			params->m_status = 0;			
			break;
		}
		
		if(*item < 0)
		{
			if(*item > countNeg)
			{
				params->m_status = 0;
			}
		
			countNeg = *item;				
		}
		else 
		{
			if(*item < countPos)
			{
				params->m_status = 0;							
			}
			
			countPos = *item;
		}
		
		free(item);
	}
	
	return params;
}

int IsGreater(int _firstKey, int _secondKey)
{
	return _firstKey > _secondKey;
}

UNIT(WaitableQueue_1_producer)

	WaitableQueue* queue;
	int* insertItem;
	int* currItem;
	int* prevItem;
	int i;
	
	queue = WaitableQueue_Create(QUEUE_CAPACITY);
	
	for(i=0; i<QUEUE_CAPACITY; ++i)
	{
		insertItem = malloc(sizeof(int));
		*insertItem = i;
		WaitableQueue_Enque(queue,(void*)insertItem);
	}

	do
	{
		WaitableQueue_Deque(queue,(void**)&prevItem);
		WaitableQueue_Deque(queue,(void**)&currItem);
		ASSERT_THAT(*currItem>*prevItem);
		free(currItem);
		free(prevItem);
	}
	while(!WaitableQueue_IsEmpty(queue));
	
	WaitableQueue_Destroy(queue);
	
END_UNIT

UNIT(WaitableQueue_1_producer_1_consumer)

	Params tProdParams;
	Params tConsParams;
	
	pthread_t prod;
	pthread_t cons;
	
	tProdParams.m_queue = WaitableQueue_Create(QUEUE_CAPACITY);		
	tProdParams.m_nItems = QUEUE_CAPACITY;
		
	tConsParams = tProdParams;
	tConsParams.m_status = 1;
		
	pthread_create(&prod, NULL, EnqueThread, &tProdParams);
	pthread_create(&cons, NULL, DequeThread, &tConsParams);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	
	ASSERT_EQUAL_INT(WaitableQueue_Size(tProdParams.m_queue), 0);
	ASSERT_THAT(tConsParams.m_status);

	WaitableQueue_Destroy(tProdParams.m_queue);
	
END_UNIT

UNIT(WaitableQueue_2_producer_1_consumer)

	Params tProdParams;
	Params tConsParams;
	
	pthread_t prod[2];
	pthread_t cons;
	
	tProdParams.m_queue = WaitableQueue_Create(QUEUE_CAPACITY);		
	tProdParams.m_nItems = QUEUE_CAPACITY/2;	
		
	tConsParams = tProdParams;
	tConsParams.m_status = 1;
	tConsParams.m_nItems = QUEUE_CAPACITY;
		
	pthread_create(&prod[0], NULL, EnqueThread, &tProdParams);
	pthread_create(&prod[1], NULL, EnqueThreadNegative, &tProdParams);
	pthread_create(&cons, NULL, DequeCountingThread, &tConsParams);

	pthread_join(prod[0], NULL);
	pthread_join(prod[1], NULL);
	pthread_join(cons, NULL);
	
	ASSERT_EQUAL_INT(WaitableQueue_Size(tProdParams.m_queue), 0);
	ASSERT_THAT(tConsParams.m_status);

	WaitableQueue_Destroy(tProdParams.m_queue);
	
END_UNIT

int drain(Vector* to, Vector* from)
{
	size_t i;
	size_t n;
	int item;

	VectorItemsNum(from, &n);
	for(i=1; i <= n; ++i)
	{
		if(VectorGet(from, i, &item) == ERR_OK)
		{
			if(VectorAdd(to, item) != ERR_OK)
			{
			    /* ASSERT_EQUAL_STR("test Fail:", "Vectors are not big enough"); */
				return 0;
			}		
		}
	}

	return 1;
}

int isLinearAscending(Vector* v, size_t total)
{
	int current, previous;
	size_t lastIndex = total;

	VectorGet(v, lastIndex, &current);
	while(--lastIndex)
	{
		VectorGet(v, lastIndex, &previous);
		if( previous != current - 1)
		{
			return 0;
		}		
		current = previous;
	}
	
	VectorDestroy(v);
	return 1;
}

int isMergedVectorsLinearAscending(Vector* v1, Vector* v2)
{
	size_t v1Size, v2Size;
	Vector *v;	
	size_t total;

	VectorItemsNum(v1, &v1Size);
	VectorItemsNum(v2, &v2Size);
	total = v1Size + v2Size;
	v = VectorCreate(v1Size + v2Size, 0);
	
	if(!drain(v, v1) || !drain(v, v2))
	{
		return 0;
	}
	
	MergeSortIterative(v);
	
	return isLinearAscending(v, total);	
}

UNIT(WaitableQueue_1_producer_2_consumer)

	Params tProdParams;
	Params tConsParams[2];
	pthread_t prod;
	pthread_t cons[2];
	
	tProdParams.m_queue = WaitableQueue_Create(QUEUE_CAPACITY);		
	tProdParams.m_nItems = QUEUE_CAPACITY*4;	
		
	tConsParams[0] = tProdParams;
	tConsParams[0].m_status = 1;
	tConsParams[0].m_nItems = QUEUE_CAPACITY*2;
	
	tConsParams[1] = tConsParams[0];
		
	pthread_create(&prod, NULL, EnqueThread, &tProdParams);
	pthread_create(&cons[0], NULL, DequeThreadToVec, &tConsParams[0]);
	pthread_create(&cons[1], NULL, DequeThreadToVec, &tConsParams[1]);

	pthread_join(prod, NULL);
	pthread_join(cons[0], NULL);
	pthread_join(cons[1], NULL);
	
	ASSERT_EQUAL_INT(WaitableQueue_Size(tProdParams.m_queue), 0);
	ASSERT_THAT(tConsParams[0].m_status);
	ASSERT_THAT(tConsParams[1].m_status);
	
	ASSERT_THAT(isMergedVectorsLinearAscending(tConsParams[0].m_returnedValues, tConsParams[1].m_returnedValues));

	VectorDestroy(tConsParams[0].m_returnedValues);
	VectorDestroy(tConsParams[1].m_returnedValues);
	WaitableQueue_Destroy(tProdParams.m_queue);
	
END_UNIT

UNIT(WaitableQueue_2_producer_2_consumer)

	Params tProdParams[2];
	Params tConsParams[2];
	pthread_t prod[2];
	pthread_t cons[2];
	
	tProdParams[0].m_queue = WaitableQueue_Create(QUEUE_CAPACITY);		
	tProdParams[0].m_nItems = QUEUE_CAPACITY*4;	
	tProdParams[1] = tProdParams[0];
	
	tConsParams[0] = tProdParams[0];
	tConsParams[0].m_status = 1;
	tConsParams[1] = tConsParams[0];
		
	pthread_create(&prod[0], NULL, EnqueThread, &tProdParams[0]);
	pthread_create(&prod[1], NULL, EnqueThreadNegative, &tProdParams[1]);
	
	pthread_create(&cons[0], NULL, DequeThreadToVec, &tConsParams[0]);
	pthread_create(&cons[1], NULL, DequeThreadToVec, &tConsParams[1]);

	pthread_join(prod[0], NULL);
	pthread_join(prod[1], NULL);
	
	pthread_join(cons[0], NULL);
	pthread_join(cons[1], NULL);
	
	ASSERT_EQUAL_INT(WaitableQueue_Size(tProdParams[0].m_queue), 0);
	ASSERT_THAT(tConsParams[0].m_status);
	ASSERT_THAT(tConsParams[1].m_status);	
	ASSERT_THAT(isMergedVectorsLinearAscending(tConsParams[0].m_returnedValues, tConsParams[1].m_returnedValues));

	VectorDestroy(tConsParams[0].m_returnedValues);
	VectorDestroy(tConsParams[1].m_returnedValues);
	WaitableQueue_Destroy(tProdParams[0].m_queue);
	
END_UNIT

TEST_SUITE(Generic Queue Module Unit Test)
	
	TEST(WaitableQueue_1_producer)
	TEST(WaitableQueue_1_producer_1_consumer)
	TEST(WaitableQueue_2_producer_1_consumer)
	TEST(WaitableQueue_1_producer_2_consumer)
	TEST(WaitableQueue_2_producer_2_consumer)

END_SUITE
