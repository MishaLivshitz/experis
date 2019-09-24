
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

UNIT(overflow_test)

	RingBuffer<int> qI;
	const size_t qSize = 64;
	int* arr = new int[qSize];
	
	try
	{
		int i=0;
		while(true)
		{	
			arr[i] = std::rand() % RANGE;
			qI.enqueue(arr[i++]);
		}
			ASSERT_THAT(false);
	}
	catch(MyOverFlowException e)
	{
		TRACER << e.what() << std::endl;
		ASSERT_THAT(true);
	}


END_UNIT

/* UNIT(underflow_test)

	RingBuffer<int> qI;
	int val;
	
	try
	{
		qI.dequeue(val);
		ASSERT_THAT(false);
	}
	catch(MyUnderFlowException const& e)
	{
		TRACER << e.what() << std::endl;
		ASSERT_THAT(true);
	}


END_UNIT

UNIT(assign_test)

	RingBuffer<int> qI;
	RingBuffer<int> qI2(20);
	const size_t qSize = 64;
	int* arr = new int[qSize];
	
	for(size_t i = 0 ; i < qSize ; i++)
	{	
		arr[i] = std::rand() % RANGE;
		qI.enqueue(arr[i]);
	}
	
	try
	{
		qI2 = qI;
		ASSERT_THAT(false);
	}
	catch(MyOverFlowException const& e)
	{
		TRACER << e.what() << std::endl;
		ASSERT_THAT(true);
	}


END_UNIT

UNIT(zero_capacity)

	try{
		RingBuffer<int> qI(0);
		ASSERT_THAT(false);
	}
	catch(MyBadArgumentException const& e)
	{
		ASSERT_THAT(true);
		TRACER << e.what() << std::endl;
	}

	


END_UNIT */


TEST_SUITE(Templated Queue Module Unit Test)

	IGNORE_TEST(constructor_test)
	IGNORE_TEST(copy_constructor_test)
	IGNORE_TEST(assignment_test)
	IGNORE_TEST(fifo_test)
	TEST(overflow_test)
/* 	TEST(underflow_test)
	TEST(assign_test)
	TEST(zero_capacity) */

END_SUITE
