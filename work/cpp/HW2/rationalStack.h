#ifndef RATIONAL_STACK_H
#define RATIONAL_STACK_H
/**
 *	@file RationalStack.h
 *
 *	@brief	Define Stack of int's with pre-defined size
 *
 */

#include <cstddef>		// size_t
#include "rational.h"


class RationalStack {
public:
// CTOR
	RationalStack(size_t _capacity = s_RATIONAL_STACK_CAPACITY, size_t _ext = s_RATIONAL_STACK_EXTENSION);
	
// CCTOR
	RationalStack(RationalStack const& _rhs);
// DTOR
	~RationalStack();

//Operators
	// In case of lack of space the current object is resized
	RationalStack& operator=(RationalStack const& _rhs);
// mem-functions
// Operations
	void push(Rational const& _value) ;
	void push(Rational const _rArr[], size_t _rhsSize);
	
	void pop(Rational& _value);
	void top(Rational& _value) const;
	
	void drain(RationalStack& _other);
	void print() const;
	void trace() const;
	
	
// State
	bool isFull() const;
	bool isEmpty() const;

	size_t size() const;
	size_t capacity() const;
	
private:
	void dump(size_t _nItems) const;
	void Realloc(size_t _newSize);

// Data members
private:
	size_t				m_top;
	size_t 				m_capacity;
	size_t				m_extension;
	Rational			*m_items;
	
static	const  size_t	s_RATIONAL_STACK_CAPACITY = 16;
static	const  size_t	s_RATIONAL_STACK_EXTENSION = 2;

};


inline void RationalStack::pop(Rational& _value)
{
	_value = m_items[--m_top];
}

inline void RationalStack::top(Rational& _value) const
{
	_value = m_items[m_top-1];
}

// State
inline bool RationalStack::isFull() const
{
	return (m_top == m_capacity);
}

inline bool RationalStack::isEmpty() const
{
	return (m_top == 0);
}

inline size_t RationalStack::size() const
{
	return m_top;
}

inline size_t RationalStack::capacity() const
{
	return m_capacity;
}

inline void RationalStack::print() const
{
	dump(m_top);
}
inline void RationalStack::trace() const
{
	dump(m_capacity);
}


#endif // RATIONAL_STACK_H
