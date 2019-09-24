#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "VerticalLine.h"
#include "HorizontalLine.h"
#include "Moveable.h"

class RectAngle: public Shape, public Moveable
{    
public:
    
    RectAngle(Color const& _color, Point const& _p, int _width = 0, int _height = 0);

    virtual ~RectAngle();
    virtual double area() const;
    virtual void Move(Point const&);
    virtual void draw(Canvas& _canvas) const;

    int width() const;
    void width(int a_width);
    void height(int a_height);
    int height() const;
   

protected:
    
    HorizontalLine m_horizontal;
    HorizontalLine m_horizontalEnd;
    VerticalLine m_vertical;
    VerticalLine m_verticalEnd;

private:
    static const bool s_MOVEABLE;
};

#endif