#ifndef IN_ORDER_VISIT
#define IN_ORDER_VISIT

#include "BaseVisitMode.h"

template<typename T>
class InOrderVisit: public BaseVisitMode<T>
{
public:

    virtual ~InOrderVisit() {};
    virtual T ActivateTraverse(BinOpNode<T> const* _node, BaseAction<T> const* _action, BaseFunctor<T>* _func) const;
};

template<typename T>
T InOrderVisit<T>::ActivateTraverse(BinOpNode<T>const* _node, BaseAction<T> const* _action, BaseFunctor<T>* _func) const
{
    _node->left()->visit(_action);
    T val =(*_func)();
    _node->right()->visit(_action);

    return val;
}

#endif