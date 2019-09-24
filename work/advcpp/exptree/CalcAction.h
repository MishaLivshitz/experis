#ifndef CALC_ACTION_H
#define CALC_ACTION_H

#include "BaseAction.h"

template <typename T>
class CalcAction: public BaseAction<T>
{
public:
    CalcAction(typename ExpressionTree<T>::TraverseMode _mode);
    virtual ~CalcAction() {};
    virtual void action(BaseNode<T> const* _node) const;
    virtual void action(BinOpNode<T> const* _node) const;

    virtual T action(ValueNode<T> const* _node) const;
    virtual T action(MulOp<T> const* _node) const;
    virtual T action(AddOp<T> const* _node) const;
    virtual T action(SubOp<T> const* _node) const;
    virtual T action(DivOp<T> const* _node) const;

};

template <typename T>
CalcAction<T>::CalcAction( typename ExpressionTree<T>::TraverseMode _mode)
:BaseAction<T>(_mode)
{

}

template <typename T>
void CalcAction<T>::action(BinOpNode<T> const* _node) const
{

}

template <typename T>
void CalcAction<T>::action(BaseNode<T> const* _node) const
{

}

template <typename T>
T CalcAction<T>::action(ValueNode<T>const* _node) const
{
    return _node->val();
}

template <typename T>
T CalcAction<T>::action(MulOp<T>const* _node) const
{
    return _node->left()->visit(this) * _node->right()->visit(this);
}

template <typename T>
T CalcAction<T>::action(AddOp<T>const* _node) const
{
    return _node->left()->visit(this) + _node->right()->visit(this);
}

template <typename T>
T CalcAction<T>::action(SubOp<T>const* _node) const
{
    return _node->left()->visit(this) - _node->right()->visit(this);
}

template <typename T>
T CalcAction<T>::action(DivOp<T>const* _node) const
{
    T rightVal = _node->right()->visit(this);

    if(rightVal !=0)
    {
        return _node->left()->visit(this) / rightVal;
    }

    return 0;
}

#endif