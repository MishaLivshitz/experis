#ifndef IEVENT_TAKER_H
#define IEVENT_TAKER_H

#include "Event.h"
#include "SharedPtr.h"

namespace SmartHomeInterfaces
{

class IEventTaker
{
public:
    virtual ~IEventTaker();
    virtual void receiveEvent(advcpp::SharedPtr<advcpp::Event> m_event) = 0;
};

}



#endif //IEVENT_TAKER_H