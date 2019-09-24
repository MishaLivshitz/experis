#include "BitSetBase.h"
#include <cstring>

namespace advcpp{

const size_t BitSetBase::s_NUM_OF_BITS = sizeof(unsigned long) * CHAR_BIT;
char BitSetBase::s_LUT[UCHAR_MAX + 1] = {0};
const bool BitSetBase::initializer = initLut();


BitSetBase::BitSetBase(size_t a_size)
:m_size(a_size)
,m_arrSize(a_size)
{
    initSet();
}

BitSetBase::BitSetBase(BitSetBase const& a_rhs)
:m_size(a_rhs.m_size)
,m_arrSize(a_rhs.m_arrSize)
{
    initSet();
    memcpy(m_bits, a_rhs.m_bits, m_arrSize);
}

BitSetBase& BitSetBase::operator=(BitSetBase const& a_rhs)
{
    m_size = a_rhs.m_size;
    m_arrSize = a_rhs.m_arrSize;
    
    delete m_bits;

    initSet();
    memcpy(m_bits, a_rhs.m_bits, m_arrSize);

    return *this;
}

BitSetBase::~BitSetBase()
{
    delete m_bits;
}

size_t BitSetBase::operator[](size_t indx) const
{
    size_t cell;
    cell = indx / s_NUM_OF_BITS;
    return (m_bits[cell] >> (s_NUM_OF_BITS - (indx - cell * s_NUM_OF_BITS))) & 0x1UL;
}

BitSetBase& BitSetBase::operator&=(BitSetBase const& a_rhs)
{
    for(size_t i = 0; i < m_arrSize; ++i)
    {
        m_bits[i] &= a_rhs.m_bits[i];
    }

    return *this;
}

BitSetBase& BitSetBase::operator|=(BitSetBase const& a_rhs)
{
    for(size_t i = 0; i < m_arrSize; ++i)
    {
        m_bits[i] |= a_rhs.m_bits[i];
    }

    return *this;
}

BitSetBase& BitSetBase::operator^=(BitSetBase const& a_rhs)
{
    for(size_t i = 0; i < m_arrSize; ++i)
    {
        m_bits[i] ^= a_rhs.m_bits[i];
    }

    return *this;
}

bool BitSetBase::any() const
{
    for(size_t i = 0; i < m_arrSize; ++i)
    {
        if(m_bits[i] != 0x0UL)
        {
            return true;
        }
    }

    return false;
}

bool BitSetBase::none() const
{
    return !any();
}

bool BitSetBase::all() const
{
    size_t rem = m_size % s_NUM_OF_BITS;

    for(size_t i = 0; i < m_arrSize-1; ++i)
    {
        if(m_bits[i] != 0x1UL)
        {
            return false;
        }
    }

    for(size_t i = 0 ; i < rem; ++i)
    {
        BitSetBase const& b = *this;
        if(b[(m_arrSize - 1) * s_NUM_OF_BITS + i] != 0x1UL)
        {
            return false;
        }
    }

    return true;
}

void BitSetBase::print(std::ostream& a_os) const
{
    for(size_t i = 0; i < m_size; ++i)
    {
        a_os << this->operator[](i);
    }
}

void BitSetBase::initSet()
{
    while(m_arrSize % s_NUM_OF_BITS !=0)
    {
        ++m_arrSize;
    }

    m_arrSize /= s_NUM_OF_BITS;
    m_bits = new unsigned long(m_arrSize);
    memset(m_bits,0,m_arrSize);
}

void BitSetBase::calcMask(size_t& a_mask, size_t& a_cell,size_t a_indx) const
{
    a_cell = a_indx / s_NUM_OF_BITS;
    a_indx -= a_cell*s_NUM_OF_BITS;
    a_mask = 0x1UL << (s_NUM_OF_BITS - a_indx);
}

void BitSetBase::set(size_t a_indx)
{
    if(a_indx < m_size)
    {
        size_t cell;
        size_t mask;

        calcMask(mask, cell, a_indx);
        m_bits[cell] |= mask;
    }
}

void BitSetBase::clear(size_t a_indx)
{
    if(a_indx < m_size)
    {
        size_t cell;
        size_t mask;

        calcMask(mask,cell,a_indx);
        m_bits[cell] &= ~mask;
    }
}

void BitSetBase::flip(size_t a_indx)
{
    size_t cell;
    size_t mask;

    calcMask(mask,cell,a_indx);
    m_bits[cell] ^= mask;
}

bool BitSetBase::initLut()
{

    for(size_t i = 0; i <= UCHAR_MAX; ++i)
    {
        size_t j = i;
        size_t counter = 0;
        while (j!=0)
        {
            counter += j & 1UL;
            j >>= 1;
        }

        BitSetBase::s_LUT[i] = counter;
    }

    return true;
}

size_t BitSetBase::count() const
{
    size_t counter = 0;
    for(size_t i = 0; i < m_arrSize; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            char val = m_bits[i] >> 8*j;
            counter += s_LUT[(int)val];        
        }
    }

   // char val = m_bits[m_arrSize - 1] >> m_size % s_NUM_OF_BITS;


    return counter;
}

std::ostream& operator << (std::ostream& a_os, BitSetBase const& a_bitSet)
{
    a_bitSet.print(a_os);
    return a_os;
}


}//advcpp