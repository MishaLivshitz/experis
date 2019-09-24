#ifndef RANDOM_FACTORY_H
#define RANDOM_FACTORY_H

#include "ctime"
#include <cstdlib>
#include <climits>

class RandomFactory
{

public:

    RandomFactory() throw();
    
    int generateInt(int _minRange, int _maxRange) const throw();

private:
  
    int static const s_COLOR_RANGE;

};

inline int RandomFactory::generateInt(int _minRange, int _maxRange) const throw()
{
    if(_minRange - _maxRange == 0)
    {
        ++_maxRange;
    }

    return std::rand() % (_maxRange - _minRange) + _minRange;
}

#endif