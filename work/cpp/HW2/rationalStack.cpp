/**
 *	@file RationalStack.cpp
 *
 *	@brief	Const size stack implementation
 *
 */

#include "rational.h"
#include "rationalStack.h"
#include <cstring>
#include <iostream>

using std::cout;

// CTOR
RationalStack::RationalStack(size_t _capacity, size_t _ext)
: m_top(0)
, m_capacity(_capacity)
, m_extension(_ext)
, m_items(new Rational[_capacity])
{}

//DTOR
RationalStack::~RationalStack()
{
	delete [] m_items;
}

//CCTOR
RationalStack::RationalStack(RationalStack const& _rhs)
:m_top(_rhs.m_top)
,m_capacity(_rhs.m_capacity)
,m_items(new Rational[m_capacity])
{
	memcpy(m_items, _rhs.m_items,_rhs.size() * sizeof(Rational));
}

//Operators

RationalStack& RationalStack::operator=(RationalStack const& _rhs)
{
	if(m_capacity < _rhs.m_capacity)
	{
		Realloc(_rhs.m_capacity);
	}
	
	m_top = _rhs.m_top;
	m_capacity = _rhs.m_capacity;
	memcpy(m_items, _rhs.m_items,_rhs.size() * sizeof(Rational));
	return *this;
}

// Operations
void RationalStack::push(Rational const& _value)
{
	
	if(isFull())
	{
		Realloc(m_capacity*m_extension);
	}
	
	m_items[m_top] = _value;
	++m_top;
	
}

void RationalStack::push(Rational const _rArr[], size_t _rhsSize)
{
	for(size_t i=0; i<_rhsSize ;++i)
	{
		push(_rArr[i]);
	}
}

void RationalStack::drain(RationalStack& _other)
{
	Rational temp;
	while(!isEmpty())
	{
		pop(temp);
		_other.push(temp);
	}
}

//private

void RationalStack::Realloc(size_t _newSize)
{
	Rational* oldItems = m_items;
	Rational* newItems = new Rational[_newSize]; 
	
	memcpy(newItems,oldItems, size()*sizeof(Rational));
	m_capacity = m_capacity * m_extension;
	m_items = newItems;
	delete [] oldItems;
}

void RationalStack::dump(size_t _nItems) const
{
	for(size_t i=0;i<_nItems; ++i)
	{
		m_items[i].print();
	}
	std::cout << '\n';
}


