#ifndef ICONNECTABLE_H
#define ICONNECTABLE_H

#include "IEventTaker.h"

namespace SmartHomeInterfaces{


class IConnectable
{
public:
    virtual ~IConnectable();
    virtual void connect(advcpp::SharedPtr<SmartHomeInterfaces::IEventTaker> const& a_eventTaker) = 0;

};

} // SmartHomeInterfaces






#endif //ICONNECTABLE_H