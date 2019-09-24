
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include "Circle.h"
#include "Square.h"


void f(Circle* _c)
{
    if(_c->type() == &Circle::s_TYPE)
    {
        _c->print(std::cout);
    }
    else
    {
        Square* p;
        p = static_cast<Square*>(_c);
        p->print(std::cout);
    }
}

#endif