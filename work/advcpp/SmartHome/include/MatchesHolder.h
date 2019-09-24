#ifndef MATCHES_HOLDER_H
#define MATCHES_HOLDER_H


#include "Event.h"
#include "ISearchable.h"
#include "ISubscriptor.h"
#include "IEventHandler.h"
#include "mutex.h"

#include <map>
#include <string>

namespace ServerComponents{


class MatchesHolder: public SmartHomeInterfaces::ISearchable, public SmartHomeInterfaces::ISubscriptor
{

public:
    typedef std::vector<SmartHomeInterfaces::IEventHandler*> Consumers;
    typedef const std::pair<std::string, SmartHomeGeneral::Location> SubKey;

private:

public:
    typedef std::map<SubKey, Consumers > EventConsumers;


public:
    virtual void receiveSubscription(SubKey const& a_eventType,
                                     SmartHomeInterfaces::IEventHandler* a_cDevice);

    virtual Consumers const* search(std::pair<std::string,SmartHomeGeneral::Location> const& a_eventType) const;

private:
    EventConsumers m_subscribers;
    mutable advcpp::Mutex  m_mutex;

};

}

#endif // MATCHES_HOLDER_H