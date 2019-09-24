#ifndef IS_SORTED_H
#define IS_SORTED_H

#include<iostream>

template <typename T>
bool isSorted(T& a_container)
{
    typename T::const_iterator itrBegin = a_container.cbegin();
    typename T::const_iterator itrEnd = a_container.cend();
    typename T::const_iterator prev;

    prev = itrBegin;
    
    while(itrBegin!=itrEnd)
    {
        if(*prev>*itrBegin)
        {
            return false;
        }
        prev = itrBegin;
          ++itrBegin;
    }

    return true;
}
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




#endif