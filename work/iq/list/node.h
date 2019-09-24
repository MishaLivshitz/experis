#ifndef NODE_H
#define NODE_H

#include "list.h"

template<typename T>
class Node
{
    
    friend class List<T>;

public:
    Node(T const& data = 0);
    T const& data() const;

private:
    Node* m_next;
    T m_data;
    
};

template<typename T>
Node<T>::Node(T const& data)
:m_next(0)
,m_data(data)
{

}

template<typename T>
T const& Node<T>::data() const
{
    return m_data;
}

#endif