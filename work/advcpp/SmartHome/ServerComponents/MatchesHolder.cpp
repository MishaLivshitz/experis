#include "MatchesHolder.h"

namespace ServerComponents{

    using SmartHomeInterfaces::IEventHandler;
    using SmartHomeGeneral::Location;
    using advcpp::Mutex;
void MatchesHolder::receiveSubscription(SubKey const& a_eventType, IEventHandler* a_cDevice)
{
    advcpp::Mutex::MutexUtil m(m_mutex);
    m_subscribers[a_eventType].push_back(a_cDevice);
}

MatchesHolder::Consumers const* MatchesHolder::search(std::pair<std::string, Location> const& a_eventType) const
{
    advcpp::Mutex::MutexUtil m(m_mutex);
    EventConsumers::const_iterator itr = m_subscribers.find(a_eventType);

    if(itr!=m_subscribers.end())
    {
        return &itr->second;
    }

    return 0;   
}

} //ServerComponents