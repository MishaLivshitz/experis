#include "mu_test.h"
#include "TwoWayMap.h"
#include <iostream>
#include <map>

UNIT(insert_test)

	TwoWayMap<std::string,int> tMap;

	ASSERT_EQUAL(true, tMap.insert("Misha", 10));
	ASSERT_EQUAL(true, tMap.insert("Daniel", 11));
	ASSERT_EQUAL(true, tMap.insert("Yossi", 12));
	
	ASSERT_EQUAL(false,tMap.insert("Yossi", 13));
	ASSERT_EQUAL(false,tMap.insert("Avi", 10));
	
	ASSERT_EQUAL_INT(3,tMap.size());

	TRACER << tMap;
	

END_UNIT

UNIT(remove_test)
	
	TwoWayMap<std::string,int> tMap;
	
	ASSERT_EQUAL(true, tMap.insert("Misha", 10));
	ASSERT_EQUAL(true, tMap.insert("Daniel", 11));
	ASSERT_EQUAL(true, tMap.insert("Yossi", 12));
	
	ASSERT_EQUAL(true, tMap.removeByKey("Yossi"));
	ASSERT_EQUAL(true, tMap.removeByValue(11));
	
	ASSERT_EQUAL_INT(1,tMap.size());

	TRACER << tMap;
	
END_UNIT


UNIT(getKeyByValue_test)

	TwoWayMap<std::string,int> tMap;
	
	tMap.insert("Misha", 10);
	tMap.insert("Daniel", 11);
	tMap.insert("Yossi", 12);
	ASSERT_EQUAL_INT(3,tMap.size());
	
	std::string name = tMap(10);

	ASSERT_EQUAL("Misha", name);
	
	TRACER << tMap;
	

END_UNIT


UNIT(getValueByKey_test)

	TwoWayMap<std::string,int> tMap;
	
	tMap.insert("Misha", 10);
	tMap.insert("Daniel", 11);
	tMap.insert("Yossi", 12);
	ASSERT_EQUAL_INT(3,tMap.size());
	
	int val = tMap["Misha"];
	int r = tMap["alex"];
	
	ASSERT_EQUAL(10, val);
	ASSERT_EQUAL(0, r);

	TRACER << tMap;
	

END_UNIT






TEST_SUITE(Bidirectional map test)

	TEST(insert_test)
	TEST(remove_test)

	TEST(getKeyByValue_test)
	TEST(getValueByKey_test)

END_SUITE
