
/*#include "mu_test.h"
#include "rational.h"
#include "rationalStack.h"

#define RANGE	100
#define DEFALUT_SIZE 20

UNIT(rational_stack_lifo)

	RationalStack rationalStack;
	Rational b[DEFALUT_SIZE];
	Rational val;
	
	for(int i=0;!rationalStack.isFull();++i)
	{
		b[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
		rationalStack.push(b[i]);
	}
	
	for(int i=rationalStack.size() - 1; !rationalStack.isEmpty() ;--i)
	{
		rationalStack.pop(val);
		ASSERT_EQUAL_INT(val.numerator(), b[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(), b[i].denumerator());
	}
	
END_UNIT

UNIT(assign)
	const int N = 10;
	RationalStack s1(N);
// Fill in first stack
	for(int i = 0; i < N; ++i)
	{
		s1.push(i+1);
	}

// Assign to another stack
	RationalStack s2 = s1;

// Do operations on s1
	
	for (int i=0; i < N-5; ++i)
	{
		Rational r(i*3,25);
		s1.pop(r);
	}
	
	for (int i=0; i < N-5; ++i)
	{
		Rational r(i*17,12);
		s1.push(r);
	}
	
	Rational t2;
	s2.top(t2);
	ASSERT_EQUAL(t2.numerator(), N);

END_UNIT

UNIT(rational_stack_drain)

	RationalStack rationalStack;
	RationalStack otherRationalStack;
	Rational b[DEFALUT_SIZE];
	Rational val;
	
	for(int i=0;!rationalStack.isFull();++i)
	{
		b[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
		rationalStack.push(b[i]);
	}
	
	rationalStack.drain(otherRationalStack);
	ASSERT_THAT(rationalStack.isEmpty());
	
	for(size_t i=0; i < otherRationalStack.size();++i)
	{
		otherRationalStack.pop(val);
		ASSERT_EQUAL_INT(val.numerator(), b[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(), b[i].denumerator());
	}
	
END_UNIT

UNIT(rational_stack_push_arr)

	RationalStack rationalStack(DEFALUT_SIZE);
	Rational b[DEFALUT_SIZE/2];
	Rational c[DEFALUT_SIZE/2];
	int	size = DEFALUT_SIZE/2; 
	Rational val;
	
	for(int i=0;i < size;++i)
	{
		b[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
		rationalStack.push(b[i]);
	}
	
	for(int i=0;i < size;++i)
	{
		c[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
	}
	
	
	rationalStack.push(c, size);
	
	ASSERT_THAT(rationalStack.isFull());
	
	for(int i=size-1; i >= 0; --i)
	{
		rationalStack.pop(val);
		ASSERT_EQUAL_INT(val.numerator(), c[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(), c[i].denumerator());
	}
	
	for(int i=size-1; i >= 0; --i)
	{
		rationalStack.pop(val);
		ASSERT_EQUAL_INT(val.numerator(), b[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(), b[i].denumerator());
	}
	
END_UNIT

UNIT(rational_stack_realloc)
	RationalStack aStack(DEFALUT_SIZE);
	const size_t ext = 3;
	RationalStack bStack(DEFALUT_SIZE, ext);
	Rational arr[DEFALUT_SIZE];
	Rational val;
	
	for(int i=0;i < DEFALUT_SIZE;++i)
	{
		arr[i] = Rational(std::rand() % RANGE, std::rand() % RANGE);
		aStack.push(arr[i]);
	}

	bStack = aStack;
	bStack.push(arr,DEFALUT_SIZE);
	ASSERT_EQUAL_INT(DEFALUT_SIZE*3, bStack.capacity());
	
	for(int i = DEFALUT_SIZE -1; i >=0  ; --i)
	{
		bStack.pop(val);
		ASSERT_EQUAL_INT(val.numerator(), arr[i].numerator());
		ASSERT_EQUAL_INT(val.denumerator(), arr[i].denumerator());
	}
	

END_UNIT


TEST_SUITE(Rational and RationalStack Test)

	TEST(assign)
	TEST(rational_stack_lifo)
	TEST(rational_stack_drain)
	TEST(rational_stack_push_arr)
	TEST(rational_stack_realloc)

END_SUITE
*/
