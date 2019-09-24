#ifndef NODE_H
#define NODE_H


template<typename T>
struct Node
{
    Node(T _val);

    Node*   m_father;
    Node*   m_left;
    Node*   m_right;
    T       m_value;     
};

template<typename T>
Node<T>::Node(T _val)
:m_value(_val)
{
    
}






#endif
