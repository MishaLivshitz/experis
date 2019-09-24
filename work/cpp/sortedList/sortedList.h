#ifndef SORTED_VEC_H
#define SORTED_VEC_H

#include <iostream>
#include <list>

template<typename T>
class SortedList: private std::list<T>
{
typedef typename std::list<T> Base;    

public:
       typedef typename Base::const_iterator ConstIterator;
       typedef typename Base::iterator Iterator;
        SortedList(); // = default
        SortedList(SortedList const&); // = default;
        SortedList& operator=(SortedList const&); // = default;
	    //~SortedList(); // = default; Why segmentation fault??
        size_t size() const;
        void pop_back();
        void insert(T const& a_value);
        void erase(size_t a_index);
        void erase(Iterator a_iter);
        void erase(Iterator a_begin, Iterator _end);
        const T& operator[](size_t a_pos) const;
        void print(std::ostream& _os) const;
        ConstIterator cbegin(int _n = 0);
        ConstIterator cend();
        Iterator begin(int _n = 0);
        Iterator end();

private:
        void advance();
};


template<typename T>
 SortedList<T>::SortedList()
 :Base()
 {
 }

template<typename T>
SortedList<T>::SortedList(SortedList const& _rhs)
:Base(_rhs)
{

}

template<typename T>
SortedList<T>& SortedList<T>::operator=(SortedList const& _rhs)
{
    Base::operator=(_rhs);
    return *this;
}

template<typename T>
std::ostream& operator<< (std::ostream& _os ,SortedList<T> const& _sVec)
{
    _sVec.print(_os);
    return _os;
}

template<typename T>
inline typename SortedList<T>::ConstIterator SortedList<T>::cbegin(int _n) 
{
    ConstIterator it = Base::begin();

    if(_n>0)
    {
        std::advance(it, _n);
    }
   
    return it;
}
template<typename T>
inline typename SortedList<T>::ConstIterator SortedList<T>::cend()
{
    return Base::end();
}

template<typename T>
inline typename SortedList<T>::Iterator SortedList<T>::begin(int _n) 
{
    Iterator it = Base::begin();

    if(_n>0)
    {
        std::advance(it, _n);
    }
   
    return it;
}
template<typename T>
inline typename SortedList<T>::Iterator SortedList<T>::end()
{
    return Base::end();
}

template<typename T>
inline size_t SortedList<T>::size() const 
{
    return Base::size();
}

template<typename T>
inline void SortedList<T>::pop_back()
{
    if(0 < size())
    {
        Base::pop_back();
    }
}

template<typename T>
inline T const& SortedList<T>::operator[] (size_t _indx) const
{
   /* ConstIterator itrBegin = begin(_indx);
    return *itrBegin;*/
}

template<typename T>
inline void SortedList<T>::erase(Iterator _iter)
{
    if(0 == size())
    {
        return;
    }
    
    Base::erase(_iter);

}

template<typename T>
inline void SortedList<T>::erase(Iterator _begin, Iterator _end)
{
    if(0 == size())
    {
        return;
    }

    Base::erase(_begin,_end);
    
}

template<typename T>
void SortedList<T>::insert(T const& a_value)
{
    //Base::push_back(a_value);

    typename std::list<T>::iterator itrBegin = Base::begin();
    typename std::list<T>::iterator itrEnd = Base::end();

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
void SortedList<T>::print(std::ostream& _os) const
{
    typename Base::const_iterator itrBegin = Base::begin();
    typename Base::const_iterator itrEnd = Base::end();

     for(;itrBegin!=itrEnd;++itrBegin)
     {
        _os << *itrBegin << " ";
     }
}

#endif