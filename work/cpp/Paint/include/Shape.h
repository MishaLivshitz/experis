#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include "Point.h"
#include "Canvas.h"

class Shape
{
public:
    Shape();
    Shape(Color const& _color, int _x = 0 , int _y = 0);
    Shape(Color const& _color, Point const& _p);

    virtual ~Shape();
    virtual double area() const = 0;
    virtual void draw(Canvas& _canvas) const = 0;

    Point const& getPoint() const;
    Color const& getColor() const;
    void setColor(Color const& _color);
    void setPoint(Point const& _p);

protected:
   Point m_origin;
   Color m_color;
};

#endif