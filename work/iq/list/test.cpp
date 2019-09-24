#include "mu_test.h"
#include "node.h"
#include "list.h"

UNIT(node)

    int a = 25;
    Node<int>n(a);

    ASSERT_EQUAL(n.data(),25);

END_UNIT

UNIT(list)

    List<int> lst;
    lst.add(25);
    lst.add(28);
    lst.add(22);
    lst.add(21);
    lst.add(27);
    lst.add(26);
    lst.add(20);

    lst.print();
    ASSERT_EQUAL(lst.remove(20), true);
    ASSERT_EQUAL(lst.remove(20), false);
    ASSERT_EQUAL(lst.remove(35), false);
    lst.add(35);
    ASSERT_EQUAL(lst.remove(35), true);
    ASSERT_EQUAL(lst.remove(25), true);
    
    lst.print();

END_UNIT

TEST_SUITE(list test)

    TEST(node)
    TEST(list)



END_SUITE