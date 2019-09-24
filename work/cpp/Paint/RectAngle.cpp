#include "RectAngle.h"


RectAngle:: RectAngle(Color const& _color, int _x ,int _y, int _width, int _height)
: Shape(_color,_x,_y)
, m_horizontal(_color,_x,_y,_width)
, m_horizontalEnd(_color,_x,_y,_width+1)
, m_vertical(_color,_x,_y,_height)
, m_verticalEnd(_color, _x, _y, _height)
{
   setLinesPoint(_width, _height);
}

RectAngle::RectAngle(Color const& _color, Point const& _p, int _width, int _height)
: Shape(_color,_p)
, m_horizontal(_color,_p , _width)
, m_horizontalEnd(_color,_p,_width+1)
, m_vertical(_color,_p , _height)
, m_verticalEnd(_color,_p,_height)
{
    setLinesPoint(_width, _height);
} 

RectAngle::~RectAngle()
{
}

void RectAngle::setLinesPoint(int _width,int _height)
{
    Point tempPoint(m_origin.getX(),m_origin.getY()+_height);
    m_horizontalEnd.setPoint(tempPoint);
    tempPoint.setX(m_origin.getX()+_width);
    tempPoint.setY(m_origin.getY());
    m_verticalEnd.setPoint(tempPoint);
}

void RectAngle::draw(Canvas& _canvas) const
{
    m_horizontal.draw(_canvas);
    m_vertical.draw(_canvas);
    m_horizontalEnd.draw(_canvas);
    m_verticalEnd.draw(_canvas); 
}

double RectAngle::area() const
{
    return m_horizontal.len() * m_vertical.len();
}

int RectAngle::width() const
{
    return m_horizontal.len();
}

void RectAngle::width(int a_width)
{
    m_horizontal.len(a_width);
    m_horizontalEnd.len(a_width);
}

void RectAngle::length(int a_height)
{
    m_horizontal.len(a_height);
    m_horizontalEnd.len(a_height);
}

int RectAngle::length() const
{
    return m_horizontal.len();
}
