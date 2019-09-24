#include "EventsContainer.h"


namespace ServerComponents{

using advcpp::SharedPtr;
using advcpp::Event;

EventsContainer::EventsContainer()
:m_isShutingDown(false)
{

}

void EventsContainer::stop()
{
    m_isShutingDown = true;
}

void EventsContainer::receiveEvent(SharedPtr<Event> a_event)
{
    if(!m_isShutingDown)
    {
        m_eQueue.enqueue(a_event);
    }
}

void EventsContainer::give(SharedPtr<Event>& a_event)
{   
    m_eQueue.dequeue(a_event);
}

void EventsContainer::terminateReceiving(SharedPtr<Event> const& a_terminator)
{
    receiveEvent(a_terminator);
}

}