#ifndef SUB_OP_H
#define SUB_OP_H

#include "BinOpNode.h"

template<typename V>
class SubOp: public BinOpNode<V>
{
public:

    SubOp(BaseNode<V>* _left, BaseNode<V>* _right);
    virtual V visit(BaseAction<V> const* _action) const;
    
};

template<typename V>
SubOp<V>::SubOp(BaseNode<V>* _left, BaseNode<V>* _right)
:BinOpNode<V>(_left, _right)
{

}

template<typename V>
V SubOp<V>::visit(BaseAction<V> const* _action) const
{
    return _action->action(this);
}

#endif