#include "Animal.h"
#include "iostream"

Animal::Animal() 
{

}
Animal::~Animal()
{}

void Animal::setName(std::string const& a_name)
{
     m_name = a_name;
}

class Dog: public Animal
{
public:
    Dog(){};
    void makeNoise() const {
        std::cout << "Whoraf: " << m_name << '\n';
    };
   
};

class Cat: public Animal
{
public:
    Cat(){};
    void makeNoise() const {
        std::cout << "Meowwww: " << m_name << '\n';
    };
};

extern "C"
Animal* makeDog()
{
    return new Dog();
}

extern "C"
Animal* makeCat()
{
    return new Cat();
}
