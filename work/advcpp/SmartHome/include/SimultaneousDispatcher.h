#ifndef SIMULTANEOUS_DISPATCHER_H
#define SIMULTANEOUS_DISPATCHER_H

#include "IDispatcher.h"
#include "ThreadPoolExecutor.h"

namespace ServerComponents{

class SimultaneousDispatcher: public SmartHomeInterfaces::IDispatcher
{

public:
    SimultaneousDispatcher();
    void endDispatching();
    virtual void activate(advcpp::SharedPtr<advcpp::Event> a_event, IDispatcher::Consumers const* a_controllers);

private:
    advcpp::ThreadPoolExecutor m_tPool;
};


}//ServerComponents





#endif //SIMULTANEOUS_DISPATCHER_H