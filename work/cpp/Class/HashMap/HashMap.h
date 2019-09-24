#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <vector>
#include <iostream>
#include "MyException.h"

using std::vector;

// template <typname T>
class HashMap
{

typedef int T;

public:
    HashMap(size_t _capacity = 7) throw(MyException);

    void add(T const&);
    void remove(T const&);    
    T const& find(T const&) const;
    void print() const;

private:
    int findNextPrime(int _number);
    size_t hashFunc(int const& _number) const;
    size_t collisionHandler(size_t _index) const;

private:
    vector<T> m_map;
    size_t m_capacity;
    size_t maxCollisions;
    static const int s_PRIME_SIZE = 20;
    static const int s_PRIME_NUMS[s_PRIME_SIZE];

    enum State {FREE = 0, DIRTY = -1};
    static const State state;
};




#endif