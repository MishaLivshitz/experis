#ifndef CIRCLE_H
#define CIRCLE_H


#define _USE_MATH_DEFINES
 
#include <cmath>
#include <iostream>

class Circle
{

public:

    Circle();
    Circle(double a_radius);
    Circle(Circle const& a_rhs);
    Circle& operator=(Circle const& a_rhs);
    ~Circle();

    double area() const;
    void print(std::ostream& _os) const;
    const char* type() const;    

protected:
    double m_radius;
    const char* m_type;

public:
   static const char s_TYPE;
   
};

inline double Circle::area() const
{
    return M_PI*pow(m_radius,2);
}

inline const char* Circle::type() const
{
    return m_type;
}

inline void Circle::print(std::ostream& a_os) const
{
    a_os << "Circle:" << std::endl;
    a_os << "        radius = " << m_radius << std::endl;
    a_os << "        area = " << area() << std::endl;

}

inline std::ostream& operator<< (std::ostream& _os, Circle const& a_circle)
{
    a_circle.print(_os);
    return _os;
}

#endif