#ifndef FILL_FUNC_H
#define FILL_FUNC_H

#include <cstddef>

template<typename T>
class FillFunc
{
public:
    FillFunc(T const& _rhs);
    FillFunc(T* const& _rhs);
    void operator()(T& _lhs);
    void operator()(T*& _lhs);

private:
T const& m_rhs;
};


template<typename T>
FillFunc<T>::FillFunc(T const& _rhs)
:m_rhs(_rhs)
{

}

template<typename T>
FillFunc<T>::FillFunc(T* const& _rhs)
:m_rhs(*_rhs)
{

}

template<typename T>
void FillFunc<T>::operator()(T& _lhs)
{
    _lhs = m_rhs;
}

template<typename T>
void FillFunc<T>::operator()(T*& _lhs)
{
    _lhs = new T(m_rhs);
}

#endif