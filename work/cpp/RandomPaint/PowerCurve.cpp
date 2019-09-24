#include "PowerCurve.h"

PowerCurve::PowerCurve(Color const& _c, Point const& _begin, Point const& _end ,Point const& _control)
: ParametricCurve(_c,_begin,_end,_control)
{

}

void PowerCurve::cureveFunc(double direction, Point& _nextPoint) const
{
    int x = (1 - direction) *
            (1 - direction) * m_origin.getX() + 2 *
            (1 - direction) * direction *
            m_endPoint.getX() + direction * direction *
            m_controlP.getX();

    int y = (1 - direction) *
            (1 - direction) * m_origin.getY() + 2 *
            (1 - direction) * direction *
            m_endPoint.getY() + direction * direction *
            m_controlP.getY();

    _nextPoint.setX(x);
    _nextPoint.setY(y);

}

void PowerCurve::draw(Canvas& _canvas) const
{
    Point nextPoint;
  
    for(double i = 0; i<1 ;i += m_advancement)
    {
        cureveFunc(i,nextPoint);
        _canvas.drawPixel(m_color,nextPoint);
    }
}