#ifndef RANDOM_SHAPE_FACTORY
#define RANDOM_SHAPE_FACTORY


#include "RandomFactory.h"
#include "Drawable.h"
#include "Group.h"

class RandomShapeFactory
{
public:
    RandomShapeFactory(int _range = 100);

    Drawable* createShape() const;
    Group*    createGroup(int _size) const;  

private:
    RandomFactory m_randomFactory;
    enum FactoryShapes {CIRCLE, RECTANGLE, SQUARE, LINE, POWER_CURVE, HORIZONTAL, VERTICAL, LAST};
};

#endif