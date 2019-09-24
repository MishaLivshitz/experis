/**
 *	@file DynStack.cpp
 *
 *	@brief	Const size stack implementation
 *
 */

#include "DynStack.h"
#include <cstring>
#include <iostream>

using std::cout;

// CTOR
DynStack::DynStack(size_t _capacity)
: m_capacity(_capacity)
, m_top(0)
{
	m_items = new int[m_capacity];
}

//CCTOR
DynStack::DynStack(DynStack const& _other)
: m_capacity(_other.m_capacity)
, m_top(_other.size())
, m_items(new int[m_capacity])
{
	std::memcpy(m_items,_other.m_items,m_top * sizeof(int));
}

//operators
DynStack& DynStack::operator=(DynStack const& _rhs)
{
	m_top = _rhs.m_top;
	std::memcpy(m_items,_rhs.m_items,m_top * sizeof(int));
	return *this;
}


// DTOR
DynStack::~DynStack()
{
	delete [] m_items;
}
 
// Operations
bool DynStack::push(int _value)
{
	if (isFull()) {
		return false;
	}

	m_items[m_top++] = _value;
	return true;
}

bool DynStack::pop(int& _value)
{
	if (isEmpty()) {
		return false;
	}

	_value = m_items[--m_top];
	return true;
}

bool DynStack::top(int& _value) const
{
	if (isEmpty()) {
		return false;
	}

	_value = m_items[m_top - 1];
	return true;
}

// print the contents of the stack
void DynStack::print(std::ostream& _os) const
{
	dump(_os, "stack", size());
}

void DynStack::trace(std::ostream& _os) const
{
	dump(_os, "trace", m_capacity);
}

void DynStack::dump(std::ostream& _os, const char* _header, size_t _n) const
{
	_os << _header << '[' << m_top << "/" << m_capacity << "]={ ";

	for (size_t i = 0; i < _n; ++i)
	{
		_os << m_items[i] << ' ';
	}
	_os << "}\n";
}
