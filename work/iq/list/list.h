#ifndef LIST_H
#define LIST_H

#include<iostream>

template<typename T>
class Node;

template<typename T>
class List
{
public:
    List();
    ~List();
    bool add(T const& a_val);
    bool remove(T const& a_val);
    void print() const;

private:
    void pushHead(Node<T>* a_node);

private:
    Node<T>* m_head;
};

template<typename T>
List<T>::List()
:m_head(0)
{
}

template<typename T>
List<T>::~List()
{
       
    while(m_head)
    {
        Node<T>* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
}

template<typename T>
bool List<T>::add(T const& a_val)
{
    Node<T>* node = new Node<T>(a_val);
    if(!node)
    {
        return false;
    }
    
    node->m_data = a_val;
    pushHead(node);
    return true;
}

template<typename T>
void List<T>::pushHead(Node<T>* a_node)
{
    a_node->m_next = m_head;
    m_head = a_node;
}

template<typename T>
void List<T>::print() const
{
    Node<T>* temp = m_head;
    while (temp)
    {
        std::cout << temp->m_data << " ";
        temp = temp->m_next;
    }

    std::cout << std::endl;
    
}

template<typename T>
bool List<T>::remove(T const& a_val)
{
    
    if(!m_head) //empty
    {
        return false;
    }

    if(!m_head->m_next) // one elem
    {
        if(a_val == m_head->m_data)
        {
            delete m_head;
            m_head = 0;
            return true;
        }   

        return false;
    }

    Node<T>* curr = m_head->m_next;
    Node<T>* prev = m_head;

    if(prev->m_data == a_val)
    {
        m_head = curr;
        delete prev;
        return true;
    }

    while(curr->m_next)
    {
        if(curr->m_data == a_val)
        {
            prev->m_next = curr->m_next; 
            delete curr;
            return true;
        }
        
        prev = curr;
        curr = curr->m_next;
    }
    
    if(curr->m_data == a_val)
    {
        prev->m_next = 0;
        delete curr;
        return true;
    }

   return false;
}





#endif