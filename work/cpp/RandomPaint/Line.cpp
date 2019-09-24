#include "Line.h"
#include "algorithm"
#include "utility"

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

    return x2-x1 ? (y2-y1)/(x2-x1): -1;
}

void Line::preparePoints(int& x0,int& x1, int& y0, int& y1) const
{
    x0 = m_origin.getX();
    x1 = m_endPoint.getX();
    
    if(x0>x1)
    {
        x1 = x0;
        x0 = m_endPoint.getX();

        y0 = m_endPoint.getY();
        y1 = m_origin.getY();
    }
    else
    {
        y0 = m_origin.getY();
        y1 = m_endPoint.getY();
    }
    
}

void Line::draw(Canvas& _canvas) const
{
    int x0;
    int x1;
    int y0;
    int y1;

    preparePoints(x0,x1,y0,y1);
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    int diff = 2*dy - dx;
    int advancement = 1;

    if(diff < 0)
    {
        advancement = -1;
        dy = -dy;
    }
    
    Point tempPoint;
   
    while(x0<x1)
    {
        tempPoint.setY(y0);
        tempPoint.setX(x0);
        _canvas.drawPixel(m_color,tempPoint);
        if(diff > 0)
        {
            y0 += advancement;
            diff -= 2*dx;
        }
        diff += 2*dy;
        ++x0;
    }
}

void Line::Move(Point const& _diraction)
{
    m_origin += _diraction;
    m_endPoint += _diraction;
}

double Line::area() const
{
    return 0;
}