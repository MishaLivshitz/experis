
/**
 * 	@file : vTest.cpp
 * 	@brief : demonstarate the standart library of vector
 * 
 * 
 * */


#include "mu_test.h"
#include <vector>
#include <iostream>


template <typename T>
void vectorPrint(std::ostream& _os, std::vector<T>const& _v)
{
	typename std::vector<T>::const_iterator itrBegin = _v.begin();
	typename std::vector<T>::const_iterator itrEnd = _v.end();
	
	for(;itrBegin!=itrEnd;++itrBegin)
	{
		_os << *itrBegin;
	}
	
	_os << '\n';
}

template <typename T>
std::ostream& operator <<(std::ostream& _os, std::vector<T> _v)
{
	vectorPrint<T>(_os,_v);
	return _os;
}


template <typename T>
void fillVector(std::vector<T>& _v, size_t _size)
{
	_v.reserve(_size);
	
	for(size_t i=0 ; i<_size; ++i)
	{
		_v.push_back(T(i));
	}
	
	TRACER << "vector of "<< typeid(T).name() << " size = " <<_v.size() << "\n";
}

template <typename T>
void fillSquereVector(std::vector<T>& _v, size_t _size)
{
	_v.reserve(_size);
	
	for(size_t i=0 ; i<_size; ++i)
	{
		_v.push_back(T(i*i));
	}
	
	TRACER << "vector of "<< typeid(T).name() << " size = " <<_v.size() << "\n";
}


UNIT(vactor_test_itr)

	const int N = 100;
	
	std::vector<int> vI;
	
	fillVector<int>(vI,N);

	ASSERT_EQUAL_INT(vI.size(),N);
	
	std::vector<int>::iterator itrBegin = vI.begin();
	std::vector<int>::iterator itrEnd = vI.end();
	
	for(int i=0;itrBegin!=itrEnd;++itrBegin,++i)
	{
		TRACER << *itrBegin << ' ';
		ASSERT_EQUAL_INT(*itrBegin, i);
	}
	TRACER << '\n';

	TRACER << vI;

END_UNIT

UNIT(vactor_test_reverse_itr)

	const int N = 100;
	
	std::vector<int> vI;
	
	fillVector<int>(vI,N);

	ASSERT_EQUAL_INT(vI.size(),N);
	
	std::vector<int>::reverse_iterator itrBegin = vI.rbegin();
	std::vector<int>::reverse_iterator itrEnd = vI.rend();
	
	for(int i=N-1;itrBegin!=itrEnd;++itrBegin,--i)
	{
		TRACER << *itrBegin << ' ';
		ASSERT_EQUAL_INT(*itrBegin, i);
	}
	TRACER << '\n';


END_UNIT


TEST_SUITE(Standart Vector Test)

	TEST(vactor_test_itr)
	TEST(vactor_test_reverse_itr)

END_SUITE

