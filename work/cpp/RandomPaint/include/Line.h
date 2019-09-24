#ifndef LINE_H
#define LINE_H

#include "Shape.h"
#include "Moveable.h"


class Line: public Shape, public Moveable
{
public:

    Line(Color const& _c, Point const& _pBegin, Point const& _pEnd = Point(0,0));
    virtual ~Line();

    virtual double area() const;
    virtual void draw(Canvas& _canvas) const;
    virtual void Move(Point const& _p);

    void endPoint(Point const& _p);
    Point const& endPoint();

private:
    void preparePoints(int& x0,int& x1, int& y0, int& y1) const;
    int calcSlope() const;

protected:
   int m_slope;
   Point m_endPoint;
};

#endif