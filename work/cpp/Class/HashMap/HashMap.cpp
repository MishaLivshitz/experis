#include "HashMap.h"
#include "algorithm"

HashMap::HashMap(size_t _capacity) throw(MyException)
{
    size_t i = findNextPrime(_capacity);

    if(i < s_PRIME_SIZE)
    {
        m_capacity = s_PRIME_NUMS[i];
        m_map.reserve(m_capacity);
        m_map.assign(m_capacity, FREE);
    }
    else
    { 
        throw EXCEPTION(MyException, "Capacity is too big, Max is = 853");
    }
}

int HashMap::findNextPrime(int _number)
{
    size_t i;

    for(i = 0 ; i < s_PRIME_SIZE ; ++i)
    {
        if(_number <= s_PRIME_NUMS[i])
        {
            break;
        }
    }

    return i;
}

void HashMap::add(T const& _item)
{
    if(m_map.size()==m_capacity)
    {
        //rehash
    }

    size_t nextIndex = hashFunc(_item);
  
    nextIndex = collisionHandler(nextIndex);

    m_map[nextIndex] = _item;
}

HashMap::T const& HashMap::find(T const& _item) const
{
    size_t nextIndex = hashFunc(_item);

    nextIndex = collisionHandler(nextIndex);

    return m_map[nextIndex];
}

size_t HashMap::collisionHandler(size_t _index) const
{
    size_t i = 0;
    while(m_map[_index+i] != FREE)
    {
        ++i;
        i %= m_capacity;
    }

    return (_index + i) % m_capacity;
}

size_t HashMap::hashFunc(T const& _number) const
{
    return _number % m_capacity;
}

void HashMap::print() const
{
    size_t const size = m_map.size();

    for(size_t i = 0 ;i < size - 1 ; ++i)
    {
        /* if(m_map[i] != FREE && m_map[i] != DIRTY)
        {
            std::cout << m_map[i] << ' ';
         }*/
        std::cout << m_map[i] << ' ';
    }
}


const int HashMap::s_PRIME_NUMS[] ={13, 29, 53, 101, 211, 421, 853};