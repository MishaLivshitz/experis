#ifndef QUEUE_H
#define QUEUE_H
/**
 *	@file RationalStack.h
 *
 *	@brief	Define Queue of rational's with dynamic size
 *
 */

#include <cstddef>		// size_t
#include <iostream>
#include "rationalStack.h"


class Queue {
public:
// CTOR
	Queue(size_t _capacity = s_QUEUE_CAPACITY, size_t _ext = s_QUEUE_EXTENSION);
	
// CCTOR
	Queue(Queue const& _rhs);
// DTOR
	~Queue();

//Operators
	// In case of lack of space the current object is resized according to the rhs size
	Queue& operator=(Queue const& _rhs);
// mem-functions
// Operations
	void enqueue(Rational const& _value);
	void enqueue(Rational const _rArr[], size_t _rhsSize);
	
	void dequeue(Rational& _value);
	void dequeue(Rational _rArr[],size_t _rhsSize);
	
	void print() const;
	void trace() const;
	
	
// State
	bool isFull() const;
	size_t size() const;

	
private:
	void dump(size_t _nItems) const;
	void Realloc(size_t _newSize);

// Data members
private:
	
	RationalStack		m_enqueueStack;
	RationalStack		m_dequeueStack;
	
static	const  size_t	s_QUEUE_CAPACITY = 16;
static	const  size_t	s_QUEUE_EXTENSION = 2;

};

inline void Queue::enqueue(Rational const& _value)
{
	m_enqueueStack.push(_value);
}

inline void Queue::enqueue(Rational const _rArr[], size_t _rhsSize)
{
	m_enqueueStack.push(_rArr, _rhsSize);
}

inline bool Queue::isFull() const
{
	return m_enqueueStack.isFull();
}

inline size_t Queue::size() const
{
	return m_enqueueStack.size() + m_dequeueStack.size();	
}

inline void Queue::dequeue(Rational& _value)
{
	if(m_dequeueStack.isEmpty())
	{
		m_enqueueStack.drain(m_dequeueStack);
	}
	
	m_dequeueStack.pop(_value);
}

inline void Queue::print() const
{
	std::cout << "Dequeue stack:\n";
	m_dequeueStack.print();
	
	std::cout << "Enqueue stack:\n";
	m_enqueueStack.print();
}

inline void Queue::trace() const
{
	std::cout << "Dequeue stack:\n";
	m_dequeueStack.trace();
	
	std::cout << "Enqueue stack:\n";
	m_enqueueStack.trace();
}

#endif // QUEUE_H
