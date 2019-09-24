#ifndef PRINT_VAR_H
#define PRINT_VAR_H

#include <iostream>

template<typename T>
class PrintVar
{
public:
    PrintVar(std::ostream& _os = std::cout);
    void operator()(T const&) const;
    void operator()(T const*) const;


private:

std::ostream& m_os;

};

template<typename T>
PrintVar<T>::PrintVar(std::ostream& _os)
:m_os(_os)
{

}

template<typename T>
void PrintVar<T>::operator()(T const& _var) const
{
    m_os << _var << ", ";
}

template<typename T>
void PrintVar<T>::operator()(T const* _var) const
{
   m_os << *_var << ", ";
}


#endif