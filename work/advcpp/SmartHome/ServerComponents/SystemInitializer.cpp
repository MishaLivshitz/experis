#include "SystemInitializer.h"
#include "IBuilder.h"

namespace ServerComponents{

    using advcpp::SharedPtr;
    using SmartHomeDevice::DeviceConfig;
    using SmartHomeInterfaces::IBuilder;
    using advcpp::Event;


SystemInitializer::SystemInitializer(SharedPtr<IBuilder> const& a_builder, const char* a_configFile)
:m_configs(new ConfigurationHandler(a_configFile))
,m_matches(new MatchesHolder)
,m_events(new EventsContainer)
,m_dispatcher(new SimultaneousDispatcher)
,m_navigator(new Navigator(SPGiver(m_events), SPDispatcher(m_dispatcher), SPSearcher(m_matches)))
,m_devices(new DevicesHolder)
,m_builder(a_builder)
{
    m_builder->build(m_devices, m_configs->configs());
    m_devices->connectDevices(m_events, m_matches);
}

void SystemInitializer::shutDown()
{
    m_events->terminateReceiving(SharedPtr<Event>
                        (new ServerDetails::SystemTerminatorEvent(advcpp::EventDetails::Terminator_tag())));
    m_events->stop();
    m_navigator->waitForTerminating();
    m_dispatcher->endDispatching();
}

}