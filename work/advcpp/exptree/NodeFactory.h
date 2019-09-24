#ifndef NODE_FACTORY_H
#define NODE_FACTORY_H

#include "map"
#include "BinOpNode.h"
#include "ValueNode.h"
#include "MulOp.h"
#include "DivOp.h"
#include "SubOp.h"
#include "AddOp.h"


template<typename T>
class NodeFactory
{

public:

    static BinOpNode<T>* createBinNode(char _op, BaseNode<T>* _lhs, BaseNode<T>* _rhs);
    static ValueNode<T>* createValNode(T const& _val);

private:

    NodeFactory();
    typedef BinOpNode<T>* (*OpCreate)(BaseNode<T>*, BaseNode<T>*);
    typedef std::map<char, OpCreate> staticMap;
    static const staticMap s_MAP;

private:
    static staticMap initMap();
    static BinOpNode<T>* createMulNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs);
    static BinOpNode<T>* createAddNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs);
    static BinOpNode<T>* createSubNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs);
    static BinOpNode<T>* createDivNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs);

};

template<typename T>
const typename NodeFactory<T>::staticMap NodeFactory<T>::s_MAP = NodeFactory<T>::initMap();


template<typename T>
BinOpNode<T>* NodeFactory<T>::createBinNode(char _op, BaseNode<T>* _lhs, BaseNode<T>* _rhs)
{
    typename staticMap::const_iterator itr = NodeFactory<T>::s_MAP.find(_op);

    if(itr != NodeFactory<T>::s_MAP.end())
    {
        return itr->second(_lhs, _rhs);
    }

    return 0;
}

template<typename T>
ValueNode<T>* NodeFactory<T>::createValNode(T const& _val)
{
    return new ValueNode<T>(_val);
}

template<typename T>
std::map<char, typename NodeFactory<T>::OpCreate> NodeFactory<T>::initMap()
{
    std::map<char, typename NodeFactory<T>::OpCreate> map;
    map['*'] = &NodeFactory<T>::createMulNode;
    map['/'] = &NodeFactory<T>::createDivNode;
    map['-'] = &NodeFactory<T>::createSubNode;
    map['+'] = &NodeFactory<T>::createAddNode;

    return map;
}


template<typename T>
BinOpNode<T>* NodeFactory<T>::createMulNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs)
{
    return new MulOp<T>(_lhs,_rhs);
}

template<typename T>
BinOpNode<T>* NodeFactory<T>::createAddNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs)
{
    return new AddOp<T>(_lhs,_rhs);
}

template<typename T>
BinOpNode<T>* NodeFactory<T>::createSubNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs)
{
    return new SubOp<T>(_lhs,_rhs);
}

template<typename T>
BinOpNode<T>* NodeFactory<T>::createDivNode(BaseNode<T>* _lhs, BaseNode<T>* _rhs)
{
    return new DivOp<T>(_lhs,_rhs);
}

#endif