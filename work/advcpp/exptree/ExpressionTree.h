#ifndef EXP_TREE_H
#define EXP_TREE_H

#include "NodeFactory.h"
#include "BaseNode.h"
#include "Tokenizer.h"
#include <stack>



template <typename T> 
class ExpressionTree
{
public:    
    enum TraverseMode {PRE_ORDER, IN_ORDER, POST_ORDER};

public:

    ~ExpressionTree();
    void buildExpTree(std::string const& _exp);
    BaseNode<T> const* root() const;


private:
    void mergeNodes(std::string const& _op, std::stack<BaseNode<T>*>& _eStack) const;
    void createNewNode(std::string const& _op, std::stack<BaseNode<T>*>& _eStack) const;

private:
    BaseNode<T>* m_root;
};

template <typename T> 
BaseNode<T> const* ExpressionTree<T>::root() const
{
    return m_root;
}

template <typename T> 
ExpressionTree<T>::~ExpressionTree()
{
    delete this->m_root;
}


template <typename T> 
void ExpressionTree<T>::mergeNodes(std::string const& _op, std::stack<BaseNode<T>*>& _eStack) const
{
    BaseNode<T>* right = 0;
    BaseNode<T>* left = 0;

    right = _eStack.top();
    _eStack.pop();

    left = _eStack.top();
    _eStack.pop();

    _eStack.push(NodeFactory<T>::createBinNode(_op.c_str()[0],left,right));
}

template <typename T> 
void ExpressionTree<T>::createNewNode(std::string const& _op, std::stack<BaseNode<T>*>& _eStack) const
{
    T val;
    std::stringstream numStream(_op);
    numStream >> val;
    _eStack.push(NodeFactory<T>::createValNode(val));
}

template <typename T> 
void ExpressionTree<T>::buildExpTree(std::string const& _exp)
{
    std::vector<Token> tokens;
    Tokenizer::getTokens(_exp, tokens);
    std::stack<BaseNode<T>*> expStack;
    size_t const size = tokens.size();
    
    for(size_t i = 0; i < size; ++i)
    {
        if(tokens[i].isOp())
        {
            mergeNodes(tokens[i].token(), expStack);
        }
        else
        {
            createNewNode(tokens[i].token(), expStack);
        }
    }

    m_root = expStack.top();

}

#endif