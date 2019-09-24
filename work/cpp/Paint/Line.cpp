#include "Line.h"

Line::Line()
{
    m_slope = 0;
}

Line::Line(Color const& _c,Point const& _p,Point const& _pEnd)
:Shape(_c, _p)
,m_endPoint(_pEnd)
{
    m_slope = calcSlope();
}

Line::~Line()
{
}

void Line::endPoint(Point const& _p)
{
    m_endPoint = _p;
}

Point const& Line::endPoint()
{
    return m_endPoint;
}

int Line::calcSlope() const
{
    int y1 = m_origin.getY();
    int y2 = m_endPoint.getY();
    int x1 = m_origin.getX();
    int x2 = m_endPoint.getX();

    return (y2-y1)/(x2-x1);
}

void Line::draw(Canvas& _canvas)
{
    int x = m_origin.getX();
    int y = m_origin.getY();
    int slope = calcSlope();
    Point tempPoint;
    int advance = slope < 0 ? -1:1;

    std::cout << slope << std::endl;
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    
    // bug if slope == 0 and more xD
    do{
        tempPoint.setY(y);
        tempPoint.setX(x);
        _canvas.drawPixel(m_color,tempPoint);
        x += advance;
        y += slope;
    }
    while(y*advance!=m_endPoint.getY());
}
double Line::area() const
{
    return 0;
}