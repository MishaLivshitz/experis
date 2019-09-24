#ifndef SORTED_VEC_H
#define SORTED_VEC_H

#include <iostream>
#include "Vector.h"

template<typename T>
class SortedVector: public Vector<T>
{
        typedef Vector<T> Base;
        typedef typename Base::iterator iterator;
public:
        typedef typename Base::const_iterator const_iterator;

        SortedVector(); // = default
        SortedVector(SortedVector const&); // = default;
        ~SortedVector(); // = default;
        SortedVector& operator=(SortedVector const&); // = default;

        size_t size() const;
        void pop_back();
        void insert(T const& a_value);
        void erase(const_iterator a_iter);
        void erase(const_iterator a_begin, const_iterator a_end);
        const T& operator[](size_t a_pos) const;

        /* const_iterator cbegin() const;
        const_iterator cend() const; */

private:
        iterator begin();
        iterator end();

public:
        static const std::string s_TYPE;
};

//static initializers
template <typename T>
std::string const SortedVector<T>::s_TYPE = "SortedVector";

template<typename T>
SortedVector<T>::SortedVector()
:Base()
{
   this->setType(s_TYPE);
}

template<typename T>
SortedVector<T>::SortedVector(SortedVector const& _rhs)
:Base(_rhs)
{ 
  this->setType(_rhs.m_type);
}

template<typename T>
SortedVector<T>::~SortedVector()
{
  std::cout << s_TYPE << " destructor\n";
}

 template<typename T>
SortedVector<T>& SortedVector<T>::operator= (SortedVector<T> const& a_rhs)
{
    Base::operator=(a_rhs);
    this->setType(s_TYPE);
    return *this;
}

template<typename T>
inline typename SortedVector<T>::iterator SortedVector<T>::begin()
{
    return Base::begin();
}
template<typename T>
inline typename SortedVector<T>::iterator SortedVector<T>::end()
{
    return Base::end();
}

template<typename T>
inline size_t SortedVector<T>::size() const 
{
    return Base::size();
}

template<typename T>
inline void SortedVector<T>::pop_back()
{
    if(0 < size())
    {
        Base::pop_back();
    }
}

template<typename T>
inline T const& SortedVector<T>::operator[] (size_t a_indx) const
{
    return Base::operator[](a_indx);
}


template<typename T>
inline void SortedVector<T>::erase(const_iterator a_iter)
{
    if(0 == size())
    {
        return;
    }

    iterator it = begin();
    it += std::distance(this->cbegin(),a_iter);
    Base::erase(it);

}

template<typename T>
inline void SortedVector<T>::erase(const_iterator a_begin, const_iterator a_end) 
{
    if(0 == size())
    {
        return;
    }

    iterator b = begin();
    iterator e = begin();
    b += std::distance(this->cbegin(),a_begin);
    e += std::distance(this->cbegin(),a_end);
    Base::erase(b,e);
    
}

template<typename T>
void SortedVector<T>::insert(T const& a_value)
{
    iterator itrBegin = begin();
    iterator itrEnd = end();

    for(;itrBegin != itrEnd ;++itrBegin)
    {
        if(*itrBegin>a_value)
        {
            break;
        }
    }

    Base::insert(itrBegin,a_value);
}

#endif