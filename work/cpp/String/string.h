#ifndef STRING_CLASS_H
#define STRING_CLASS_H

//
// 	Create a simple String class that will dynamically allocate memory
//	*	default CTOR
//	*	CTOR from "const char*"
//	*	copy CTOR
//	*	DTOR
//	*	assignment operator
//
//	mem-function 'length',	which returns length of the string
//	mem-function 'get',		which returns "const char*"
//	global function 'compare',	which compares 2 Strings (a, b)
//		returns:	0 - if they are equal
//					a negative number - a < b
//					a positive number - a > b
//	global stream op<< for printing

#include <cstddef>
#include <cstring>
#include <iostream>

class String
{
public:
	String(const char* _source = "");
	~String();

// Copy CTOR
	String(String const& _source);
// assignment operator
	String& operator= (String const& _source);
	
// operators	
	String& operator+= (String const& _source);
	
	bool operator!= (String const& _other) const;
	bool operator== (String const& _other) const;
	bool operator< (String const& _other) const;
	bool operator> (String const& _other) const;
	bool operator>= (String const& _other) const;
	bool operator<= (String const& _other) const;
	
	String operator() (size_t _start, size_t _leng) const;
	const char& operator[] (size_t _indx) const;
	char& operator[] (size_t _indx);

	size_t length() const;
	void print(std::ostream& _os) const;
	char const* get() const;
	bool contains(String const& _other) const;
	int findFirst(char _ch) const;
	int findLast(char _ch) const;
	size_t getCapacity() const;
	
	static size_t getObjCount();
	static void setSensitive(bool _isSensitive);
	static bool getSensitive();
	static size_t getBlockSize();
	static void setBlockSize(size_t _bSize);
	
private:
	void setCapacity(size_t _otherSize);
	void grow(size_t _newSize);
	void init(char const* _src);
	
private:
	   char*			m_chars;
	   size_t			m_size;
	   size_t			m_capacity;
static size_t 			s_objCount;
static size_t 			s_blockSize;
static bool				s_isCaseSensitive;
	
};

//public Funcs

inline size_t String::getCapacity() const
{
	return m_capacity;
}

inline size_t String::length() const
{
	return m_size;
}

inline char const* String::get() const
{
	return m_chars;
}

inline size_t String::getObjCount()
{
	return s_objCount;
}

inline bool String::getSensitive()
{
	return s_isCaseSensitive;
}

inline void String::setSensitive(bool _isSensitive)
{
	s_isCaseSensitive = _isSensitive;
}

inline size_t String::getBlockSize()
{
	return s_blockSize;
}

inline void String::setBlockSize(size_t _bSize)
{
	s_blockSize = _bSize;
}

inline bool String::contains(String const& _other) const
{
	return strstr(m_chars,_other.get()) != 0;
}

inline int String::findFirst(char _ch) const
{
	char* temp = strchr(m_chars, _ch);

	return temp == 0 ? -1 : temp - m_chars;
}

inline int String::findLast(char _ch) const
{
	char* temp = strrchr(m_chars, _ch);

	return temp == 0 ? -1 : temp - m_chars;
}

inline void String::print(std::ostream& _os) const
{
	_os << m_chars;
}

//private funcs
inline void String::grow(size_t srcLen)
{
	size_t newSize = srcLen + length();
	 
	if(m_capacity <  newSize)
	{
		setCapacity(newSize);
		char* newChars = new char[m_capacity];
		strcpy(newChars,m_chars);
		delete [] m_chars;
		m_chars = newChars;
		m_size+=newSize;
	}
}

inline void String::init(char const* _src)
{
	m_size = strlen(_src);
	setCapacity(m_size);
	m_chars = new char[m_capacity];
	strcpy(m_chars, _src);
	s_objCount++;
}

inline void String::setCapacity(size_t _newSize)
{
	m_capacity = (1 + (_newSize+1)/s_blockSize) * s_blockSize; 
}

//operators

inline const char& String::operator[](size_t _indx) const
{
	return m_chars[_indx];
}
inline char& String::operator[](size_t _indx)
{
	return m_chars[_indx];
}

inline bool String::operator==(String const& _other) const
{
	return s_isCaseSensitive == true ? strcmp(m_chars,_other.get()) == 0: strcasecmp(m_chars,_other.get()) == 0;
}

inline bool String::operator>=(String const& _other) const
{
	return s_isCaseSensitive == true ? strcmp(m_chars,_other.get()) >= 0: strcasecmp(m_chars,_other.get()) >= 0;
}

inline bool String::operator<=(String const& _other) const
{
	return s_isCaseSensitive == true ? strcmp(m_chars,_other.get()) <= 0: strcasecmp(m_chars,_other.get()) <= 0;
}

inline bool String::operator!=(String const& _other) const
{
	return !(*this == _other);
}

inline bool String::operator<(String const& _other) const
{
	return !(*this >= _other);
}

inline bool String::operator>(String const& _other) const
{
	return !(*this <= _other);
}

inline String& String::operator+=(String const& _source)
{
	grow(_source.length());
	strcat(m_chars,_source.get());
	
	return *this;
}

inline String& String::operator=(String const& _source)
{
	grow( _source.length());
	strcpy(m_chars,_source.m_chars);
	
	return *this;
}

inline String String::operator()(size_t _start, size_t _leng) const
{
	char *subStr = new char[_leng];
	strncpy(subStr, &m_chars[_start], _leng);
	subStr[_leng] = '\0';
	String temp(subStr);
	delete [] subStr;
	return temp;
}

//global

inline std::ostream& operator<<(std::ostream& _os, String const& _rhs)
{
	_rhs.print(_os);
	return _os;
}

inline String operator+(String const& _first, String const& _second)
{
	String temp(_first);
	temp += _second;
	return temp;
}

#endif // STRING_CLASS_H
