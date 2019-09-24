/**
 *	@file RationalStack.cpp
 *
 *	@brief	Const size stack implementation
 *
 */

#include "rational.h"
#include "rationalStack.h"
#include <iostream>

using std::cout;

// CTOR
RationalStack::RationalStack()
: m_top(0)
, m_capacity(RATIONAL_STACK_CAPACITY)
{}

// Operations
void RationalStack::push(Rational const& _value)
{
	
	m_items[m_top] = _value;
	++m_top;
	
}

void RationalStack::push(Rational const _rArr[], size_t _rhsSize)
{
	for(size_t i=0; i<_rhsSize ;i++)
	{
		push(_rArr[i]);
	}
}

void RationalStack::pop(Rational& _value)
{
	_value = m_items[--m_top];
}

void RationalStack::top(Rational& _value) const
{
	_value = m_items[m_top-1];
}

// State
bool RationalStack::isFull() const
{
	return (m_top == m_capacity);
}

bool RationalStack::isEmpty() const
{
	return (m_top == 0);
}

size_t RationalStack::size() const
{
	return m_top;
}

size_t RationalStack::capacity() const
{
	return m_capacity;
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
void RationalStack::print() const
{
	dump(m_top);
}
void RationalStack::trace() const
{
	dump(m_capacity);
}

//private

void RationalStack::dump(size_t _nItems) const
{
	
	for(size_t i=0;i<_nItems; ++i)
	{
		m_items[i].print();
	}
	
}

