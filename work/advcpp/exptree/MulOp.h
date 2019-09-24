#ifndef MUL_OP_H
#define MUL_OP_H

#include "BinOpNode.h"


template<typename V>
class MulOp: public BinOpNode<V>
{

public:

    MulOp(BaseNode<V>* _left, BaseNode<V>* _right);
    virtual V visit(BaseAction<V> const* _action) const;

};

template<typename V>
MulOp<V>::MulOp(BaseNode<V>* _left, BaseNode<V>* _right)
:BinOpNode<V>(_left, _right)
{

}


template<typename V>
V MulOp<V>::visit(BaseAction<V> const* _action) const
{
    return _action->action(this);
}

#endif