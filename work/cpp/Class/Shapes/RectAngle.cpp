#include "RectAngle.h"


RectAngle::RectAngle(int _x , int _y, size_t _width, size_t _length)
:Shape(_x,_y)
,m_width(_width)
,m_length(_length)
{
}

RectAngle::RectAngle(Point _p, size_t _width, size_t _length)
:Shape(_p)
,m_width(_width)
,m_length(_length)
{

}

RectAngle::~RectAngle()
{
}
double RectAngle::area() const
{
    return m_length*m_width;
}

size_t RectAngle::width() const
{
    return m_width;
}

void RectAngle::width(size_t a_width)
{
    m_width = a_width;
}

void RectAngle::length(size_t a_length)
{
    m_length = a_length;
}

size_t RectAngle::length() const
{
    return m_length;
}