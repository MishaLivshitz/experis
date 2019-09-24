#include "mu_test.h"
#include "string.h"
#include <iostream>


UNIT(StrTest)

	String s("hello world\n");
	String s1("whatt\n");
	
	TRACER << s1;
	
	ASSERT_THAT(compare(s,s1) < 0);
	ASSERT_THAT(compare(s1,s) > 0);
	
	s1 = s;
	
	TRACER << s1;
	TRACER << s;
	
	String s2(s);
	
	TRACER << s2;
	
	ASSERT_THAT(compare(s,s1) == 0);
	ASSERT_THAT(compare(s,s2) == 0);
	
	ASSERT_EQUAL_INT(String::getObjCount(),3);
	s1.~String();
	s2.~String();
	s.~String();
	ASSERT_EQUAL_INT(String::getObjCount(),0);

END_UNIT

TEST_SUITE(test String class)

	TEST(StrTest)
	
END_SUITE
