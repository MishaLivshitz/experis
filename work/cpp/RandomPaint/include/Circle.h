#ifndef CIRCLE_H
#define CIRCLE_H


#include "Shape.h"
#define _USE_MATH_DEFINES
#include <cmath>
 


class Circle: public Shape
{
public:
   
    Circle(Color const& _c, Point const& _p, int _radius = 0);

    virtual ~Circle();
    virtual double area() const;
    virtual void draw(Canvas& _c) const;
    int radius() const;
    void radius(int a_radius);

private:
    void drawQuarter(int xBegin ,int xEnd ,int yBegin ,int yEnd, Canvas& _canvas) const;


private:
    int m_radius;
};

#endif