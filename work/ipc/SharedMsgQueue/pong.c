#include "mu_test.h"
#include "msgQueue.h"

#define DEFAULT_MEM_SIZE 	1000000
#define DEFULAT_MSG_NAME 	"msgQueue.c"
#define RECEIVE_MSG_LEN		100
#define NUM_OF_ITERATIONS	1000
#define DEFAULT_NUM_OF_ITEMS 10000

UNIT(msg_q_1_consumer)
	int prevItem = 0;
	int currItem = 0;
	int i;	
	size_t byteRead;	
	SharedMessageQueue* msgQ = SharedMessageQueue_Connect(DEFULAT_MSG_NAME);
	
	for(i=0; i<DEFAULT_NUM_OF_ITEMS;i++)
	{
		SharedMessageQueue_Recv(msgQ, &prevItem, sizeof(int), &byteRead);
		SharedMessageQueue_Recv(msgQ, &currItem, sizeof(int), &byteRead);
		ASSERT_EQUAL_INT(prevItem+1,currItem);
		printf("		child = %d\n",i);
		printf("		prevItem = %d\n",prevItem);
		printf("		currItem = %d\n",currItem);
	}
	
	SharedMessageQueue_Destroy(msgQ);
	
END_UNIT


TEST_SUITE(Generic SharedQueue Module Unit Test)

TEST(msg_q_1_consumer)
	
END_SUITE
