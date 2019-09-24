#include "mu_test.h"
#include "msgQueue.h"

#define DEFAULT_MEM_SIZE 	1000000
#define DEFULAT_MSG_NAME 	"msgQueue.c"
#define RECEIVE_MSG_LEN		100
#define NUM_OF_ITERATIONS	1000
#define DEFAULT_NUM_OF_ITEMS 10000

UNIT(msg_q_1_producer)

	int i;
	SharedMessageQueue* msgQ;
	msgQ = SharedMessageQueue_Create(DEFULAT_MSG_NAME, DEFAULT_MEM_SIZE,DEFAULT_NUM_OF_ITEMS);
	
	
	for(i=0; i<DEFAULT_NUM_OF_ITEMS*2 ;i++)
	{
		ASSERT_THAT(MSG_QUEUE_SUCCESS == SharedMessageQueue_Send(msgQ, &i, sizeof(int)));
		printf("father = %d\n",i);
	}
	
	SharedMessageQueue_Destroy(msgQ);

END_UNIT


TEST_SUITE(Generic SharedQueue Module Unit Test)

	TEST(msg_q_1_producer)
	
END_SUITE
