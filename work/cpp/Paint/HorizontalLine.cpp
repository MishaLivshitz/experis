#include "HorizontalLine.h"


HorizontalLine::HorizontalLine()
{

}

HorizontalLine::HorizontalLine(Color const& _c, int _x, int _y , int _len)
:Shape(_c,_x,_y)
,m_len(_len)
{

}

HorizontalLine::HorizontalLine(Color const& _c,Point const& _p, int _len)
:Shape(_c, _p)
,m_len(_len)
{

}

HorizontalLine::~HorizontalLine()
{
}

int HorizontalLine::len() const
{
    return m_len;
}

void HorizontalLine::len(int _len)
{
    m_len = _len;
}

void HorizontalLine::draw(Canvas& _canvas) const
{
    int x = m_origin.getX();
    int y = m_origin.getY();
    Point tempPoint;
    tempPoint.setY(y);
    for(int i = 0 ; i < m_len ;i++)
    {   
        tempPoint.setX(x+i);
        _canvas.drawPixel(m_color,tempPoint);
    }
}
double HorizontalLine::area() const
{
    return 0;
}