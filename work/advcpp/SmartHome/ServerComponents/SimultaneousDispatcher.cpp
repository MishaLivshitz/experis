#include "SimultaneousDispatcher.h"

namespace ServerComponents{

    using SmartHomeInterfaces::IEventHandler;
    using advcpp::Event;
    using advcpp::SharedPtr;
    using advcpp::Runnable;

class ConsumerRunnable: public advcpp::Runnable
{
public:
    ConsumerRunnable(IEventHandler* a_consumer, Event const* a_event);
    virtual void run();

private:    
    SmartHomeInterfaces::IEventHandler* m_handler;
    advcpp::Event const* m_event;
};

ConsumerRunnable::ConsumerRunnable(IEventHandler* a_handler, Event const* a_event)
:m_handler(a_handler)
,m_event(a_event)
{

}

void ConsumerRunnable::run()
{
    m_handler->action(m_event);
}

SimultaneousDispatcher::SimultaneousDispatcher()
:m_tPool(1)
{

}

void SimultaneousDispatcher::endDispatching()
{
    m_tPool.shutDown();
}

void SimultaneousDispatcher::activate(SharedPtr<Event> a_event, IDispatcher::Consumers const* a_controllers)
{
    if(a_controllers->size())
    {
        Consumers::const_iterator itrB = a_controllers->begin();
        Consumers::const_iterator itrE = a_controllers->end();

        while(itrE!=itrB)
        {
           SharedPtr<Runnable> r(new ConsumerRunnable(&**itrB, &*a_event));
            m_tPool.submit(r);
            ++itrB;
        }
    }
}


}//ServerComponents