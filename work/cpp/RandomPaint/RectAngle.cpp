#include "RectAngle.h"

RectAngle::RectAngle(Color const& _color, Point const& _p, int _width, int _height)
: Shape(_color,_p)
, m_horizontal(_color,_p , _width)
, m_horizontalEnd(_color,_p,_width+1)
, m_vertical(_color,_p , _height)
, m_verticalEnd(_color,_p,_height)
{
    Point pH(m_origin.getX(), m_origin.getY()+_height);
    Point pV(m_origin.getX() + _width ,m_origin.getY() );
    m_horizontalEnd.setPoint(pH);
    m_verticalEnd.setPoint(pV);
} 

RectAngle::~RectAngle()
{
}

void RectAngle::draw(Canvas& _canvas) const
{
    m_horizontal.draw(_canvas);
    m_vertical.draw(_canvas);
    m_horizontalEnd.draw(_canvas);
    m_verticalEnd.draw(_canvas); 
}

void RectAngle::Move(Point const& _diraction)
{
    m_horizontal.Move(_diraction);
    m_vertical.Move(_diraction);
    m_horizontalEnd.Move(_diraction);
    m_verticalEnd.Move(_diraction);
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
    m_horizontalEnd.len(a_width+1);
}

void RectAngle::height(int a_height)
{
    m_vertical.len(a_height);
    m_verticalEnd.len(a_height);
}

int RectAngle::height() const
{
    return m_horizontal.len();
}

const bool RectAngle::s_MOVEABLE = true;