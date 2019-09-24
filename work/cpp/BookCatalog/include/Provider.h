#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <map>
#include <fstream> 
#include "MyException.h"

class Provider
{

public:
    virtual ~Provider() {};
    virtual std::map<int, std::string>* provide() = 0;

};


#endif