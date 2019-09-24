#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <vector>
#include <map>
#include <cmath>


using std::vector;
using std::map;
using std::pair;

template <typename K, typename V, int (*hf)(K)>
class HashMap: private vector<map<K,V> >
{

public:
    HashMap(size_t _capacity);
    //HashMap& operator= (HashMap const& _rhs);
    ~HashMap();

    V const* operator[] (K _key);
    
    void insert(K const& _key, V const& _val);
    pair<V const*, int> find(K const& _key) const;
    void remove(K const& _key);
    void clear();
    void rehash();
    void print() const;

private:
    HashMap(HashMap const& _rhs);
    typedef vector<map<K,V> > Base;
    size_t findNextPrime(size_t) const;
    bool isPrime(size_t) const;
    bool isOccupied(size_t) const;


private:
    size_t m_size;

};

template <typename K, typename V, int (*hf)(K)>
inline bool HashMap<K, V, hf>::isOccupied(size_t _index) const
{
    return Base::operator[](_index).size() > 0;
}


template <typename K, typename V, int (*hf)(K)>
void HashMap<K, V, hf>::rehash()
{
    HashMap tempMap(this->capacity()*2);
    size_t const size = this->size();

    for(size_t i = 0; i < size; ++i)
    {
        if(isOccupied(i))
        {
            typename map<K,V>::iterator itrB = Base::operator[](i).begin();
            typename map<K,V>::iterator itrE = Base::operator[](i).end();

            while(itrB != itrE)
            {
                tempMap.insert(itrB->first,itrB->second);
                ++itrB;
            }
        }
    }

    this->clear();
    this->reserve(tempMap.capacity());
    *this = tempMap;

}

template <typename K, typename V, int (*hf)(K)>
void HashMap<K, V, hf>::clear()
{
    size_t size = this->size();
    for(size_t i=0;i<size;++i)
    {
       Base::operator[](i).clear(); 
    }
    m_size = 0;
}

template <typename K, typename V, int (*hf)(K)>
inline void HashMap<K, V, hf>::insert(K const& _key, V const& _val)
{
    size_t index = hf(_key) % this->capacity();
    Base::operator[](index)[_key] = _val;
    ++m_size;
}

template <typename K, typename V, int (*hf)(K)>
inline void HashMap<K, V, hf>::remove(K const& _key)
{
    pair<V const*, int> p;
    int index = find(_key).second;
    if(index > -1)
    {
        typename map<K,V>::iterator itr = Base::operator[](index).find(_key);
        Base::operator[](index).erase(itr);
        --m_size;
    }
}

template <typename K, typename V, int (*hf)(K)>
inline pair<V const*, int> HashMap<K, V, hf>::find(K const& _key) const
{
    size_t index = hf(_key) % this->capacity();
    typename map<K,V>::const_iterator itr;

    itr = Base::operator[](index).find(_key);

    return itr == Base::operator[](index).end() ? pair<V const*, int>(0,-1): pair<V const*, int>(&itr->second, index);  
}

template <typename K, typename V, int (*hf)(K)>
inline V const* HashMap<K, V, hf>::operator[] (K _key)
{
   pair<V const*, int> p = find(_key);

   return p.second > 0 ? p.first : 0;
}

template <typename K, typename V, int (*hf)(K)>
HashMap<K, V, hf>::HashMap(size_t _capacity)
:Base(findNextPrime(_capacity),map<K,V>())
,m_size(0)
{
  
}

template <typename K, typename V, int (*hf)(K)>
HashMap<K, V, hf>:: ~HashMap()
{

}

template <typename K, typename V, int (*hf)(K)>
size_t HashMap<K, V, hf>::findNextPrime(size_t _number) const
{
    while(!isPrime(_number))
    {
        ++_number;
    }
    return _number;
}

template <typename K, typename V, int (*hf)(K)>
bool HashMap<K, V, hf>::isPrime(size_t _number) const
{
    size_t sqrtNum = sqrt(_number);

    for(size_t i = 2 ;i < sqrtNum; ++i)
    {
        if(_number%i == 0)
        {
            return false;
        }
    }

    return true;
}

template <typename K, typename V, int (*hf)(K)>
void HashMap<K, V, hf>::print() const
{
    size_t size = this->size();

    for(size_t i = 0; i < size; ++i)
    {
        if(isOccupied(i))
        {
            typename map<K,V>::const_iterator itrB = Base::operator[](i).begin();
            typename map<K,V>::const_iterator itrE = Base::operator[](i).end();

            while(itrB != itrE)
            {
                std::cout << itrB->second << ' ';
                ++itrB;
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

}



#endif