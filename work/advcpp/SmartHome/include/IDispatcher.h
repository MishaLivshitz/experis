#ifndef IDISPATCHER_H
#define IDISPATCHER_H

#include "SharedPtr.h"
#include "Event.h"
#include <vector>
#include "ControllerDevice.h"

namespace SmartHomeInterfaces{


class IDispatcher
{
public:
    typedef std::vector<SmartHomeInterfaces::IEventHandler* > Consumers;
    virtual ~IDispatcher();
    virtual void activate(advcpp::SharedPtr<advcpp::Event> a_event, Consumers const* a_controllers) = 0;
};

}



#endif //IDISPATCHER_H