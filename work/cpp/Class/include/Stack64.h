#ifndef STACK_64_H
#define STACK_64_H
/**
 *	@file Stack64.h
 *
 *	@brief	Define Stack of int's with pre-defined size
 *
 */

#include <cstddef>		// size_t

#define STACK_CAPACITY	64

class Stack64 {
public:
// CTOR
	Stack64();
// DTOR
//	~Stack64();

// mem-functions
// Operations
	bool push(int _value);
	bool pop(int& _value);
	bool top(int& _vlaue) const;

// State
	bool isFull() const;
	bool isEmpty() const;

	size_t size() const;
	size_t capacity() const;

// Data members
private:
	size_t	m_top;
	const size_t m_capacity;
	int		m_items[STACK_CAPACITY];
};

#endif // STACK_64_H
