#include "VerticalLine.h"


VerticalLine::VerticalLine()
{

}

VerticalLine::VerticalLine(Color const& _c, int _x, int _y , int _len)
:Shape(_c,_x,_y)
,m_len(_len)
{

}

VerticalLine::VerticalLine(Color const& _c, Point const& _p, int _len)
:Shape(_c, _p)
,m_len(_len)
{

}

VerticalLine::~VerticalLine()
{
}

int VerticalLine::len() const
{
    return m_len;
}

void VerticalLine::len(int _len)
{
    m_len = _len;
}

void VerticalLine::draw(Canvas& _canvas) const
{
    int x = m_origin.getX();
    int y = m_origin.getY();
    Point tempPoint;
    tempPoint.setX(x);
    for(int i = 0 ; i < m_len ;i++)
    {   
        tempPoint.setY(y+i);
        _canvas.drawPixel(m_color,tempPoint);
    }
}
double VerticalLine::area() const
{
    return 0;
}