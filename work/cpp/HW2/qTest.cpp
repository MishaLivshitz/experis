#include "mu_test.h"
#include "queue.h"

#define BIG_ALLOCATION_SIZE 1000000000000
#define RANGE 100


UNIT(Queue_is_fifo)
	const size_t size = 20;
	const size_t ext = 2;
	Queue queue(size,ext);
	Rational b[size*ext];
	Rational val;

	for(size_t i = 0; i< size*ext; ++i)
	{
		b[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
		queue.enqueue(b[i]);
	}

	for(size_t i = 0; i< size*ext; ++i)
	{
		queue.dequeue(val);
		ASSERT_EQUAL_INT(val.numerator(),b[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(),b[i].denumerator());
	}
	
	ASSERT_THAT(0 == queue.size());
	
END_UNIT


UNIT(Queue_assign)

	const size_t size = 20;
	const size_t ext = 2;
	Queue Aqueue(size,ext);
	Queue Bqueue;
	Rational b[size*ext];
	Rational val;

	for(size_t i = 0; i< size*ext; ++i)
	{
		b[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
		Aqueue.enqueue(b[i]);
	}
	
	Bqueue = Aqueue;
	
	for(size_t i = 0; i< size; ++i)
	{
		Bqueue.dequeue(val);
		ASSERT_EQUAL_INT(val.numerator(),b[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(),b[i].denumerator());
	}
	
	ASSERT_EQUAL_INT(Bqueue.size(),size);
	ASSERT_EQUAL_INT(Aqueue.size(),size*ext);
	
END_UNIT

UNIT(Queue_copy)

	const size_t size = 20;
	const size_t ext = 2;
	Queue Aqueue(size,ext);

	Rational b[size*ext];
	Rational val;

	for(size_t i = 0; i< size*ext; ++i)
	{
		b[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
		Aqueue.enqueue(b[i]);
	}
	
	Queue Bqueue(Aqueue);
	
	for(size_t i = 0; i< size; ++i)
	{
		Bqueue.dequeue(val);
		ASSERT_EQUAL_INT(val.numerator(),b[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(),b[i].denumerator());
	}
	
	ASSERT_EQUAL_INT(Bqueue.size(),size);
	ASSERT_EQUAL_INT(Aqueue.size(),size*ext);
	
END_UNIT


TEST_SUITE(Generic Queue Module Unit Test)
	
	TEST(Queue_is_fifo)
	TEST(Queue_assign)
	TEST(Queue_copy)

END_SUITE
