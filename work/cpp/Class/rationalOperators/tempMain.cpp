
#include "mu_test.h"
#include "Rational.h"

#define RANGE	100

UNIT(rational_add)

	Rational a(18,5);
	Rational b(12,23);
	
	/*a+=b;
	ASSERT_EQUAL_INT(a.numerator(), 474);
	ASSERT_EQUAL_INT(a.denominator(), 115);*/
	
	Rational c = a+b;
	ASSERT_EQUAL_INT(c.numerator(), 474);
	ASSERT_EQUAL_INT(c.denominator(), 115);
	
	b.add(5);
	ASSERT_EQUAL_INT(b.numerator(), 127);
	ASSERT_EQUAL_INT(b.denominator(), 23);

END_UNIT

UNIT(rational_mul)

	Rational a(18,5);
	Rational b(12,23);
	
	a*=b;
	ASSERT_EQUAL_INT(a.numerator(), 216);
	ASSERT_EQUAL_INT(a.denominator(), 115);
	
	b.mul(5);
	ASSERT_EQUAL_INT(b.numerator(), 60);
	ASSERT_EQUAL_INT(b.denominator(), 23);

END_UNIT

UNIT(rational_sub)

	Rational a(18,5);
	Rational b(12,23);
	
	a-=b;
	ASSERT_EQUAL_INT(a.numerator() ,354);
	ASSERT_EQUAL_INT(a.denominator() , 115);
	
	b.sub(5);
	ASSERT_EQUAL_INT(b.numerator() , -103);
	ASSERT_EQUAL_INT(b.denominator() , 23);

END_UNIT

UNIT(rational_div)

	Rational a(18,5);
	Rational b(12,23);
	
	a/=b;
	
	ASSERT_EQUAL_INT(a.numerator() , 414);
	ASSERT_EQUAL_INT(a.denominator() , 60);
	
	a.reduce();
	ASSERT_EQUAL_INT(a.numerator() , 69);
	ASSERT_EQUAL_INT(a.denominator() , 10);
	
	b.div(5);
	ASSERT_EQUAL_INT(b.numerator() , 12);
	ASSERT_EQUAL_INT(b.denominator() , 115);

END_UNIT

TEST_SUITE(Rational and RationalStack Test)

	TEST(rational_add)
	TEST(rational_mul)
	TEST(rational_sub)
	TEST(rational_div)


END_SUITE

