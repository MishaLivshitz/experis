

#include "queue.h"

//CTOR
Queue::Queue(size_t _capacity, size_t _ext)
:m_enqueueStack(_capacity,_ext)
,m_dequeueStack(_capacity,_ext)
{}

//CCTOR
Queue::Queue(Queue const& _rhs)
:m_enqueueStack(_rhs.m_enqueueStack)
,m_dequeueStack(_rhs.m_dequeueStack)
{}

//DTOR
Queue::~Queue(){}

Queue&::Queue::operator=(Queue const& _rhs)
{
	m_enqueueStack = _rhs.m_enqueueStack;
	m_dequeueStack = m_dequeueStack;
	return *this;
}

void Queue::dequeue(Rational _rArr[],size_t _rhsSize)
{
	for(size_t i=0;i < _rhsSize; ++i)
	{
		dequeue(_rArr[i]);
	}
}
