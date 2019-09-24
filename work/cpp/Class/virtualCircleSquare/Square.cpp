#include "Square.h"


Square::Square(double a_radius, std::string _color)
:Base(a_radius,_color)
{

}

Square::~Square()
{
    std::cout << "Square distructor" << std::endl;
}

