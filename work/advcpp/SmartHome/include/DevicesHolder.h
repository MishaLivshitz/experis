#ifndef DEVICES_HOLDER_H
#define DEVICES_HOLDER_H

#include "SensorDevice.h"
#include "ControllerDevice.h"
#include <vector>

namespace ServerComponents{

class MatchesHolder;
class EventsContainer;

class DevicesHolder
{
public:
    void addDevice(advcpp::SharedPtr<SmartHomeDevice::Device> const& a_device);
    void connectDevices(advcpp::SharedPtr<SmartHomeInterfaces::IEventTaker> const& a_events,
                        advcpp::SharedPtr<SmartHomeInterfaces::ISubscriptor> const& a_matches) const;
    
private:
    std::vector<advcpp::SharedPtr<SmartHomeDevice::Device> >  m_devices;

};


}//ServerComponents



#endif //DEVICES_HOLDER_H