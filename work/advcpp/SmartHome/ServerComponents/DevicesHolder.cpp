#include "DevicesHolder.h"
#include "MatchesHolder.h"
#include "EventsContainer.h"
#include <algorithm>

namespace ServerComponents{

using SmartHomeInterfaces::IEventTaker;
using SmartHomeInterfaces::ISubscriptor;
using SmartHomeDevice::ControllerDevice;
using SmartHomeDevice::SensorDevice;
using SmartHomeDevice::Device;
using advcpp::SharedPtr;

class ConnectOne
{
public:
    ConnectOne(SharedPtr<IEventTaker> const& a_events ,SharedPtr<ISubscriptor>const& a_matches) 
    : m_events(a_events)
    , m_matches(a_matches)
    {}

    void operator()(SharedPtr<Device>const& a_device ) const
    {
        ControllerDevice* pc = dynamic_cast<ControllerDevice*>(&*a_device);
        if(pc)
        {
            pc->registraition(m_matches);
        }

        SensorDevice* ps = dynamic_cast<SensorDevice*>(&*a_device);
        if(ps)
        {
            ps->connect(m_events);
        }
        
    }

private:
    SharedPtr<IEventTaker> const& m_events;
    SharedPtr<ISubscriptor> const& m_matches;
};

void DevicesHolder::addDevice(SharedPtr<Device> const& a_device)
{
    m_devices.push_back(a_device);
}

void DevicesHolder::connectDevices(SharedPtr<IEventTaker> const& a_events,
                        SharedPtr<ISubscriptor> const& a_matches) const
{
    std::for_each(m_devices.begin(), m_devices.end(), ConnectOne(a_events, a_matches));
}

}//ServerComponents