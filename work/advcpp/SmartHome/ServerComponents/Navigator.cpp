#include "Navigator.h"

namespace ServerComponents{

using ServerDetails::SystemTerminatorEvent;
using advcpp::EventDetails::Terminator_tag;
using advcpp::SharedPtr;
using advcpp::Thread;
using advcpp::Event;
using SmartHomeInterfaces::IDispatcher;


SystemTerminatorEvent::SystemTerminatorEvent(Terminator_tag a_tag)
:Event(a_tag)
{
    
}

void Navigator::waitForTerminating() const
{
    m_thread->join();
}

Navigator::Navigator(SPGiver a_giver, SPDispatcher a_dispatcher , SPSearcher a_searcher)
: m_giver(a_giver)
, m_dispatcher(a_dispatcher)
, m_searcher(a_searcher)
, m_thread(SharedPtr<Thread>(new Thread(*this)))
{

}

void Navigator::run()
{
    while(true)
    {
        SharedPtr<Event> event;
        m_giver->give(event);

        if(dynamic_cast<SystemTerminatorEvent*> (&*event))
        {
            break;
        }
        
        IDispatcher::Consumers const* controllers =
                                m_searcher->search(std::make_pair(event->type(), event->location()));
        if(controllers)
        {
            m_dispatcher->activate(event, controllers);
        }
    }
}


} // ServerComponents