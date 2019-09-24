#include "Circle.h"

//static initialization
const char Circle::s_TYPE = 't';

Circle::Circle()
:m_radius(0)
,m_type(&s_TYPE)
{

}

Circle::Circle(double a_radius)
:m_radius(a_radius)
,m_type(&s_TYPE)
{
  
}

Circle::Circle(Circle const& a_rhs)
:m_radius(a_rhs.m_radius)
,m_type(&s_TYPE)
{

}

Circle& Circle::operator=(Circle const& a_rhs)
{
    m_radius = a_rhs.m_radius;
    return *this;
}

Circle::~Circle()
{

}