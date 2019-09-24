#include "RandomFactory.h"

RandomFactory::RandomFactory(int _range)
:m_range(_range)
{
    srand(time(0));
}

//static initalizers
int const RandomFactory::s_COLOR_RANGE = 256;