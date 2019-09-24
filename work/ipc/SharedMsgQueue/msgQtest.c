#include "mu_test.h"
#include "msgQueue.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define DEFAULT_MEM_SIZE 	1000000
#define DEFULAT_MSG_NAME 	"msgQueue.c"
#define RECEIVE_MSG_LEN		100
#define NUM_OF_ITERATIONS	1000
#define DEFAULT_NUM_OF_ITEMS 10000
typedef struct Params
{
	SharedMessageQueue*		m_msgQ;
	pthread_t 				m_thread;
	int 					m_numOfIter;
	int 					m_status;
	
}Params;

void* ProducerFunc(void* _params)
{
	Params* params = (Params*)_params;
	int i;
	SharedMessageQueueResult err;
	
	params->m_status = 1;
	for(i=0; i<params->m_numOfIter && params->m_status ;i++)
	{
		
		err = SharedMessageQueue_Send(params->m_msgQ, &i, sizeof(int));
		if(MSG_QUEUE_SUCCESS != err)
		{
			params->m_status = 0;
		}
	}
	
	return NULL;
}

void* ConsumerFunc(void* _params)
{
	
	Params* params = (Params*)_params;
	int i;
	int currItem = 0;
	size_t byteRead;
	
	params->m_status = 1;
	for(i=0; i<params->m_numOfIter;i++)
	{
		SharedMessageQueue_Recv(params->m_msgQ, &currItem, sizeof(int), &byteRead);
		if(i!=currItem)
		{
			params->m_status = 0;
			break;
		}
	}
	
	return NULL;
}

UNIT(msg_q_fifo)
	
	int i;
	int prevItem = 0;
	int currItem = 0;
	size_t byteRead;
	SharedMessageQueue* msgQ = NULL;
	
	msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE, DEFAULT_NUM_OF_ITEMS);

	for(i=0; i<DEFAULT_NUM_OF_ITEMS ;i++)
	{
		SharedMessageQueue_Send(msgQ, &i, sizeof(int));
	}

	for(i=0; i<DEFAULT_NUM_OF_ITEMS/2;i++)
	{
		SharedMessageQueue_Recv(msgQ, &prevItem, sizeof(int), &byteRead);
		SharedMessageQueue_Recv(msgQ, &currItem, sizeof(int), &byteRead);
		ASSERT_EQUAL_INT(prevItem+1,currItem);
	}
	
	ASSERT_THAT(SharedMessageQueue_IsEmpty(msgQ));
	SharedMessageQueue_Destroy(msgQ);
	
END_UNIT


UNIT(msg_q_1_producer_1_consumer)
	
	Params consumerParams;
	Params producerParams;
	
	producerParams.m_msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE,DEFAULT_NUM_OF_ITEMS);
	consumerParams.m_msgQ = SharedMessageQueue_Connect(DEFULAT_MSG_NAME);
	
	producerParams.m_numOfIter = DEFAULT_NUM_OF_ITEMS*2;
	consumerParams.m_numOfIter = producerParams.m_numOfIter;
	
	pthread_create(&producerParams.m_thread, NULL, ProducerFunc, &producerParams);
	pthread_create(&consumerParams.m_thread, NULL, ConsumerFunc, &consumerParams);
	
	pthread_join(producerParams.m_thread, NULL);
	pthread_join(consumerParams.m_thread, NULL);
	
	ASSERT_THAT(producerParams.m_status);
	ASSERT_THAT(consumerParams.m_status);
	
	SharedMessageQueue_Destroy(consumerParams.m_msgQ);
	SharedMessageQueue_Destroy(producerParams.m_msgQ);
	
END_UNIT

UNIT(mallocTest)

	size_t byteRead;
	char msg[] = "hello World";
	char recMsg[RECEIVE_MSG_LEN];
	size_t msg_size = sizeof(msg);
	SharedMessageQueue* sharedQueue;
	
	
	sharedQueue = SharedMessageQueue_Create(DEFULAT_MSG_NAME,DEFAULT_MEM_SIZE,DEFAULT_NUM_OF_ITEMS);
	ASSERT_THAT(sharedQueue);
	SharedMessageQueue_Send(sharedQueue,msg,msg_size);

	ASSERT_THAT(MSG_QUEUE_BUFFER_TOO_SMALL == SharedMessageQueue_Recv(sharedQueue, recMsg, msg_size - 1, &byteRead));
	ASSERT_EQUAL_INT(msg_size, byteRead);
	ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Recv(sharedQueue, recMsg, msg_size, &byteRead));
	ASSERT_THAT(!strcmp(msg,recMsg));
	
	SharedMessageQueue_Destroy(sharedQueue);
END_UNIT


UNIT(msg_q_1_producer_1_consumer_proccess)
	
	int pid;
	SharedMessageQueue* msgQ;
	msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE,DEFAULT_NUM_OF_ITEMS);
	
	pid=fork();
	
	if(pid==0)	
	{
		int prevItem = 0;
		int currItem = 0;
		int i;	
		size_t byteRead;	
		SharedMessageQueue* msgQchild = SharedMessageQueue_Connect(DEFULAT_MSG_NAME);
		
		for(i=0; i<DEFAULT_NUM_OF_ITEMS;i++)
		{
			SharedMessageQueue_Recv(msgQ, &prevItem, sizeof(int), &byteRead);
			SharedMessageQueue_Recv(msgQ, &currItem, sizeof(int), &byteRead);
			ASSERT_EQUAL_INT(prevItem+1,currItem);
			printf("		child = %d\n",i);
			printf("		prevItem = %d\n",prevItem);
			printf("		currItem = %d\n",currItem);
		}
		
		SharedMessageQueue_Destroy(msgQchild);
	}
	else    	
	{		
		int j;
		for(j=0; j<DEFAULT_NUM_OF_ITEMS*2 ;j++)
		{
			SharedMessageQueue_Send(msgQ, &j, sizeof(int));
			/*printf("father = %d\n",j);*/
		}
		wait(NULL);
		SharedMessageQueue_Destroy(msgQ);
	}
	
	
	
END_UNIT



TEST_SUITE(Generic SharedQueue Module Unit Test)

	TEST(mallocTest)
	TEST(msg_q_fifo)
	TEST(msg_q_1_producer_1_consumer)
	TEST(msg_q_1_producer_1_consumer_proccess)
	
END_SUITE
