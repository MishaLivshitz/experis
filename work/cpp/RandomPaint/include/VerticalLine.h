#ifndef VERTICAL_H
#define VERTICAL_H

#include "Line.h"

class VerticalLine: public Line
{
public:

    VerticalLine();
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