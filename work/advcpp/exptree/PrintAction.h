#ifndef PRINT_ACTION_H
#define PRINT_ACTION_H

#include "BaseAction.h"
#include "InOrderTraverse.h"
#include "BaseFunctor.h"

template<typename T>
class PrintAction: public BaseAction<T>
{
public:
    PrintAction(typename ExpressionTree<T>::TraverseMode _mode, std::ostream& _os = std::cout);
    virtual ~PrintAction() {};

    virtual void action(BaseNode<T> const* _node) const {};
    virtual void action(BinOpNode<T> const* _node) const {};

    virtual T action(ValueNode<T> const* _node) const ;
    virtual T action(MulOp<T> const* _node) const;
    virtual T action(AddOp<T> const* _node) const;
    virtual T action(DivOp<T> const* _node) const;
    virtual T action(SubOp<T> const* _node) const;

    std::ostream& getStream() const;

    class printFunc: public BaseFunctor<T>
    {
    public:
        printFunc(char _ch, std::ostream& _os);
        virtual ~printFunc() {};
        virtual T operator()() const;

        char m_char;
        std::ostream& m_os;
    };

private:
    void generalPrint(BinOpNode<T> const* , char _ch) const;

private:
    std::ostream& m_os;

};

template<typename T>
std::ostream& PrintAction<T>::getStream() const
{
    return m_os;
}

template<typename T>
PrintAction<T>::PrintAction(typename ExpressionTree<T>::TraverseMode _mode ,std::ostream& _os)
: BaseAction<T>(_mode)
, m_os(_os)
{

}

template<typename T>
void PrintAction<T>::generalPrint(BinOpNode<T> const* _node, char _ch) const
{
    InOrderVisit<T> inOrder;
    printFunc pF(_ch, m_os);
    switch (BaseAction<T>::m_mode)
    {
    case ExpressionTree<T>::IN_ORDER:
       /*  m_os << "( ";
        _node->left()->visit(this);
        m_os << _ch << ' ';
        _node->right()->visit(this);
        m_os << ") "; */
        m_os << "( ";
        inOrder.ActivateTraverse(_node, this, &pF);
        m_os << ") ";
        break;

    case ExpressionTree<T>::PRE_ORDER:
        m_os << _ch << ' ';
        m_os << _node->left()->visit(this);
        m_os << _node->right()->visit(this);

        break;

    case ExpressionTree<T>::POST_ORDER:
        _node->left()->visit(this);
        _node->right()->visit(this);
        m_os << _ch << ' ';

        break;
    
    default:
        break;
    }

}

template<typename T>
T PrintAction<T>::action(ValueNode<T> const* _node) const
{
    m_os <<_node->val() << ' ';
    return 0;
}

template<typename T>
T PrintAction<T>::action(MulOp<T> const* _node) const
{
    generalPrint(_node, '*');

    return 0;
}


template<typename T>
T PrintAction<T>::action(AddOp<T> const* _node) const
{
    generalPrint(_node, '+');
    return 0;
}

template<typename T>
T PrintAction<T>::action(DivOp<T> const* _node) const
{
    generalPrint(_node, '/');
    return 0;
}

template<typename T>
T PrintAction<T>::action(SubOp<T> const* _node) const
{
    generalPrint(_node, '-');
    return 0;
}

template<typename T>
T PrintAction<T>::printFunc::operator()() const
{
   m_os << this->m_char << ' ';
   return 0;
}

template<typename T>
PrintAction<T>::printFunc::printFunc(char _ch, std::ostream& _os)
: m_char(_ch)
, m_os(_os)
{

}


#endif