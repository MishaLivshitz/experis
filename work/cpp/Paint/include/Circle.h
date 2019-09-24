#ifndef CIRCLE_H
#define CIRCLE_H


#include "Shape.h"
#define _USE_MATH_DEFINES
#include <cmath>
 


class Circle: public Shape
{
public:
   Circle(Color _c, int _x, int _y, size_t _radius);

    Circle(Color _c, Point _p, size_t _radius = 0);

    virtual ~Circle();
    virtual double area() const;
    virtual void draw(Canvas& _c) const;
    size_t radius() const;
    void radius(int a_radius);

private:
    void drawQuarter(int xBegin ,int xEnd ,int yBegin ,int yEnd, Canvas& _canvas) const;


private:
    size_t m_radius;
};

#endif