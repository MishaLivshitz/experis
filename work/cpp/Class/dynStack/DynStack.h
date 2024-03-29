#ifndef DYN_STACK_H
#define DYN_STACK_H
/**
 *	@file DynStack.h
 *
 *	@brief	Define Dynamic Stack of int's with specified (at CTOR) size
 *
 */

#include <cstddef>		// size_t
#include <iostream>


class DynStack {
public:
// CTOR
	DynStack(size_t _capacity = s_DEFAULT_STACK_CAPACITY);
	
//CCTOR
	DynStack(DynStack const& _other);
//Opertors
	DynStack& operator = (DynStack const& _rhs);

// DTOR
	~DynStack();

// mem-functions
// Operations
	bool push(int _value);
	bool pop(int& _value);
	bool top(int& _value) const;

// State
	bool isFull() const;
	bool isEmpty() const;

	// automatic inline in-body
	//		size_t size() const { return m_top; }
	size_t size() const;
	size_t capacity() const;

// print the contents of the stack
	void print(std::ostream& _os = std::cout) const;
	void trace(std::ostream& _os = std::cout) const;
// Private mem-functions
private:
	void dump(std::ostream& _os, const char* _header, size_t _n) const;
	

// Data members
private:
const	size_t	m_capacity;
		size_t	m_top;
		int*	m_items;

static const size_t s_DEFAULT_STACK_CAPACITY = 16;

};

// All state and accessors are inline
inline bool DynStack::isFull() const
{
	return (m_top == m_capacity);
}

inline bool DynStack::isEmpty() const
{
	return (m_top == 0);
}

inline size_t DynStack::size() const
{
	return m_top;
}

inline size_t DynStack::capacity() const
{
	return m_capacity;
}

#endif // DYN_STACK_H
