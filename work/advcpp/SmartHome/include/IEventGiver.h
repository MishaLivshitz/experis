#ifndef IEVENT_GIVER_H
#define IEVENT_GIVER_H

#include "Event.h"
#include "SharedPtr.h"

namespace SmartHomeInterfaces
{

class IEventGiver
{
public:
    virtual ~IEventGiver();
    virtual void give(advcpp::SharedPtr<advcpp::Event>&) = 0;
};

}



#endif //IEVENT_TAKER_H