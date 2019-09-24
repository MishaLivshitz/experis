#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "Point.h"

class Moveable
{

public:
    virtual void Move(Point const& _p) = 0;
    virtual ~Moveable() {};
};

#endif