#ifndef VERTICAL_H
#define VERTICAL_H

#include "Shape.h"

class VerticalLine: public Shape
{
public:

    VerticalLine();
    VerticalLine(Color const& _c, int _x = 0, int _y = 0, int _len = 0);
    VerticalLine(Color const& _c,Point const& _p, int _len = 0);
    virtual ~VerticalLine();

    virtual double area() const;
    virtual void draw(Canvas& _canvas) const;
    int len() const;
    void len(int len);

private:
   int m_len;
};

#endif