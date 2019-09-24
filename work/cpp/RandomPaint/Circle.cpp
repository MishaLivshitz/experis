#include "Circle.h"


Circle::Circle(Color const& _c, Point const& _p, int _radius)
:Shape(_c,_p)
,m_radius(_radius)
{

}

Circle::~Circle()
{
}

double Circle::area() const
{
    return M_PI*pow(m_radius,2);
}

int Circle::radius() const
{
    return m_radius;
}

void Circle::radius(int a_radius)
{
    m_radius = a_radius;
}

void Circle::draw(Canvas& _c) const
{
    int x = m_origin.getX();
    int y = m_origin.getY();
    Point tempPoint;
    float dist;
    
    //Taken from GeeksForGeeks and modified
    for (int i = 0; i <= 2 * m_radius; ++i) { 
        // for vertical movement 
        for (int j = 0; j <= 2 * m_radius; j++) 
        { 
            dist = sqrt((i - m_radius) * (i - m_radius) + (j - m_radius) * (j - m_radius)); 
        
            // dist should be in the range (radius - 0.5) 
            // and (radius + 0.5) to draw pixel
            if (dist > m_radius - 0.5 && dist < m_radius + 0.5)
            {
                tempPoint.setX(x+i);
                tempPoint.setY(y+j);
                _c.drawPixel(m_color,tempPoint); 
            }          
        }
    }
}
