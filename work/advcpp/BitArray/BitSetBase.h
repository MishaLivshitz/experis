#ifndef BIT_SET_BASE_H
#define BIT_SET_BASE_H

#include <cstddef>
#include <iostream>
#include <climits>


namespace advcpp{

class BitSetBase
{
    
public:
    BitSetBase(size_t a_size);
    BitSetBase(BitSetBase const& a_rhs);

    BitSetBase& operator=(BitSetBase const& a_rhs);
    BitSetBase& operator&=(BitSetBase const& a_rhs);
    BitSetBase& operator|=(BitSetBase const& a_rhs);
    BitSetBase& operator^=(BitSetBase const& a_rhs);

    void set(size_t a_indx);
    void clear(size_t a_indx);
    void flip(size_t a_indx);
    void print(std::ostream& _os) const;
    bool any() const;
    bool none() const;
    bool all() const;
    size_t count() const;

    size_t operator[](size_t indx) const;

    ~BitSetBase();

private:
    void initSet();
    void calcMask(size_t& a_mask, size_t& a_cell,size_t a_indx) const;
    static bool initLut();

private:
    size_t* m_bits;
    size_t  m_size;
    size_t  m_arrSize;
    static const size_t s_NUM_OF_BITS;
    static char s_LUT[UCHAR_MAX + 1];
    static const bool initializer;
};


std::ostream& operator << (std::ostream& a_os, BitSetBase const& a_bitSet);

}//advcpp


#endif //BIT_SET_BASE_H