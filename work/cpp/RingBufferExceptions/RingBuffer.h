#ifndef RINGBUFFER_H
#define RINGBUFFER_H
//
// 	Create a RingBuffer<T> container
//	*	default CTOR
//	*	mem-function:	enqueue		insert to ringbuffer
//	*	mem-function:	dequeue		extract from ringbuffer
//	*	mem-function:	front		return front of the queue without extracting
//	*	mem-function:	isFull()
//	*	mem-function:	isEmpty()
//	*	mem-function:	size()		returns current number of elements
//	*	support ostream << ringbuffer for printing
//

#include <cstddef>
#include <cstring>
#include <iostream>
#include "MyOverFlowException.h"
#include "MyUnderFlowException.h"
#include "MyBadArgumentException.h"

template<typename T>
class RingBuffer
{
public:
	//CTOR
	RingBuffer(size_t _capacity = 64) throw(MyBadArgumentException);
	//CCTOR
	RingBuffer(RingBuffer<T> const& _source);
	//DTOR
	~RingBuffer();
	//Assignment operator
	RingBuffer& operator= (RingBuffer<T> const& _source) throw (MyOverFlowException);
	
	void enqueue(const T& _value) throw(MyOverFlowException);
	void dequeue(T& _value) throw (MyUnderFlowException);

	const T& front() const;

	bool isFull() const;
	bool isEmpty() const;

	size_t size() const;

	void print(std::ostream& _os = std::cout) const;
	void trace(std::ostream& _os = std::cout) const;

private:
	void init(RingBuffer<T> const& _source);
	void dump(std::ostream& _os, const char* _header, size_t _n) const;

private:
	size_t	 m_capacity;
	size_t	 m_head;
	size_t	 m_tail;
	size_t	 m_size;
	T		*m_items;
};

//CTOR
template <typename T>
RingBuffer<T>::RingBuffer(size_t _capacity) throw(MyBadArgumentException)
:m_capacity(_capacity)
,m_head(0)
,m_tail(0)
,m_size(0)
,m_items(new T[_capacity])
{
	if (_capacity < 1)
	{
		delete[] m_items;
		throw EXCEPTION(MyBadArgumentException, "Capacity must be greater then 0");
	}
}
//DTOR
template <typename T>
RingBuffer<T>::~RingBuffer()
{
	delete [] m_items;
}

//CCTOR
template <typename T>
RingBuffer<T>::RingBuffer(RingBuffer<T> const& _source)
:m_capacity(_source.m_capacity)
,m_items(new T[m_capacity])
{
	init(_source);
}

//Assignment operator
template <typename T>
RingBuffer<T>& RingBuffer<T>::operator= (RingBuffer<T> const& _source) throw (MyOverFlowException)
{
	if(m_capacity < _source.m_size)
	{
		throw EXCEPTION(MyOverFlowException,"Source is too big");
	}
	else if(this != &_source)
	{	
		init(_source);
	}
	
	return *this;
}


//public funcs
template<typename T>
inline void RingBuffer<T>::enqueue(const T& _value) throw(MyOverFlowException)
{
	if(!isFull())
	{
		m_items[m_tail++] = _value;
		m_tail %= m_capacity; 
		++m_size;
	}

	else
	{
		throw EXCEPTION(MyOverFlowException, "Ring buffer is full");
	}
	
}

template<typename T>
inline void RingBuffer<T>::dequeue(T& _value) throw (MyUnderFlowException)
{
	if(!isEmpty())
	{
		_value = m_items[m_head++];
		m_head %= m_capacity;
		--m_size;
	}
	else
	{
		throw EXCEPTION(MyUnderFlowException, "Ring buffer is empty");
	}
}

template<typename T>
inline bool RingBuffer<T>::isFull() const
{
	return m_size == m_capacity;
}

template<typename T>
inline bool RingBuffer<T>::isEmpty() const
{
	return m_size == 0;
}

template<typename T>
inline const T& RingBuffer<T>::front() const
{
	return m_items[m_head];
}

template<typename T>
inline size_t RingBuffer<T>::size() const
{
	return m_size;
}

template<typename T>
inline void RingBuffer<T>::print(std::ostream& _os) const
{
	dump(_os,"Print:",m_size);
}

template<typename T>
inline void RingBuffer<T>::trace(std::ostream& _os) const
{
	dump(_os,"Trace:",m_capacity);
}

// private funcs
template <typename T>
inline void RingBuffer<T>::init(RingBuffer<T> const& _source)
{
	size_t i = m_head;
	for(size_t c = 0; c < _source.m_size; ++c)
	{
		m_items[c] = _source.m_items[i];
		i = (i+1)%m_capacity;
	}	
	
	m_head = 0;
	m_tail = _source.m_size;
	m_size = _source.m_size;
	
}

template<typename T>
void RingBuffer<T>::dump(std::ostream& _os, const char* _header, size_t _n) const
{
	_os << _header << '\n';
	
	size_t i=m_head;
	for(size_t j = 0; j < _n-1; i = (i+1)%m_capacity, ++j)
	{
		_os << m_items[i] << ", ";
	}
	_os << m_items[i] << '\n';	
}

//global funcs
template<typename T>
inline std::ostream& operator<< (std::ostream& _os, RingBuffer<T> const& _ringBuffer)
{
	_ringBuffer.print(_os);
	return _os;
}

#endif	/* RINGBUFFER_H */

