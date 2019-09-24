#ifndef EVENTS_CONTAINER_H
#define EVENTS_CONTAINER_H

#include "WaitableQueue.h"
#include "Event.h"
#include "IEventTaker.h"
#include "IEventGiver.h"

namespace ServerComponents
{


class EventsContainer: public SmartHomeInterfaces::IEventTaker, public SmartHomeInterfaces::IEventGiver
{
public:
    EventsContainer();
    virtual void receiveEvent(advcpp::SharedPtr<advcpp::Event> a_event); 
    virtual void give(advcpp::SharedPtr<advcpp::Event>& a_event);
    void terminateReceiving(advcpp::SharedPtr<advcpp::Event> const& a_terminator);
    void stop();

private:
    bool m_isShutingDown;
    advcpp::WaitableQueue<advcpp::SharedPtr<advcpp::Event> > m_eQueue;
};

}
#endif //EVENTS_CONTAINER_H