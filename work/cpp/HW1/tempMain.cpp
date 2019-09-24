
#include "mu_test.h"
#include "rational.h"
#include "rationalStack.h"

#define RANGE	100

UNIT(rational_add)

	Rational a(18,5);
	Rational b(12,23);
	
	a.add(b);
	ASSERT_EQUAL_INT(a.numerator(), 474);
	ASSERT_EQUAL_INT(a.denumerator(), 115);
	
	b.add(5);
	ASSERT_EQUAL_INT(b.numerator(), 127);
	ASSERT_EQUAL_INT(b.denumerator(), 23);

END_UNIT

UNIT(rational_mul)

	Rational a(18,5);
	Rational b(12,23);
	
	a.mul(b);
	ASSERT_EQUAL_INT(a.numerator(), 216);
	ASSERT_EQUAL_INT(a.denumerator(), 115);
	
	b.mul(5);
	ASSERT_EQUAL_INT(b.numerator(), 60);
	ASSERT_EQUAL_INT(b.denumerator(), 23);

END_UNIT

UNIT(rational_sub)

	Rational a(18,5);
	Rational b(12,23);
	
	a.sub(b);
	ASSERT_EQUAL_INT(a.numerator() ,354);
	ASSERT_EQUAL_INT(a.denumerator() , 115);
	
	b.sub(5);
	ASSERT_EQUAL_INT(b.numerator() , -103);
	ASSERT_EQUAL_INT(b.denumerator() , 23);

END_UNIT

UNIT(rational_div)

	Rational a(18,5);
	Rational b(12,23);
	
	a.div(b);
	
	ASSERT_EQUAL_INT(a.numerator() , 414);
	ASSERT_EQUAL_INT(a.denumerator() , 60);
	
	a.reduce();
	ASSERT_EQUAL_INT(a.numerator() , 69);
	ASSERT_EQUAL_INT(a.denumerator() , 10);
	
	b.div(5);
	ASSERT_EQUAL_INT(b.numerator() , 12);
	ASSERT_EQUAL_INT(b.denumerator() , 115);

END_UNIT


UNIT(rational_stack_fifo)

	RationalStack rationalStack;
	Rational b[RATIONAL_STACK_CAPACITY];
	Rational val;
	
	for(int i=0;!rationalStack.isFull();i++)
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

UNIT(rational_stack_drain)

	RationalStack rationalStack;
	RationalStack otherRationalStack;
	Rational b[RATIONAL_STACK_CAPACITY];
	Rational val;
	
	for(int i=0;!rationalStack.isFull();i++)
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

	RationalStack rationalStack;
	Rational b[RATIONAL_STACK_CAPACITY/2];
	Rational c[RATIONAL_STACK_CAPACITY/2];
	int	size = RATIONAL_STACK_CAPACITY/2; 
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


TEST_SUITE(Rational and RationalStack Test)

	TEST(rational_add)
	TEST(rational_mul)
	TEST(rational_sub)
	TEST(rational_div)
	TEST(rational_stack_fifo)
	TEST(rational_stack_drain)
	TEST(rational_stack_push_arr)

END_SUITE

