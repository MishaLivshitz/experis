#ifndef BIT_SET_H
#define BIT_SET_H

#include "BitSetBase.h"
#include <string>

namespace advcpp{


template <size_t N>
class BitSet: public BitSetBase
{

public:
    
    BitSet();
    BitSet(std::string const& a_str);
    BitSet(BitSet const&);

    BitSet& operator&=(BitSet const& a_rhs);
    BitSet& operator|=(BitSet const& a_rhs);
    BitSet& operator^=(BitSet const& a_rhs);

};

template <size_t N>
BitSet<N>& BitSet<N>::operator&=(BitSet<N> const& a_rhs)
{
    BitSetBase::operator&=(a_rhs);
    return *this;
}

template <size_t N>
BitSet<N>& BitSet<N>::operator|=(BitSet<N> const& a_rhs)
{
    BitSetBase::operator|=(a_rhs);
    return *this;
}

template <size_t N>
BitSet<N>& BitSet<N>::operator^=(BitSet<N> const& a_rhs)
{
    BitSetBase::operator^=(a_rhs);
    return *this;
}

template <size_t N>
BitSet<N>::BitSet()
:BitSetBase(N)
{

}

template <size_t N>
BitSet<N>::BitSet(std::string const& a_str)
:BitSetBase(N)
{
    size_t const size = a_str.size();
    // need to throw exception or something if size greater then N
    for(size_t i = 0; i < size; ++i)
    {
        if(a_str[i] == '1')
        {
            this->set(i);
        }
    }
}

template <size_t N>
BitSet<N>::BitSet(BitSet<N> const& a_rhs)
:BitSetBase(a_rhs)
{
    
}


} //advcpp



#endif