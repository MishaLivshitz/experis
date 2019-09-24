
#ifndef SQUARE_H
#define SQUARE_H

#include "Circle.h"

class Square: public Circle
{

typedef Circle Base;
public:
    Square();
    Square(double a_radius);
    Square(Square const& a_rhs);
    Square& operator=(Square const& a_rhs);
    ~Square();

    void print(std::ostream& _os) const;
    double area() const;

public:
   static const char s_TYPE;

};


inline void Square::print(std::ostream& a_os) const
{
    a_os << "Square:" << std::endl;
    a_os << "        radius = " << m_radius << std::endl;
    a_os << "        area = " << area() << std::endl;

}

inline std::ostream& operator<< (std::ostream& _os, Square const& a_circle)
{
    a_circle.print(_os);
    return _os;
}

#endif