#include "Square.h"



//static initialization
const char Square::s_TYPE = 't';

Square::Square()
:Base()
{
    m_type = &s_TYPE;
}

Square::Square(double a_radius)
:Base(a_radius)
{
  m_type = &s_TYPE;
}

Square::Square(Square const& a_rhs)
:Base(a_rhs.m_radius)
{
    m_type = &s_TYPE;
}

Square& Square::operator=(Square const& a_rhs)
{
    m_radius = a_rhs.m_radius;
    return *this;
}

Square::~Square()
{
    m_type = &Base::s_TYPE;
}

double Square::area() const
{
    return 4*pow(m_radius,2);
}