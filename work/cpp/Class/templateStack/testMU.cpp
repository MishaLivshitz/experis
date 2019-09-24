//
// Template Stack64 Exercise
//
//

#include "mu_test.h"

#include "templateStack64.h"
#include "rational.h"


UNIT(construct_stack_of_ints)
	Stack64<int> s;

	ASSERT_THAT(s.isEmpty());
	ASSERT_THAT(s.isFull() == false);

	ASSERT_EQUAL(s.size(), 0);

	int r = 99;
	ASSERT_THAT(s.pop(r) == false);
	ASSERT_EQUAL(r, 99);
END_UNIT

UNIT(construct_stack_of_rationals)
	Stack64<Rational> s;

	ASSERT_THAT(s.isEmpty());
	ASSERT_THAT(s.isFull() == false);

	ASSERT_EQUAL(s.size(), 0);

	Rational r(11, 13);
	ASSERT_THAT(s.pop(r) == false);
	ASSERT_EQUAL(r.numerator(), 11);
	ASSERT_EQUAL(r.denomirator(), 13);
END_UNIT

UNIT(stack_of_ints_is_fifo)
	Stack64<int> s;
	const int N = 10;

	for(int i = 0; i < N; ++i)
	{
		s.push(i*i);
	}

	ASSERT_THAT(s.isEmpty() == false);
	ASSERT_THAT(s.isFull() == false);
	ASSERT_EQUAL(s.size(), N);

	for(int i = N-1; i >= 0; --i)
	{
		int r = -1;
		ASSERT_THAT(s.pop(r));
		ASSERT_EQUAL(r, (i*i));
		ASSERT_EQUAL_INT(s.size(), i);
	}

	ASSERT_THAT(s.isEmpty());
	ASSERT_EQUAL(s.size(), 0);
END_UNIT

UNIT(stack_of_Rational_is_fifo)
	Stack64<Rational> s;
	const int N = 10;

	for(int i = 1; i <= N; ++i)
	{
		Rational r(i, i+1);
		s.push(r);
	}

	ASSERT_THAT(s.isEmpty() == false);
	ASSERT_THAT(s.isFull() == false);
	ASSERT_EQUAL(s.size(), N);

	for(int i = N; i > 0; --i)
	{
		Rational r;
		ASSERT_THAT(s.pop(r));
		ASSERT_EQUAL(r.numerator(), i);
		ASSERT_EQUAL(r.denomirator(), i+1);
		ASSERT_EQUAL_INT(s.size(), i-1);
	}

	ASSERT_THAT(s.isEmpty());
	ASSERT_EQUAL(s.size(), 0);

END_UNIT

UNIT(stack_of_ints_print)
	Stack64<int> s;
	s.print();
	s.trace();

	const int N = 10;
	for(int i = 1; i < N; ++i)
	{
		s.push(i);
	}
	s.print();
	s.trace();

END_UNIT

UNIT(stack_of_Rational_print)
	Stack64<Rational> s;
	const int N = 10;

	s.print();
	s.trace();
	for(int i = 1; i <= N; ++i)
	{
		Rational r(i, i+1);
		s.push(r);
	}

	s.print();
	s.trace();

END_UNIT

TEST_SUITE(Stack64 Template <Rational> Test)

	TEST(construct_stack_of_ints)
	TEST(construct_stack_of_rationals)
	TEST(stack_of_ints_is_fifo)
	TEST(stack_of_Rational_is_fifo)
	TEST(stack_of_ints_print)
	TEST(stack_of_Rational_print)

END_SUITE
