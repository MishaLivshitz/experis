#include "ParametricCurve.h"


class PowerCurve: public ParametricCurve
{
public:
    PowerCurve(Color const& _c, Point const& _begin, Point const& _end ,Point const& _control);

    virtual void draw(Canvas& _canvas) const;

protected:
    virtual void cureveFunc(double direction, Point& _nextPoint) const;

};