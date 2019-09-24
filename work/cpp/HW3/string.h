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
#include <iostream>

class String
{
public:
	String(const char* _source = "");
	~String();

// Copy CTOR
	String(String const& _source);
// assignment operator
	String& operator=(const String& _source);

	size_t length() const;

	void print(std::ostream& _os) const;
	char const* get() const;
	static size_t getObjCount();
	
private:
	void grow(size_t _newSize);
	void init(char const* _src);
	
private:
	char*	m_chars;
	static size_t s_objCount;
	
};

inline size_t String::getObjCount()
{
	return s_objCount;
}

std::ostream& operator<<(std::ostream& _os, String const& _rhs);
int compare(const String& _first, const String& _second);

#endif // STRING_CLASS_H
