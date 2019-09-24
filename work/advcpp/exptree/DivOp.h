#ifndef DIV_OP_H
#define DIV_OP_H

#include "BinOpNode.h"

template<typename V>
class DivOp: public BinOpNode<V>
{
public:

    DivOp(BaseNode<V>* _left, BaseNode<V>* _right);
    virtual V visit(BaseAction<V> const* _action) const;
};

template<typename V>
DivOp<V>::DivOp(BaseNode<V>* _left, BaseNode<V>* _right)
:BinOpNode<V>(_left, _right)
{

}

template<typename V>
V DivOp<V>::visit(BaseAction<V> const* _action) const
{
    return _action->action(this);
}

#endif