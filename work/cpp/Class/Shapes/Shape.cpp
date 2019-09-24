#include "Shape.h"

Shape::Shape(int _x, int _y)
:m_origin(_x,_y)
{
}

Shape::Shape(Point const& _p)
:m_origin(_p)
{ 
}

Shape::~Shape()
{}

Point const& Shape::getPoint() const
{
    return m_origin;
}