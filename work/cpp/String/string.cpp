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

//static initializers
size_t String::s_objCount = 0;
bool   String::s_isCaseSensitive = false;
size_t 	String::s_blockSize = 32;




