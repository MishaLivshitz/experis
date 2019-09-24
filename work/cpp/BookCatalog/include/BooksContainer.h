#ifndef BOOK_CONTAINER
#define BOOK_CONTAINER

#include <map>

template<typename K,typename V>
class BooksContainer: private std::map<K,V>
{

typedef std::map<K,V> Base;
public:

    BooksContainer();
    V& operator[]( const K& key);
   
};


template<typename K,typename V>
BooksContainer<K,V>::BooksContainer()
:Base()
{}
 
template<typename K,typename V>
V& BooksContainer<K,V>::operator[]( const K& _key)
{
    return Base::operator[](_key);
}


#endif