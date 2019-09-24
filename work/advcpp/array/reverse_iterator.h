#ifndef REVESE_ITR_H
#define REVESE_ITR_H

namespace MyReverseIterator{


template<typename T>
class reverse_iterator
{

public:
    reverse_iterator(T* a_pVar);

    reverse_iterator<T>& operator++();
    reverse_iterator<T> operator++(int);
    reverse_iterator<T>& operator--();
    reverse_iterator<T> operator--(int);

    T& operator*() const;
    bool operator== (reverse_iterator const& _rhs) const;    
    bool operator!= (reverse_iterator const& _rhs) const;    

private:
    T* m_pVar;
};

template<typename T>
reverse_iterator<T>::reverse_iterator(T* a_pVar)
: m_pVar(a_pVar)
{

}

template<typename T>
bool reverse_iterator<T>::operator!= (reverse_iterator const& _rhs) const
{
    return m_pVar != _rhs.m_pVar;
}

template<typename T>
bool reverse_iterator<T>::operator== (reverse_iterator const& _rhs) const
{
    return !operator!=(_rhs);
}

template<typename T>
reverse_iterator<T>& reverse_iterator<T>::operator++()
{
    --m_pVar;
    return *this;
}

template<typename T>
reverse_iterator<T> reverse_iterator<T>::operator++(int)
{
    reverse_iterator<T> temp(*this);
    --m_pVar;
    return temp;
}

template<typename T>
reverse_iterator<T>& reverse_iterator<T>::operator--()
{
    ++m_pVar;
    return *this;
}

template<typename T>
reverse_iterator<T> reverse_iterator<T>::operator--(int)
{
    reverse_iterator<T> temp(*this);
    ++m_pVar;
    return temp;
}

template<typename T>
T& reverse_iterator<T>::operator*() const
{
    return *m_pVar;
}

} // MyReverseIterator
#endif