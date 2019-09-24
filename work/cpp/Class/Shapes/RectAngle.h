#include "Shape.h"



class RectAngle: public Shape
{
    
public:
    RectAngle(int _x=0 ,int _y = 0 , size_t _width = 0, size_t _length = 0);
    RectAngle(Point _p, size_t _width = 0, size_t _length = 0);

    virtual ~RectAngle();
    virtual double area() const;
    size_t width() const;
    void width(size_t a_width);
    void length(size_t a_length);
    size_t length() const;

protected:
    int m_width;
    int m_length;

};