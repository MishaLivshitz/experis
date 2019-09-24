#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class Animal
{
public:

    Animal();
    virtual ~Animal();
    void setName(std::string const& a_name);
    virtual void makeNoise() const {};

protected:
    std::string m_name;

};



#endif