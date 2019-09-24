#include "Shape.h"

Shape::Shape()
{
    
}

Shape::Shape(Color const& _color, Point const& _p, bool _isMoveable)
:m_origin(_p)
,m_color(_color)
{ 
}

Shape::~Shape()
{}

Point const& Shape::getPoint() const
{
    return m_origin;
}

Color const& Shape::getColor() const
{
    return m_color;
}

void Shape::setColor(Color const& _color)
{
    m_color = _color;
}

void Shape::setPoint(Point const& _p)
{
    m_origin = _p;
}