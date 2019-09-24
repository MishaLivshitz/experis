#ifndef SORTED_VEC_H
#define SORTED_VEC_H

#include <iostream>
#include <vector>

template<typename T>
class SortedVector: private std::vector<T>
{
        typedef std::vector<T> Base;
public:
        typedef typename Base::iterator iterator;

        SortedVector(); // = default
        SortedVector(SortedVector const&); // = default;
        SortedVector& operator=(SortedVector const&); // = default;
        ~SortedVector(); // = default;

        size_t size() const;
        void pop_back();
        void insert(T const& a_value);
        void erase(size_t a_index);
        void erase(iterator a_iter);
        void erase(iterator a_begin, iterator a_end);
        const T& operator[](size_t a_pos) const;
        void print(std::ostream& _os) const;
        iterator begin();
        iterator end();
};


template<typename T>
SortedVector<T>::SortedVector()
:Base()
{
}

template<typename T>
SortedVector<T>::SortedVector(SortedVector const& _rhs)
:Base(_rhs)
{ 
}

template<typename T>
SortedVector<T>::~SortedVector()
{
  Base::~Base();
}

template<typename T>
SortedVector<T>& SortedVector<T>::operator= (SortedVector<T> const& a_rhs)
{
    Base::operator=(a_rhs);
    return *this;
}
template<typename T>
std::ostream& operator<< (std::ostream& a_os ,SortedVector<T> const& a_sVec)
{
    a_sVec.print(a_os);
    return a_os;
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
inline void SortedVector<T>::erase(iterator a_iter)
{
    if(0 == size())
    {
        return;
    }
    
    Base::erase(a_iter);

}

template<typename T>
inline void SortedVector<T>::erase(iterator a_begin, iterator a_end)
{
    if(0 == size())
    {
        return;
    }

    Base::erase(a_begin,a_end);
    
}

template<typename T>
void SortedVector<T>::insert(T const& a_value)
{
    //Base::push_back(a_value);

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


template<typename T>
void SortedVector<T>::print(std::ostream& a_os) const
{
    typename Base::const_iterator itrBegin = Base::begin();
    typename Base::const_iterator itrEnd = Base::end();

     for(;itrBegin!=itrEnd;++itrBegin)
     {
        a_os << *itrBegin << " ";
     }
}

#endif