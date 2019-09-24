#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point{

public:

    Point(int x = 0,int y =0);

    int getX() const;
    int getY() const;

    void setX(int _x);
    void setY(int _y);

private:

    int m_x;
    int m_y;

};

#endif