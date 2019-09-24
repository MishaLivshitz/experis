#ifndef SQUARE_H
#define SQUARE_H


#include "Moveable.h"
#include "HorizontalLine.h"
#include "VerticalLine.h"

class Square: public Shape, public Moveable
{
public:

    Square(Color _c, Point _p, size_t _side = 0);

    virtual ~Square();
    virtual double area() const;
    virtual void draw(Canvas& _canvas) const;
    virtual void Move(Point const&);

    size_t side() const;
    void side(size_t a_side);

private:

    HorizontalLine m_horizontal;
    HorizontalLine m_horizontalEnd;
    VerticalLine m_vertical;
    VerticalLine m_verticalEnd;

};

#endif