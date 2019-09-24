#ifndef BASE_NODE_H
#define BASE_NODE_H

#include "iostream"

template<typename T>
    class BaseAction;

template<typename V>
class BaseNode{


public:

    virtual ~BaseNode() {};
    virtual V visit(BaseAction<V> const* _action) const = 0;
    
};

#endif