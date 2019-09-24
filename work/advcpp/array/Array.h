#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>      /*  size_t */
#include <iostream>
#include <algorithm>
#include "PrintVar.h"
#include "variance.h"
#include "reverse_iterator.h"

namespace spex {

    template<typename T, size_t N>
    class Array
    {
    public:
        Array();
        ~Array();
        Array(Array<T,N> const&);
        Array<T,N>& operator= (Array<T,N> const&);
        void fill(T const& _item);
        
        T& operator[](size_t index);
        T const& operator[](size_t index) const;
        
        size_t size() const;
        T* begin();
        T* end();
        T const* cbegin() const;
        T const* cend() const;

        MyReverseIterator::reverse_iterator<T>        rbegin();
        MyReverseIterator::reverse_iterator<T>        rend();
        MyReverseIterator::reverse_iterator<T const>  crbegin();
        MyReverseIterator::reverse_iterator<T const>  crend();

    private:

        T m_data[N];
        
    };



/*Array of T* */

template<typename T, size_t N>
Array<T,N>::Array()
{
    Variance<T>::activateConstructor(begin(), end());
}

template<typename T, size_t N>
Array<T,N>::Array(Array<T,N> const& _rhs)
{
    Variance<T>::copyConstructor(begin(), end(), _rhs.cbegin());
}

template<typename T, size_t N>
Array<T,N>& Array<T,N>::operator= (Array<T,N> const& _rhs)
{
    Variance<T>::assignment(begin(), end(), _rhs.cbegin());
    return *this; 
}

template<typename T, size_t N>
Array<T,N>::~Array()
{
    Variance<T>::activateDestructor(rbegin(), rend());
}

template<typename T, size_t N>
T& Array<T,N>::operator[](size_t index)
{
    T const& val = const_cast<Array<T,N> const*>(this)->operator[](index);
    return const_cast<T&>(val);
}

template<typename T, size_t N>
T const & Array<T,N>::operator[](size_t index) const
{
    return m_data[index];
}

template<typename T, size_t N>
size_t Array<T,N>::size() const
{
    return N;
}

template<typename T, size_t N>
MyReverseIterator::reverse_iterator<T> Array<T,N>::rbegin()
{
    MyReverseIterator::reverse_iterator<T> itrBegin(end());
    ++itrBegin;
    return itrBegin;
}

template<typename T, size_t N>
MyReverseIterator::reverse_iterator<T> Array<T,N>::rend()
{
    MyReverseIterator::reverse_iterator<T> itrEnd(begin());
    ++itrEnd;
    return itrEnd;
}

template<typename T, size_t N>
MyReverseIterator::reverse_iterator<T const>  Array<T,N>::crbegin()
{
    MyReverseIterator::reverse_iterator<T const>  itrBegin(end());
    ++itrBegin;
    return itrBegin;
}

template<typename T, size_t N>
MyReverseIterator::reverse_iterator<T const>  Array<T,N>::crend()
{
    MyReverseIterator::reverse_iterator<T const> itrEnd(begin());
    ++itrEnd;
    return itrEnd;
}

template<typename T, size_t N>
T* Array<T,N>::begin()
{
    return m_data;
}

template<typename T, size_t N>
T* Array<T,N>::end()
{
    return m_data+N;
}

template<typename T, size_t N>
T const* Array<T,N>::cbegin() const
{
    return m_data;
}

template<typename T, size_t N>
T const* Array<T,N>::cend() const
{
    return m_data+N;
}

template<typename T, size_t N>
void Array<T,N>::fill(T const& _item)
{
    Variance<T>::fill(begin(), end(), _item);
}

/*End of array of T* */

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& _os, Array<T,N> const& _arr)
{
    T const* itrLast = _arr.cend() - 1;

    _os << '[';
    std::for_each(_arr.cbegin(), itrLast, PrintVar<T>(_os));
    _os << *itrLast << "]";

    return _os;
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& _os, Array<T*,N> const& _arr)
{
    PrintVar<T>func(_os);
     
    T* const* itrLast = _arr.cend() - 1;

    _os << '[';
    std::for_each(_arr.cbegin(), itrLast, func);
    _os << **itrLast << "]";

    return _os;
}

} /* spex */








#endif /*   ARRAY_H  */