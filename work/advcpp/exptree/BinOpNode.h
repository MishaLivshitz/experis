#ifndef BIN_OP_NODE_H
#define BIN_OP_NODE_H

#include "BaseNode.h"

template<typename V>
class BinOpNode: public BaseNode<V>
{
public:

    virtual ~BinOpNode();
    BinOpNode(BaseNode<V>* _left, BaseNode<V>* _right);
    BinOpNode(BinOpNode const& _rhs);
    BinOpNode& operator=(BinOpNode const& _rhs);

    BaseNode<V>* left() const;
    BaseNode<V>* right() const;

protected:
       
    BaseNode<V>* m_left;
    BaseNode<V>* m_right;

};

template<typename V>
BinOpNode<V>::BinOpNode(BinOpNode<V> const& _rhs)
{
    this->m_left = _rhs->m_left;
    this->m_right = _rhs->m_right;
}

template<typename V>
BinOpNode<V>& BinOpNode<V>::operator=(BinOpNode<V> const& _rhs)
{
    this->m_left = _rhs->m_left;
    this->m_right = _rhs->m_right;

    return *this;
}

template<typename V>
BaseNode<V>* BinOpNode<V>::left() const
{
    return m_left;
}

template<typename V>
BaseNode<V>* BinOpNode<V>::right() const
{
    return m_right;
}

template<typename V>
BinOpNode<V>::BinOpNode(BaseNode<V>* _left, BaseNode<V>* _right)
:m_left(_left)
,m_right(_right)
{
    
}

template<typename V>
BinOpNode<V>::~BinOpNode()
{
    delete m_left;
    delete m_right;
}

#endif


