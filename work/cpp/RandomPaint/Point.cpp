
#include "Point.h"

Point::Point(int _x,int _y)
:m_x(_x)
,m_y(_y)
{
    
}

void Point::operator+=(Point const& _p)
{
    m_x += _p.m_x;
    m_y += _p.m_y;
}

int Point::getX() const
{
    return m_x;
}

int Point::getY() const
{
    return m_y;
}

void Point::setX(int _x)
{
    m_x = _x;
}

void Point::setY(int _y)
{
    m_y = _y;
}