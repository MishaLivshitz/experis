#ifndef BASE_VISIT_MODE_H
#define BASE_VISIT_MODE_H

#include "BinOpNode.h"
#include "ExpressionTree.h"
#include "BaseAction.h"
#include "BaseFunctor.h"

template <typename T>
class BaseVisitMode
{
public:

    virtual ~BaseVisitMode() {};
    virtual T ActivateTraverse(BinOpNode<T> const* _node, BaseAction<T> const* _action, BaseFunctor<T>* _func) const = 0;

};

#endif