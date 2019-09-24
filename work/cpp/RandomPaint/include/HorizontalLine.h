#ifndef HORIZONTAL_H
#define HORIZONTAL_H


#include "Line.h"

class HorizontalLine: public Line
{
public:

    HorizontalLine();
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