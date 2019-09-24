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

template <typename T>
class Stack64 {
public:
// CTOR
	Stack64();
// DTOR
//	~Stack64();

// mem-functions
// Operations
	bool push(T const _value);
	bool pop(T& _value);
	bool top(T& _vlaue) const;
	
// Operators

// State
	bool isFull() const;
	bool isEmpty() const;

	size_t size() const;
	size_t capacity() const;
	
	void print(std::ostream& _os = std::cout) const;
	void trace(std::ostream& _os = std::cout) const;
	
private:
	void dump(std::ostream& _os, const char* _header, size_t _n) const;
// Data members
private:
	size_t			m_top;
	const size_t 	m_capacity;
	T				m_items[STACK_CAPACITY];
};

template <typename T>
Stack64<T>::Stack64()
: m_top(0)
, m_capacity(STACK_CAPACITY)
{
	for (size_t i=0; i < m_capacity; ++i)
	{
		m_items[i] = 0;
	}
}
 
// Operations
template <typename T>
inline bool Stack64<T>::push(T _value)
{
	if(isFull())
	{
		return false;
	}
	
	m_items[m_top] = _value;
	++m_top;
	
	return true;
}

template <typename T>
inline bool Stack64<T>::pop(T& _value)
{
	if(isEmpty())
	{
		return false;
	}
	
	_value = m_items[--m_top];
	
	return true;
}

template <typename T>
inline bool Stack64<T>::top(T& _value) const
{
	if(isEmpty())
	{
		return false;
	}
	
	_value = m_items[m_top-1];
	
	return true;
}

// State
template <typename T>
inline bool Stack64<T>::isFull() const
{
	return (m_top == m_capacity);
}
template <typename T>
inline bool Stack64<T>::isEmpty() const
{
	return (m_top == 0);
}
template <typename T>
inline size_t Stack64<T>::size() const
{
	return m_top;
}
template <typename T>
inline size_t Stack64<T>::capacity() const
{
	return m_capacity;
}

// print the contents of the stack
template<typename T>
void Stack64<T>::print(std::ostream& _os) const
{
	dump(_os, "stack", size());
}

template<typename T>
void Stack64<T>::trace(std::ostream& _os) const
{
	dump(_os, "trace", STACK_CAPACITY);
}

template<typename T>
void Stack64<T>::dump(std::ostream& _os, const char* _header, size_t _n) const
{
	_os << _header << '[' << m_top << "/" << STACK_CAPACITY << "]={ ";

	for (size_t i = 0; i < _n; ++i)
	{
		_os << m_items[i] << ' ';
	}
	_os << "}\n";	
}

#endif // STACK_64_H
