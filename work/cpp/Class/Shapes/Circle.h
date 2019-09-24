#ifndef CIRCLE_H
#define CIRCLE_H


#include "Shape.h"
#define _USE_MATH_DEFINES
#include <cmath>
 


class Circle: public Shape
{
public:
    Circle(int _x=0 ,int _y = 0 , size_t _radius = 0);

    Circle(Point _p, size_t _radius = 0);

    virtual ~Circle();
    virtual double area() const;
    size_t radius() const;
    void radius(int a_radius);


private:
    size_t m_radius;
};

#endif