#include "ParametricCurve.h"


ParametricCurve::ParametricCurve(Color const& _c, Point const& _begin, Point const& _end ,Point const& _control)
: Line(_c,_begin,_end)
,m_controlP(_control)
{

}

void ParametricCurve::Move(Point const& _diraction)
{
    Line::Move(_diraction);
    m_controlP += _diraction;
}


double const ParametricCurve::m_advancement = 0.001;