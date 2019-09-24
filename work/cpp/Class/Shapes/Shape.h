#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include "Point.h"

class Shape
{
public:
    Shape(int _x = 0 , int _y = 0);
    Shape(Point const& _p);

    virtual ~Shape();
    virtual double area() const = 0;

    Point const& getPoint() const;

private:
   Point m_origin;
};

#endif