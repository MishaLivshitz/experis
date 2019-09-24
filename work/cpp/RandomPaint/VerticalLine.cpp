#include "VerticalLine.h"

VerticalLine::VerticalLine(Color const& _c, Point const& _p, int _len)
:Line(_c, _p, Point(_p.getX(),_p.getY()+ _len))
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