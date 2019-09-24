#include "mu_test.h"

#include "BaseNode.h"
#include "BinOpNode.h"
#include "ValueNode.h"
#include "AddOp.h"
#include "MulOp.h"
#include "SubOp.h"
#include "DivOp.h"
#include <sstream>
#include "Token.h"
#include "Tokenizer.h"
#include <string>
#include "NodeFactory.h"
#include "ExpressionTree.h"
#include "CalcAction.h"
#include "PrintAction.h"


UNIT(visitor_test)

    ExpressionTree<int> eTree;

    eTree.buildExpTree("5 1 2 + 4 * + 3 -");

    CalcAction<int> act(ExpressionTree<int>::IN_ORDER);

    ASSERT_EQUAL_INT(eTree.root()->visit(&act), 14);

END_UNIT

UNIT(visitor_print_test)

    ExpressionTree<int> eTree;

    eTree.buildExpTree("42 3 - 124 12 - 3 2 * / *");

    std::stringstream expStr;

    PrintAction<int> act(ExpressionTree<int>::IN_ORDER, expStr);

    eTree.root()->visit(&act);

    ASSERT_EQUAL(expStr.str(), "( ( 42 - 3 ) * ( ( 124 - 12 ) / ( 3 * 2 ) ) ) ");

END_UNIT



TEST_SUITE(Expression tree test)

    TEST(visitor_test)
    TEST(visitor_print_test)

END_SUITE