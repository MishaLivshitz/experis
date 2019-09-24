#ifndef HORIZONTAL_H
#define HORIZONTAL_H


#include "Shape.h"

class HorizontalLine: public Shape
{
public:

    HorizontalLine();
    HorizontalLine(Color const& _c, int _x = 0, int _y = 0, int _len = 0);
    HorizontalLine(Color const& _c, Point const& _p, int _len = 0);
    virtual ~HorizontalLine();

    virtual double area() const;
    virtual void draw(Canvas& _canvas) const;
    int len() const;
    void len(int _len);

private:
   int m_len;
};

#endif