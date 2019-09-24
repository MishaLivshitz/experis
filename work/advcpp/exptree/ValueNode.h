#ifndef VALUE_NODE_H
#define VALUE_NODE_H

#include "BaseNode.h"

template <typename V>
class ValueNode: public BaseNode<V>
{

public:

    ValueNode(V const& _val);
    virtual ~ValueNode() {};
    virtual V visit(BaseAction<V> const* _action) const;
    V val() const;

private:
    V m_val;
};

template <typename V>
ValueNode<V>::ValueNode(V const& _val)
:m_val(_val)
{
}

template <typename V>
V ValueNode<V>::visit(BaseAction<V> const* _action) const
{
    return _action->action(this);
}

template <typename V>
V ValueNode<V>::val() const
{
    return m_val;
}

#endif