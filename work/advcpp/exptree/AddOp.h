#ifndef ADD_OP_H
#define ADD_OP_H

#include "BinOpNode.h"

template<typename V>
class AddOp: public BinOpNode<V>
{
public:

    AddOp(BaseNode<V>* _left, BaseNode<V>* _right);
    virtual V visit(BaseAction<V> const* _action) const;
   
};

template<typename V>
AddOp<V>::AddOp(BaseNode<V>* _left, BaseNode<V>* _right)
: BinOpNode<V>(_left, _right)
{

}

template<typename V>
V AddOp<V>::visit(BaseAction<V> const* _action) const
{
    return _action->action(this);
}

#endif