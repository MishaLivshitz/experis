
#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <iostream>
#include <string.h>

#define LINE(L)	LINE_TO_STRING(L)
#define LINE_TO_STRING(L) #L
#define EXCEPTION(T,S)	T(S,__FILE__, __func__, LINE(__LINE__))
#define NO_EXCEPT throw()

class MyException: public std::exception
{

public:

    MyException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line);
    virtual ~MyException() NO_EXCEPT;    
    virtual char const* what() const NO_EXCEPT;

protected:
    std::string m_file;
    std::string m_line;
    std::string m_func;
    std::string m_what;
    static std::string m_buff; 

};

inline char const* MyException::what() const NO_EXCEPT
{
    m_buff.clear();
    m_buff += m_what + ":\nerror at:\nFile:" + m_file + "\nFunction:" +m_func +"\nLine: " + m_line + "\n";

    return m_buff.c_str();
}

#endif