
#include "mu_test.h"
#include "RingBuffer.h"
#include "rational.h"

#define RANGE 100

UNIT(constructor_test)
	RingBuffer<int> qI;
	RingBuffer<float> qF;
	RingBuffer<char> qC;
	RingBuffer<Rational> qR;
	const size_t qSize = 64;
	const char* chars = "abcdefghijklmnopqrstuvwxyz";
	const size_t charsLen = strlen(chars);
	float j=0.5;
	
	for(size_t i = 0 ; i < qSize ; i++, j++)
	{
		qI.enqueue(std::rand() % RANGE);
		qF.enqueue(j);
		qC.enqueue(chars[std::rand() % charsLen]);
		qR.enqueue(Rational(std::rand() % RANGE, std::rand() % RANGE));
	} 
	
	TRACER << qI << '\n';
	TRACER << qF << '\n';
	TRACER << qC << '\n';
	TRACER << qR << '\n';
	
END_UNIT

UNIT(copy_constructor_test)
	RingBuffer<int> qI;
	const size_t qSize = 64;
	int firstQ;
	int secondQ;
	
	for(size_t i = 0 ; i < qSize ; i++)
	{
		qI.enqueue(i);
	}
	 
	TRACER << qI << '\n';

	RingBuffer<int> qI1(qI);
	
	TRACER << qI1 << '\n';
	
	while(!qI.isEmpty())
	{
		qI.dequeue(firstQ);
		qI1.dequeue(secondQ);
		
		ASSERT_EQUAL_INT(firstQ,secondQ);
	}
	

END_UNIT

UNIT(assignment_test)
	RingBuffer<int> qI;
	const size_t qSize = 64;
	int firstQ;
	int secondQ;
	
	for(size_t i = 0 ; i < qSize ; i++)
	{
		qI.enqueue(i);
	}
	 
	TRACER << qI << '\n';

	RingBuffer<int> qI1;
	qI1 = qI;
	
	TRACER << qI1 << '\n';
	
	while(!qI.isEmpty())
	{
		qI.dequeue(firstQ);
		qI1.dequeue(secondQ);
		
		ASSERT_EQUAL_INT(firstQ, secondQ);
	}

END_UNIT

UNIT(fifo_test)
	RingBuffer<int> qI;
	const size_t qSize = 64;
	int* arr = new int[qSize];
	
	for(size_t i = 0 ; i < qSize ; i++)
	{	
		arr[i] = std::rand() % RANGE;
		qI.enqueue(arr[i]);
	}
	 
	TRACER << qI << '\n';

	RingBuffer<int> qI1;
	qI1 = qI;
	
	TRACER << qI1 << '\n';
	
	for(size_t i=0;!qI.isEmpty();i++)
	{
		int val;
		qI.dequeue(val);
		ASSERT_EQUAL_INT(arr[i], val);
	}

END_UNIT


TEST_SUITE(Templated Queue Module Unit Test)

	TEST(constructor_test)
	TEST(copy_constructor_test)
	TEST(assignment_test)
	TEST(fifo_test)

END_SUITE
