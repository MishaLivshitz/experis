#ifndef CIRCLE_H
#define CIRCLE_H


#define _USE_MATH_DEFINES
 
#include <cmath>
#include <iostream>

class Circle
{

public:

    Circle();
    Circle(double a_radius = 0, std::string _color = "white");
    Circle(Circle const& a_rhs);
    Circle& operator=(Circle const& a_rhs);

    virtual ~Circle();
    virtual double area() const;
    virtual std::string const header() const;

    double color(std::string const& _color) const;
    void print(std::ostream& _os) const;

protected:
    double m_radius;
    std::string m_color;
   
};

inline double Circle::area() const
{
    return M_PI*pow(m_radius,2);
}

inline void Circle::print(std::ostream& a_os) const
{
    a_os << header() << std::endl;
    a_os << "        radius = " << m_radius << std::endl;
    a_os << "        area = " << area() << std::endl;
    a_os << "        color: " << m_color << std::endl;

}

inline std::string const Circle::header() const
{
    return "Circle";
}

#endif