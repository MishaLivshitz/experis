#include "string.h"
#include <cstring>


//CTOR

String::String(const char* _source)
{
	init(_source);
}

//CCTOR

String::String(String const& _rhs)
{
	init(_rhs.get());
}

//DTOR

String::~String()
{
	delete [] m_chars;
	s_objCount--;
}

//Operators

String& String::operator=(const String& _source)
{
	
	size_t srcLen = _source.length(); 
	if(srcLen > length())
	{
		grow(srcLen);
	}
	
	strcpy(m_chars,_source.m_chars);
	
	return *this;
}

//static initializers
size_t String::s_objCount = 0;

//public Funcs
size_t String::length() const
{
	return strlen(m_chars);
}

char const* String::get() const
{
	return m_chars;
}

void String::print(std::ostream& _os) const
{
	_os << m_chars;
}
//private funcs
void String::grow(size_t _newSize)
{
	char* newChars = new char[_newSize];
	strcpy(newChars,m_chars);
	delete [] m_chars;
	m_chars = newChars;
	
}

void String::init(char const* _src)
{
	m_chars = new char[strlen(_src) + 1];
	strcpy(m_chars, _src);
	s_objCount++;
}

//global funcs
std::ostream& operator<<(std::ostream& _os, String const& _rhs)
{
	_rhs.print(_os);
	return _os;
}

int compare(const String& _first, const String& _second)
{
	return strcmp(_first.get(),_second.get());
}
