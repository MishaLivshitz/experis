#ifndef IS_SORTED_H
#define IS_SORTED_H

#include<iostream>
#include "Vector.h"
#include "sortedVec.h"

template<typename A ,typename T>
bool isPtrOf(A* p)
{
    return p->type() == T::s_TYPE;
}

template<typename T ,typename A>
T* tryCast(A* _p)
{
    if(isPtrOf<A,T>(_p))
    {
        T* pd = static_cast<T*>(_p);
        return pd;
    }
    return 0;
}

template <typename T>
bool isSorted(Vector<T>& a_container)
{

    if(a_container.size() <= 2 || isPtrOf<Vector<T>, SortedVector<T> >(&a_container))
    {
        return true;
    }

    typename Vector<T>::const_iterator itrBegin = a_container.cbegin();
    typename Vector<T>::const_iterator itrNext = itrBegin;
    ++itrNext;
    typename Vector<T>::const_iterator itrEnd = a_container.cend();
    bool asc = false;

    while(itrNext!= itrEnd && *itrBegin == *itrNext)
    {
        ++itrBegin;
        ++itrNext;
    }

    if(*itrBegin < *itrNext)
    {
        asc = true;
    }
    
    if(true==asc)
    {
        while(itrNext!=itrEnd)
        {
            if(*itrNext<*itrBegin)
            {
                return false;
            }

            ++itrBegin;
            ++itrNext;
        }
    }
    else
    {
         while(itrNext!=itrEnd)
        {
            if(*itrNext>*itrBegin)
            {
                return false;
            }

            ++itrBegin;
            ++itrNext;
        }
    }

    return true;
}

#endif