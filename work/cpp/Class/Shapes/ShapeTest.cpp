#include "mu_test.h"
#include "Shape.h"
#include "Circle.h"
#include "Square.h"
#include <vector>

UNIT(create)

    std::vector<Shape*> vec;
    Point p(6,9);

    Circle c(p,5);
    Square s(p,5);

    vec.push_back(&c);
    vec.push_back(&s);

    std::cout << vec[0]->area() << std::endl;
    std::cout << vec[1]->area() << std::endl;
    

    

END_UNIT


TEST_SUITE(Shapes Test)

    TEST(create)

END_SUITE