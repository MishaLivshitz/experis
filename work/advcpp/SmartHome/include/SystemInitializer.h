#ifndef SYSTEM_INITIALIZER_H
#define SYSTEM_INITIALIZER_H

#include "Navigator.h"
#include "MatchesHolder.h"
#include "EventsContainer.h"
#include "SimultaneousDispatcher.h"
#include "DevicesHolder.h"
#include "IBuilder.h"
#include "ConfigurationHandler.h"




namespace ServerComponents{

class SystemInitializer
{

public:
    SystemInitializer(advcpp::SharedPtr<SmartHomeInterfaces::IBuilder> const& a_builder, const char* a_configFile = "config.txt");
    advcpp::SharedPtr<MatchesHolder> subscriptor() const;
    advcpp::SharedPtr<EventsContainer> eventTaker() const;
    void addDevice(SmartHomeDevice::Device*);
    void shutDown();

private:
  
    advcpp::SharedPtr<ConfigurationHandler>          m_configs;
    advcpp::SharedPtr<MatchesHolder>                 m_matches;
    advcpp::SharedPtr<EventsContainer>               m_events;
    advcpp::SharedPtr<SimultaneousDispatcher>        m_dispatcher;
    advcpp::SharedPtr<Navigator>                     m_navigator;
    advcpp::SharedPtr<DevicesHolder>                 m_devices;
    advcpp::SharedPtr<SmartHomeInterfaces::IBuilder> m_builder;


};


}// ServerComponents


#endif //SYSTEM_INITIALIZER_H