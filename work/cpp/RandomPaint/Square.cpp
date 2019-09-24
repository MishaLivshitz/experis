#include "Square.h"

Square::Square(Color _color, Point _p, size_t _side)
:Shape(_color, _p)
, m_horizontal(_color,_p , _side)
, m_horizontalEnd(_color,_p,_side+1)
, m_vertical(_color,_p , _side)
, m_verticalEnd(_color,_p,_side)
{
    Point pH(m_origin.getX(), m_origin.getY()+_side);
    Point pV(m_origin.getX() + _side,m_origin.getY() );
    m_horizontalEnd.setPoint(pH);
    m_verticalEnd.setPoint(pV);
}

Square::~Square()
{
}

double Square::area() const
{
    return m_vertical.len() * m_horizontal.len();
} 

size_t Square::side() const
{
    return m_vertical.len();
}

void Square::side(size_t a_side)
{
    m_vertical.len(a_side);
    m_verticalEnd.len(a_side);
    m_horizontal.len(a_side);
    m_horizontalEnd.len(a_side+1);
}

void Square::draw(Canvas& _canvas) const
{
    m_horizontal.draw(_canvas);
    m_vertical.draw(_canvas);
    m_horizontalEnd.draw(_canvas);
    m_verticalEnd.draw(_canvas); 
}

void Square::Move(Point const& _diraction)
{
    m_horizontal.Move(_diraction);
    m_vertical.Move(_diraction);
    m_horizontalEnd.Move(_diraction);
    m_verticalEnd.Move(_diraction);
}