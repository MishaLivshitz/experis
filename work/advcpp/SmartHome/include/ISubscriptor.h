#ifndef ISUBSCRIPTOR_H
#define ISUBSCRIPTOR_H

#include <string>
#include <utility>
#include "Location.h"
	

namespace SmartHomeInterfaces{

class IEventHandler;

class ISubscriptor
{
public:
    virtual ~ISubscriptor();
    virtual void receiveSubscription(std::pair<std::string,SmartHomeGeneral::Location> const& a_eventType, IEventHandler* a_handler) = 0;
    
};


}

#endif //ISUBSCRIPTOR_H