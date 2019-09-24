#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "VerticalLine.h"
#include "HorizontalLine.h"

class RectAngle: public Shape
{    
public:
    
    RectAngle(Color const& _color, int _x=0 ,int _y = 0 , int _width = 0, int _length = 0);
    RectAngle(Color const& _color, Point const& _p, int _width = 0, int _length = 0);

    virtual ~RectAngle();
    virtual double area() const;
    virtual void draw(Canvas& _canvas) const;

    int width() const;
    void width(int a_width);
    void length(int a_length);
    int length() const;

private:
    void setLinesPoint(int _width, int _height);

protected:
    
    HorizontalLine m_horizontal;
    HorizontalLine m_horizontalEnd;
    VerticalLine m_vertical;
    VerticalLine m_verticalEnd;

};

#endif