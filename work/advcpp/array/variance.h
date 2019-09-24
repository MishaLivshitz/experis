#ifndef VARIANCE_H
#define VARIANCE_H

#include <cstddef>
#include "FillFunc.h"
#include "reverse_iterator.h"

template<typename T>
class Variance
{
public:
    static void activateDestructor( MyReverseIterator::reverse_iterator<T> a_begin,
                                    MyReverseIterator::reverse_iterator<T> a_end);

    static void activateConstructor(T* a_begin, T* a_end);
    static void copyConstructor(T* a_begin, T* a_end, T const* a_otherBegin);
    static void assignment(T* a_begin, T* a_end, T const* a_otherBegin);
    static void fill(T* a_begin, T* a_end, T const& item);

private:
    static T& assing(T& a_elem, T const& _rhs);

};

template<typename T>
class Variance<T*>
{
public:
    static void activateDestructor( MyReverseIterator::reverse_iterator<T*> a_begin,
                                    MyReverseIterator::reverse_iterator<T*> a_end);
                                    
    static void activateConstructor(T** a_begin, T** a_end);
    static void copyConstructor(T** a_begin, T** a_end, T* const* a_otherBegin);
    static void assignment(T** a_begin, T** a_end, T* const* a_otherBegin);
    static void fill(T** a_begin, T** a_end, T* const& item);
    

private:
    static T*   assing(T*& a_elem, T const* _rhs);
    static T*  copyConstruct(T*& a_elem, T const* _rhs);
    static void construct(T*& a_elem);
    static void destruct(T*& a_elem);
};


//Variance
template<typename T>
T& Variance<T>::assing(T& a_elem, T const& _rhs)
{
    a_elem = _rhs;
    return a_elem;
}

template<typename T>
void Variance<T>::activateDestructor(MyReverseIterator::reverse_iterator<T> a_begin, MyReverseIterator::reverse_iterator<T> a_end)
{

}

template<typename T>
void Variance<T>::activateConstructor(T* a_begin, T* a_end)
{

}

template<typename T>
void Variance<T>::copyConstructor(T* a_begin, T* a_end, T const* a_otherBegin)
{
    assignment(a_begin, a_end, a_otherBegin);
}

template<typename T>
void Variance<T>::assignment(T* a_begin, T* a_end, T const* a_otherBegin)
{
    std::transform(a_begin, a_end, a_otherBegin, a_begin, assing);
}

template<typename T>
void Variance<T>::fill(T* a_begin, T* a_end, T const& _rhs)
{
    std::for_each(a_begin, a_end, FillFunc<T>(_rhs));
}

//Variance Pointers
template<typename T>
void Variance<T*>::activateDestructor(  MyReverseIterator::reverse_iterator<T*> a_begin,
                                        MyReverseIterator::reverse_iterator<T*> a_end)
{
    std::for_each(a_begin, a_end, destruct);
}
template<typename T>
void Variance<T*>::activateConstructor(T**  a_begin, T** a_end)
{
    std::for_each(a_begin, a_end, construct);
}

template<typename T>
void Variance<T*>::copyConstructor(T** a_begin, T** a_end, T* const* a_otherBegin)
{
    std::transform(a_begin, a_end, a_otherBegin, a_begin, copyConstruct);
}

template<typename T>
void Variance<T*>::assignment(T** a_begin, T** a_end, T* const* a_otherBegin)
{
    std::transform(a_begin, a_end, a_otherBegin, a_begin, assing);
}

template<typename T>
T* Variance<T*>::assing(T*& a_elem, T const* _rhs)
{
    if(a_elem == 0)
    {
        a_elem = new T(*_rhs);
    }
    else
    {
        delete a_elem;
        a_elem = new T(*_rhs);
    }   
        
    return a_elem;
}


template<typename T>
T* Variance<T*>::copyConstruct(T*& a_elem, T const* _rhs)
{
    a_elem = new T(*_rhs);
    return a_elem;
}

template<typename T>
void Variance<T*>::construct(T*& a_elem)
{
    a_elem = 0;
}

template<typename T>
void Variance<T*>::destruct(T*& a_elem)
{
    delete a_elem;
}

template<typename T>
void Variance<T*>::fill(T** a_begin, T** a_end, T* const& _rhs)
{
    std::for_each(a_begin, a_end, FillFunc<T>(_rhs));
}

#endif