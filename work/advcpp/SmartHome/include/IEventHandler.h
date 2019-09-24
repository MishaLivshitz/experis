#ifndef IEVENT_HANDLER_H
#define IEVENT_HANDLER_H

#include "Event.h"

namespace SmartHomeInterfaces{

class IEventHandler
{
public:
    virtual ~IEventHandler();
    virtual void action(advcpp::Event const* a_event) = 0;

};




} //SmartHomeInterfaces




#endif //IEVENT_HANDLER_H