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

#define RATIONAL_STACK_CAPACITY	16

class RationalStack {
public:
// CTOR
	RationalStack();
// DTOR
//	~RationalStack();

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

// Data members
private:
	size_t			m_top;
	const size_t 	m_capacity;
	Rational		m_items[RATIONAL_STACK_CAPACITY];
};

#endif // RATIONAL_STACK_H
