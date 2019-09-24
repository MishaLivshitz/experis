#include "Circle.h"

Circle::Circle()
:m_radius(0)
,m_color("White")
{

}

Circle::Circle(double a_radius, std::string _color)
:m_radius(a_radius)
,m_color(_color)
{

}

Circle::Circle(Circle const& a_rhs)
:m_radius(a_rhs.m_radius)
,m_color(a_rhs.m_color)
{

}

Circle& Circle::operator=(Circle const& a_rhs)
{
    m_radius = a_rhs.m_radius;
    m_color = a_rhs.m_color;
    return *this;
}

Circle::~Circle()
{
    std::cout << "Circle distructor" << std::endl;
}