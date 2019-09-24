
#ifndef SQUARE_H
#define SQUARE_H

#include "Circle.h"

class Square: public Circle
{

typedef Circle Base;
public:
    
    Square(double a_radius = 0, std::string _color = "white");
    Square& operator=(Square const& a_rhs);
    virtual ~Square();

    virtual double area() const;
    virtual std::string const header() const;

};

inline double Square::area() const
{
    return 4*pow(m_radius,2);
}

inline std::string const Square::header() const
{
    return "Square";
}

#endif