#include "cat.h"
#include <iostream>


Cat::Cat()
{

}

Cat::~Cat()
{

}

void Cat::lookForMice()
{
    std::cout << "MICE!~!~!" <<'\n';
}

void Cat::eat()
{
    std::cout << "Yammi" <<'\n';
}

void play()
{
    std::cout << "Dont bother me!!" <<'\n';
}