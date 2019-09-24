#ifndef BASE_ACTION_H
#define BASE_ACTION_H

#include "BinOpNode.h"
#include "ValueNode.h"
#include "MulOp.h"
#include "AddOp.h"
#include "SubOp.h"
#include "DivOp.h"

template<typename T>
class ExpressionTree;

template<typename T>
class BaseAction
{
public:
    BaseAction( typename ExpressionTree<T>::TraverseMode _mode);
    virtual ~BaseAction() {};
    virtual void action(BaseNode<T> const* _node) const = 0;
    virtual void action(BinOpNode<T> const* _node) const = 0;

    virtual T action(ValueNode<T> const* _node) const {return 0;};
    virtual T action(MulOp<T> const* _node) const {return 0;};
    virtual T action(AddOp<T> const* _node) const {return 0;};
    virtual T action(DivOp<T> const* _node) const {return 0;};
    virtual T action(SubOp<T> const* _node) const {return 0;};

protected:
    typename ExpressionTree<T>::TraverseMode m_mode;


};

template<typename T>
BaseAction<T>::BaseAction(typename ExpressionTree<T>::TraverseMode _mode)
: m_mode(_mode) 
{

}

#endif