#ifndef SQUARE_H
#define SQUARE_H


#include "RectAngle.h"
#define _USE_MATH_DEFINES
#include <cmath>
 


class Square: public RectAngle
{
public:
    Square(int _x=0 ,int _y = 0 , size_t _side = 0);
    Square(Point _p, size_t _side = 0);

    virtual ~Square();
    virtual double area() const;
    size_t side() const;
    void side(size_t a_side);

};

#endif