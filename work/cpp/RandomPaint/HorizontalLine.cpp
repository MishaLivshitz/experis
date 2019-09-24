#include "HorizontalLine.h"


HorizontalLine::HorizontalLine(Color const& _c,Point const& _p, int _len)
:Line(_c, _p, Point(_p.getX()+_len ,_p.getY()))
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