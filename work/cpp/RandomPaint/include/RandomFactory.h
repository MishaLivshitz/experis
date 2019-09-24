#ifndef RANDOM_FACTORY_H
#define RANDOM_FACTORY_H

#include "Color.h"
#include "Point.h"
#include "ctime"
#include <cstdlib>

class RandomFactory
{

public:

    RandomFactory(int _range = 100);
    Point   generatePoint() const;
    Color   generateColor() const;
    int     generateInt() const;

private:
    int m_range;
    int static const s_COLOR_RANGE;

};

inline Point RandomFactory::generatePoint() const
{
    int x = generateInt();
    int y = generateInt();
    
    return Point(x,y);
}

inline Color RandomFactory::generateColor() const
{
    int r = std::rand() % s_COLOR_RANGE;
    int g = std::rand() % s_COLOR_RANGE;
    int b = std::rand() % s_COLOR_RANGE;

    return Color(r,g,b);
}

inline int RandomFactory::generateInt() const
{
    return std::rand() % m_range;
}

#endif