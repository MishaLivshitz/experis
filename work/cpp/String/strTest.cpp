#include "mu_test.h"
#include "string.h"
#include <iostream>


UNIT(StrTest)

	String s("hello world\n");
	String s1("whatt\n");
	String s3;
	
	TRACER << s1;
	ASSERT_THAT(s!=s1);
	ASSERT_THAT(s<s1);
	ASSERT_THAT(s<=s1);
	
	s1 = s;
																		
	TRACER << s1;
	TRACER << s;
	
	String s2(s);
	
	TRACER << s2;																				
	ASSERT_THAT(s==s2);
	
	String s4("say hello: ");
	s4+=s1;
	TRACER << s4;
	
	ASSERT_EQUAL_INT(String::getObjCount(),5);

END_UNIT

UNIT(comparison_tests)

	String s("hello world\n");
	String s1("whatt\n");
	
	ASSERT_THAT(s!=s1);
	ASSERT_THAT(s<s1);
	ASSERT_THAT(s<=s1);
	
	s1 = s;
	
	ASSERT_THAT(s==s1);
	

END_UNIT

UNIT(concatinate_tests)

	const char* str1 = "hello world";
	const char* str2 = " whatt\n";
	String s(str1);
	String s1(str2);
	String s2;
	String s3;
	String s4;
	
	s2 = s + s1;
	
	TRACER << s2;
	ASSERT_EQUAL_STR(s2.get(),"hello world whatt\n");
	
	s3 = s + " my friend\n";
	
	TRACER << s3;
	ASSERT_EQUAL_STR(s3.get(),"hello world my friend\n");
	
	s4 = str1 + s1;
	
	TRACER << s4;
	ASSERT_EQUAL_INT(String::getObjCount(),5);

END_UNIT

UNIT(substring_test)

	const char* str1 = "hello world";
	const char* str2 = " whatt\n";
	String s(str1);
	String s1(str2);
	String s2;

	s2 = s(2,5);
	
	ASSERT_EQUAL_STR(s2.get(),"llo w");

END_UNIT


UNIT(contains_test)

	const char* str = "hello world";
	const char* str1 = " whatt\n";
	const char* str2 = "hello";
	String s(str);
	String s1(str1);
	String s2(str2);
	
	ASSERT_THAT(!s.contains(s1));
	ASSERT_THAT(s.contains(s2));

END_UNIT

UNIT(findFirst_test)

	const char* str = "hello world";
	String s(str);
	
	ASSERT_EQUAL_INT(2, s.findFirst('l'));
	ASSERT_EQUAL_INT(-1, s.findFirst('k'));

END_UNIT

UNIT(findLast_test)

	const char* str = "hello world";
	String s(str);
	
	ASSERT_EQUAL_INT(9, s.findLast('l'));
	ASSERT_EQUAL_INT(-1, s.findLast('k'));

END_UNIT


UNIT(capacity_test)

	const char* str = "hello world\n";
	String s(str);
	String s1;
	
	s1 = s + s + s;
	
	TRACER << s;
	TRACER  << s1;
	
	
	ASSERT_EQUAL_INT(s.getCapacity(),32);
	ASSERT_EQUAL_INT(s1.getCapacity(),64);

END_UNIT

UNIT(operator_test)

	const char* str = "hello world";
	String s(str);
	String s1;
	char b;
	
	
	TRACER << s << '\n';
	s[0] = 'T'; 
	b = s[1];
	
	
	ASSERT_EQUAL_STR("Tello world",s.get());
	ASSERT_EQUAL(b, 'e');
	
	TRACER << s;
	
END_UNIT

TEST_SUITE(test String class)

	TEST(StrTest)
	TEST(comparison_tests)
	TEST(concatinate_tests)
	TEST(substring_test)
	TEST(contains_test)
	TEST(findFirst_test)
	TEST(findLast_test)
	TEST(capacity_test)
	TEST(operator_test)
	
END_SUITE
