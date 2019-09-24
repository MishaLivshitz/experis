#include "Square.h"


Square::Square(int _x, int _y, size_t _side)
:RectAngle(_x,_y,_side,_side)
{

}

Square::Square(Point _p, size_t _side)
:RectAngle(_p,_side,_side)
{

}

Square::~Square()
{
}

double Square::area() const
{
    return RectAngle::area();
} 

size_t Square::side() const
{
    return m_width;
}

void Square::side(size_t a_side)
{
    m_width = a_side;
    m_length = a_side;
}