/**
 *	@file Stack64.cpp
 *
 *	@brief	Const size stack implementation
 *
 */

#include "Stack64.h"
#include <iostream>

using std::cout;

// CTOR
Stack64::Stack64()
: m_top(0)
, m_capacity(STACK_CAPACITY)
{

	for (size_t i=0; i < m_capacity; ++i)
	{
		m_items[i] = 0;
	}
}

// DTOR
/*Stack64::~Stack64()
{
	cout << "Stack64: DTOR called\n";
}
*/
 
// Operations
bool Stack64::push(int _value)
{
	if(isFull())
	{
		return false;
	}
	
	m_items[m_top] = _value;
	++m_top;
	
	return true;
}

bool Stack64::pop(int& _value)
{
	if(isEmpty())
	{
		return false;
	}
	
	_value = m_items[--m_top];
	
	return true;
}

bool Stack64::top(int& _value) const
{
	if(isEmpty())
	{
		return false;
	}
	
	_value = m_items[m_top-1];
	
	return true;
}

// State
bool Stack64::isFull() const
{
	return (m_top == m_capacity);
}

bool Stack64::isEmpty() const
{
	return (m_top == 0);
}

size_t Stack64::size() const
{
	return m_top;
}

size_t Stack64::capacity() const
{
	return m_capacity;
}

