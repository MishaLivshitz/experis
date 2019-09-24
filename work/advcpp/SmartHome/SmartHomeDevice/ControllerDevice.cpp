#include "ControllerDevice.h"
#include "ISubscriptor.h"


namespace SmartHomeDevice{

using advcpp::SharedPtr;
using SmartHomeInterfaces::ISubscriptor;
using SmartHomeInterfaces::IEventHandler;
using SmartHomeGeneral::Location;

ControllerDevice::ControllerDevice(SharedPtr<DeviceConfig> a_config)
:Device(a_config)
{

}

void ControllerDevice::registraition(SharedPtr<ISubscriptor> a_subscriptor)
{
    m_subscriptor = a_subscriptor;
}

void ControllerDevice::subscribe(std::pair<std::string, Location> const& a_typeEvent, IEventHandler* a_handle)
{
    m_subscriptor->receiveSubscription(a_typeEvent, a_handle);
}

}//SmartHomeDevice