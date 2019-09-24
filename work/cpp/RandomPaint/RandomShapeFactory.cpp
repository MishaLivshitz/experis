#include "RandomShapeFactory.h"
#include "Circle.h"
#include "RectAngle.h"
#include "Line.h"
#include "PowerCurve.h"
#include "HorizontalLine.h"
#include "VerticalLine.h"
#include "Square.h"

RandomShapeFactory::RandomShapeFactory(int _range)
: m_randomFactory(_range)
{

}

Drawable* RandomShapeFactory::createShape() const
{
    FactoryShapes shape = static_cast<FactoryShapes>(std::rand() % LAST);
    Point p = m_randomFactory.generatePoint();
    Color c = m_randomFactory.generateColor();
    
    switch (shape)
    {
    case CIRCLE:
        
       return new Circle(c,p,m_randomFactory.generateInt());

    case RECTANGLE:

        return new RectAngle(c,p,m_randomFactory.generateInt(),m_randomFactory.generateInt());

    case SQUARE:

        return new Square(c,p,m_randomFactory.generateInt());

    case HORIZONTAL:

        return new HorizontalLine(c,p,m_randomFactory.generateInt());

    case VERTICAL:

        return new VerticalLine(c,p,m_randomFactory.generateInt());
    
    case LINE:

        return new Line(c,p,m_randomFactory.generatePoint());

    case POWER_CURVE:

        return new PowerCurve(c,p,m_randomFactory.generatePoint(),m_randomFactory.generatePoint());

    default:
        return 0;
    }
}

Group* RandomShapeFactory::createGroup(int _size) const
{
    Group *newGroup = new Group(_size);

    for(int i =0; i< _size; ++i)
    {
        newGroup->add(createShape());
    }

    return newGroup;
} 