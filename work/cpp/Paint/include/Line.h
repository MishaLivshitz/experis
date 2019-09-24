#ifndef LINE_H
#define LINE_H


#include "Shape.h"

class Line: public Shape
{
public:

    Line();
    Line(Color const& _c, Point const& _pBegin, Point const& _pEnd = 0);
    virtual ~Line();

    virtual double area() const;
    virtual void draw(Canvas& _canvas);

    void endPoint(Point const& _p);
    Point const& endPoint();

private:
    int calcSlope() const;

private:
   int m_slope;
   Point m_endPoint;
};

#endif