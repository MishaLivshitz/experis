#include "Circle.h"


Circle::Circle(int _x, int _y, size_t _radius)
:Shape(_x,_y)
,m_radius(_radius)
{

}


Circle::Circle(Point _p, size_t _radius)
:Shape(_p)
,m_radius(_radius)
{

}

Circle::~Circle()
{
}

double Circle::area() const
{
    return M_PI*pow(m_radius,2);
}

size_t Circle::radius() const
{
    return m_radius;
}

void Circle::radius(int a_radius)
{
    m_radius = a_radius;
}