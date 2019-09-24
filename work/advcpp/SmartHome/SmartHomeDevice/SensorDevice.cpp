#include "SensorDevice.h"


namespace SmartHomeDevice{

using advcpp::SharedPtr;
using advcpp::Event;
using SmartHomeInterfaces::IEventTaker;



SensorDevice::SensorDevice(SharedPtr<DeviceConfig> a_config)
:Device(a_config)
{

}

void SensorDevice::connect(SharedPtr<IEventTaker> const& a_eventTaker)
{
    m_eventTaker = a_eventTaker;
}

void SensorDevice::sendEvent(SharedPtr<Event> a_event)
{
    a_event->time();
    m_eventTaker->receiveEvent(a_event);
}

}//SmartHomeDevices