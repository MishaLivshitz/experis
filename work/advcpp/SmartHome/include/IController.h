#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "SharedPtr.h"

namespace SmartHomeInterfaces{
class ISubscriptor;

class IController
{
public:
    virtual ~IController();
    virtual void registraition(advcpp::SharedPtr<ISubscriptor> a_subscriptor) = 0;

};


} //SmartHomeInterfaces

#endif //ICONTROLLER