
/**
 * 	@file : vTest.cpp
 * 	@brief : demonstarate the standart library of vector
 * 
 * 
 * */

#include "mu_test.h"
#include <vector>
#include <iostream>
#include <map>

template <typename T>
typename std::vector<T>::const_iterator findFirstDuplicate(std::vector<T>const& _v)
{
	typename std::vector<T>::const_iterator itrBegin = _v.begin();
	typename std::vector<T>::const_iterator itrEnd = _v.end();
	std::map<T,T> map;

	for(;itrBegin!=itrEnd;++itrBegin)
	{
		if(map.count(*itrBegin))
		{
			break;
		}
		
		map[*itrBegin] = *itrBegin;
	}
	
	return itrBegin;
}

template <typename T>
void vectorPrint(std::ostream& _os, std::vector<T>const& _v)
{
	typename std::vector<T>::const_iterator itrBegin = _v.begin();
	typename std::vector<T>::const_iterator itrEnd = _v.end();
	
	for(;itrBegin!=itrEnd;++itrBegin)
	{
		_os << *itrBegin << ' ';
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
		_v.push_back(T(std::rand()% (_size/4)));
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


UNIT(findFirstDuplicate_test)

	const int N = 100;
	
	std::vector<int> vI;
	
	fillVector<int>(vI,N);

	ASSERT_EQUAL_INT(vI.size(),N);
	
	std::vector<int>::const_iterator res = findFirstDuplicate(vI);
	
	ASSERT_THAT(res != vI.end());
	
	TRACER << *res;
	
	TRACER << '\n';

	TRACER << vI;

END_UNIT

TEST_SUITE(Standart Vector Test)

	TEST(findFirstDuplicate_test)
	
END_SUITE

