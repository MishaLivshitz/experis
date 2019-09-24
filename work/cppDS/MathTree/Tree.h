#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>

using std::string;
using std::stack;

template <typename T>
class Tree
{
public:
    Tree();
    virtual void buildTree(string const&);
    T* inOrderPrint(T* _root);
    T* root() const;

private:
    
    bool isOperator(char _ch) const;
    bool isLessOperator(char _lhs, char _rhs) const;
    void connectLeft(stack<T*>& _nodeStack ,char _ch);
    void connectRight(stack<T*>& _nodeStack, char _ch);
    void connectLeftRight(stack<T*>& _nodeStack, char _ch);
    void print() const;

private:
    T* m_root;
    T* m_currNode;
    int m_sum;

};



template <typename T>
T* Tree<T>::root() const
{
    return m_root;
}

template <typename T>
T* Tree<T>::inOrderPrint(T* _root)
{
    T* left;
    T* right;
    
    if(0 == _root->m_left && 0 == _root->m_right)
    {
        return _root;
    }

    switch (_root->m_value)
    {

    case '*':
        left = inOrderPrint(_root->m_left);
        right = inOrderPrint(_root->m_right);
        _root->m_value = (left->m_value) * (right->m_value); 
        break;

    case '/':
        left = inOrderPrint(_root->m_left);
        right = inOrderPrint(_root->m_right);
        _root->m_value = (left->m_value) / (right->m_value);   
        break;

    case '-':
        left = inOrderPrint(_root->m_left);
        right = inOrderPrint(_root->m_right);
        _root->m_value = (left->m_value) - (right->m_value); 
        break;

    case '+':
        left = inOrderPrint(_root->m_left);
        right = inOrderPrint(_root->m_right);
        _root->m_value = (left->m_value) + (right->m_value); 
        break;
    
    default:
        break;
    }
   
    return _root;
}

template <typename T>
void Tree<T>::connectLeft(stack<T*>& _nodeStack, char _ch)
{
    T* n1 = 0;
    T* temp = 0; 

    temp = new T(_ch);
    n1 = _nodeStack.top();
    _nodeStack.pop();
    temp->m_left = n1;
    _nodeStack.push(temp);

}
template <typename T>
void Tree<T>::connectRight(stack<T*>& _nodeStack, char _ch)
{
    T* n1 = 0;
    T* n2 = 0;

    n1 = _nodeStack.top();
    _nodeStack.pop();
    n2 = _nodeStack.top();
    _nodeStack.pop();
    n2->m_right = n1;
    _nodeStack.push(n2);

}
template <typename T>
void Tree<T>::connectLeftRight(stack<T*>& _nodeStack, char _ch)
{
    T* n1 = 0;
    T* n2 = 0;
    T* temp = 0; 

    temp = new T(_ch);
    n1 = _nodeStack.top();
    _nodeStack.pop();

    n2 = _nodeStack.top();
    _nodeStack.pop();

    n2->m_right = n1;
    temp->m_left = n2;
    _nodeStack.push(temp);
}

template <typename T>
bool Tree<T>::isOperator(char _ch) const
{
    if (_ch == '+' || _ch == '-' ||_ch == '*' || _ch == '/' || _ch == '^') 
    {
        return true;
    }

    return false; 
}

template <typename T>
bool Tree<T>::isLessOperator(char _lhs, char _rhs) const
{
    if(_lhs == '*' || _lhs == '/')
    {
        return false;
    }

    if( (_lhs == '+' || _lhs == '-') && (_rhs == '*' || _rhs == '/'))
    {
        return true;
    }

    return false;
}

template <typename T>
Tree<T>::Tree()
: m_currNode(m_root)
{

}

template <typename T>
void Tree<T>::buildTree(string const& _expression)
{
    stack<T*> nodeStack;

    string::const_iterator itB = _expression.begin();
    string::const_iterator itE = _expression.end();
 
    char lastOperation = '+';
    int counter = 0;

    while(itB != itE)
    {
        if(*itB == '(')
        {
            ++counter;
            ++itB;
            lastOperation = '+';
            continue;
        }

        if(isOperator(*itB))
        {
            
            if(isLessOperator(*itB, lastOperation) && 0 == counter)
            {
                connectLeftRight(nodeStack, *itB);
            }

            else
            {
                connectLeft(nodeStack, *itB);
            }

            lastOperation = *itB;
        }

        else if(*itB != ')')
        {
            nodeStack.push(new T(*itB - '0'));
        }

        else
        {
            connectRight(nodeStack, *itB);
            --counter;
        }
        
        ++itB;
    }

    while(1 != nodeStack.size())
    {
        connectRight(nodeStack, *itB);
    }

    m_root = nodeStack.top();

}

#endif