#include "Tree.h"
#include <string>

using std::string;


int main()
{
    Tree<Node<int> > t;
   
    t.buildTree("3+(2*(1+1))");
    std::cout << t.inOrderPrint(t.root())->m_value << std::endl;

}