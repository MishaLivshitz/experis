#ifndef UTILS_H
#define UTILS_H

#include"reverse_iterator.h"

namespace utils{

void fillAscending(int* a_begin, int* a_end)
{
    for(int i = 0; a_begin!=a_end; ++i, ++a_begin)
    {
        *a_begin = i;
    }
}

void fillDecending(int* a_begin, int* a_end)
{
    --a_end;
    for(int i = 0; a_begin!=a_end; ++i, --a_end)
    {
        *a_end = i;
    }
}


template <typename T,size_t N>
bool isPalindrom(spex::Array<T, N> const& array)
{

    int const* itrB = array.cbegin();
    int const* itrE = array.cend();

    --itrE;

    while(std::distance(itrB,itrE)>0)
    {
        if(*itrB != *itrE)
        {
            return false;
        }

        ++itrB;
        --itrE;
    }

    return true;
}

template<typename T, typename U>
void fill(T& arr, U const& item)
{
    U* itrB = arr.begin();
    U* itrE = arr.end();

    for(;itrB!=itrE; ++itrB)
    {
        *itrB = item;
    }
}

template<typename T, typename U>
void fill(T& arr, U const* item)
{
    U** itrB = arr.begin();
    U** itrE = arr.end();

    for(;itrB!=itrE; ++itrB)
    {
        *(*itrB) = *item;
    }
}

} /*utils namespace */

#endif