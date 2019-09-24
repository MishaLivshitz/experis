#include "Line.h"

class ParametricCurve: public Line
{
public:

    ParametricCurve(Color const& _c, Point const& _begin, Point const& _end,Point const& _control);
    virtual ~ParametricCurve(){};

protected:
    virtual void cureveFunc(double direction, Point& _nextPoint) const = 0;
    virtual void Move(Point const& _diraction);

protected:
    static double const m_advancement;
    Point m_controlP;
};