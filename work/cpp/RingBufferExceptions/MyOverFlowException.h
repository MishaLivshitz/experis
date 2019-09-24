
#include "MyException.h"

class MyOverFlowException: public MyException
{
public:
    MyOverFlowException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line);
    virtual char const* what() const NO_EXCEPT;

};

inline char const* MyOverFlowException::what() const NO_EXCEPT
{
    m_buff.clear();
    m_buff.append(m_what);
    m_buff.append(":\nin file:");
    m_buff.append(m_file);
    m_buff.append(m_func);
    m_buff.append(m_line);
   
    return m_buff.c_str();
}