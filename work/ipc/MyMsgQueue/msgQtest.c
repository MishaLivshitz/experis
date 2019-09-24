#include "mu_test.h"
#include "msgQueue.h"
#include <pthread.h>
#include <unistd.h>

#define DEFAULT_MEM_SIZE 	1000000
#define DEFULAT_MSG_NAME 	"msgQueue.c"
#define RECEIVE_MSG_LEN		100
#define NUM_OF_ITERATIONS	1000

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
		printf("producer i = %d\n",i);
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
	int i=0;
	int item;
	size_t buffRead;
	SharedMessageQueueResult err;
	
	params->m_status = 1;
	while(i<params->m_numOfIter)
	{	
		err = SharedMessageQueue_Recv(params->m_msgQ, &item, sizeof(size_t),&buffRead);
		if(err == MSG_QUEUE_SUCCESS)
		{
			if(i != item)
			{
				params->m_status = 0;
				break;
			}
			printf("		consumer i = %d item = %d\n",i,item);
			++i;
		}
	}
	
	return NULL;
}

UNIT(msg_q_create)

	SharedMessageQueue* msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE);
	ASSERT_THAT(msgQ);
	SharedMessageQueue_Destroy(msgQ);

END_UNIT

UNIT(msg_q_send)
	
	SharedMessageQueueResult status;
	char msg[] = "hello World";
	size_t msg_size = sizeof(msg);
	
	SharedMessageQueue* msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE);

	ASSERT_THAT(MSG_QUEUE_SUCCESS==SharedMessageQueue_Send(msgQ,msg,msg_size));
	
	while(MSG_QUEUE_SUCCESS == (status = SharedMessageQueue_Send(msgQ,msg,msg_size)))
	{}
	
	ASSERT_THAT(MSG_QUEUE_OVERFLOW==status);
	SharedMessageQueue_Destroy(msgQ);
	
END_UNIT

UNIT(msg_q_send_rcv)
	
	char msg[] = "hello World";
	char recMsg[RECEIVE_MSG_LEN];
	size_t msg_size = sizeof(msg);
	size_t byteRead;
	
	SharedMessageQueue* msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE);

	ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Send(msgQ, msg, msg_size));
	
	ASSERT_THAT(MSG_QUEUE_BUFFER_TOO_SMALL == SharedMessageQueue_Recv(msgQ, recMsg, msg_size - 1, &byteRead));
	
	ASSERT_EQUAL_INT(msg_size, byteRead);
	
	ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Recv(msgQ, recMsg, msg_size, &byteRead));
	
	ASSERT_THAT(!strcmp(msg,recMsg));
	
	ASSERT_THAT(MSG_QUEUE_UNDERFLOW == SharedMessageQueue_Recv(msgQ, recMsg, msg_size, &byteRead));
	
	ASSERT_THAT(SharedMessageQueue_IsEmpty(msgQ));
	
	SharedMessageQueue_Destroy(msgQ);
	
END_UNIT

UNIT(msg_q_fifo)
	
	int i;
	int prevItem;
	int currItem;
	size_t byteRead;
	SharedMessageQueueResult status;
	SharedMessageQueue* msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE);
	
	for(i=0; MSG_QUEUE_OVERFLOW != SharedMessageQueue_Send(msgQ, &i, sizeof(int)) ;i++)
	{}

	do
	{
		status = SharedMessageQueue_Recv(msgQ, &prevItem, sizeof(int), &byteRead);
		status |= SharedMessageQueue_Recv(msgQ, &currItem, sizeof(int), &byteRead);
		if(MSG_QUEUE_SUCCESS != status)
		{
			ASSERT_EQUAL_INT(prevItem,currItem+1);
			break;
		}
		ASSERT_EQUAL_INT(prevItem+1,currItem);
		
	}while(1);
	
	ASSERT_THAT(SharedMessageQueue_IsEmpty(msgQ));
	SharedMessageQueue_Destroy(msgQ);
END_UNIT

UNIT(msg_q_split_msg)
	
	char msg[] = "hello World";
	char recMsg[RECEIVE_MSG_LEN];
	size_t msg_size = sizeof(msg);
	size_t byteRead;
	
	SharedMessageQueue* msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, 32);

	ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Send(msgQ, msg, msg_size));
	ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Recv(msgQ, recMsg, msg_size, &byteRead));
	ASSERT_THAT(!strcmp(msg,recMsg));
	ASSERT_EQUAL_INT(msg_size, byteRead);
	
	ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Send(msgQ, msg, msg_size));
	ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Recv(msgQ, recMsg, msg_size, &byteRead));
	ASSERT_EQUAL_INT(msg_size, byteRead);
	ASSERT_THAT(!strcmp(msg,recMsg));
	ASSERT_THAT(SharedMessageQueue_IsEmpty(msgQ));
	
	SharedMessageQueue_Destroy(msgQ);
END_UNIT

UNIT(msg_q_1_producer_1_consumer)
	
	Params consumerParams;
	Params producerParams;
	
	producerParams.m_msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE);
	consumerParams.m_msgQ = SharedMessageQueue_Connect(DEFULAT_MSG_NAME);
	
	consumerParams.m_numOfIter = NUM_OF_ITERATIONS;
	producerParams.m_numOfIter = consumerParams.m_numOfIter;
	
	pthread_create(&producerParams.m_thread, NULL, ProducerFunc, &producerParams);
	pthread_create(&consumerParams.m_thread, NULL, ConsumerFunc, &consumerParams);
	
	pthread_join(producerParams.m_thread, NULL);
	pthread_join(consumerParams.m_thread, NULL);
	
	ASSERT_THAT(producerParams.m_status);
	ASSERT_THAT(consumerParams.m_status);
	
	SharedMessageQueue_Destroy(consumerParams.m_msgQ);
	SharedMessageQueue_Destroy(producerParams.m_msgQ);
	
END_UNIT



TEST_SUITE(Generic Queue Module Unit Test)

	/*TEST(msg_q_create)
	TEST(msg_q_send)
	TEST(msg_q_send_rcv)
	TEST(msg_q_fifo)
	TEST(msg_q_split_msg)*/
	TEST(msg_q_1_producer_1_consumer)
	
END_SUITE
