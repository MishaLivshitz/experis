#include "mu_test.h"
#include "Circle.h"
#include "Square.h"
#include "common.h"


UNIT(construct)

    Circle c(3);
    Square s(3);

END_UNIT

UNIT(f_test)

    Circle* c = new Square(3, "green");
    Circle* c1 = new Circle(3);

    f(c);
    f(c1);

END_UNIT

TEST_SUITE(Circle Square test)

    TEST(construct)
    TEST(f_test)

END_SUITE