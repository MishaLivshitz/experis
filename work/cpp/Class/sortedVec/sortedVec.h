#ifndef SORTED_VEC_H
#define SORTED_VEC_H

#include <iostream>
#include <vector>

template<typename T>
class SortedVector: private std::vector<T>
{
typedef std::vector<T> Base;
typedef typename Base::iterator SortedVectorIterator;
public:
        SortedVector(); // = default
        SortedVector(SortedVector const&); // = default;
        size_t size() const;
        void pop_back();
        void insert(T const& a_value);
        void erase(size_t a_index);
        void erase(SortedVectorIterator a_iter);
        void erase(SortedVectorIterator a_begin, SortedVectorIterator _end);
        const T& operator[](size_t a_pos) const;
        void print(std::ostream& _os) const;
        SortedVectorIterator begin();
        SortedVectorIterator end();
};


template<typename T>
 SortedVector<T>::SortedVector()
 {
 }

template<typename T>
std::ostream& operator<< (std::ostream& _os ,SortedVector<T> const& _sVec)
{
    _sVec.print(_os);
    return _os;
}

template<typename T>
inline typename SortedVector<T>::SortedVectorIterator SortedVector<T>::begin()
{
    return Base::begin();
}
template<typename T>
inline typename SortedVector<T>::SortedVectorIterator SortedVector<T>::end()
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
inline T const& SortedVector<T>::operator[] (size_t _indx) const
{
    return Base::operator[](_indx);
}


template<typename T>
inline void SortedVector<T>::erase(SortedVectorIterator _iter)
{
    if(0 == size())
    {
        return;
    }
    
    Base::erase(_iter);

}

template<typename T>
inline void SortedVector<T>::erase(SortedVectorIterator _begin, SortedVectorIterator _end)
{
    if(0 == size())
    {
        return;
    }

    Base::erase(_begin,_end);
    
}

template<typename T>
void SortedVector<T>::insert(T const& a_value)
{
    //Base::push_back(a_value);

    SortedVectorIterator itrBegin = begin();
    SortedVectorIterator itrEnd = end();

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
void SortedVector<T>::print(std::ostream& _os) const
{
    typename Base::const_iterator itrBegin = Base::begin();
    typename Base::const_iterator itrEnd = Base::end();

     for(;itrBegin!=itrEnd;++itrBegin)
     {
        _os << *itrBegin << " ";
     }
}

#endif