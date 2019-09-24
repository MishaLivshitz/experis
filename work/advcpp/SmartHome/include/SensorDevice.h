#ifndef SENSOR_DEVICE_H
#define SENSOR_DEVICE_H

#include "IConnectable.h"
#include "Device.h"

namespace SmartHomeDevice
{


class SensorDevice: public virtual Device
                    , public SmartHomeInterfaces::IConnectable
{
public:
    SensorDevice(advcpp::SharedPtr<DeviceConfig>);
    virtual void connect(advcpp::SharedPtr<SmartHomeInterfaces::IEventTaker> const& a_eventTaker);

protected: 
    void sendEvent(advcpp::SharedPtr<advcpp::Event> a_event);
private:
    advcpp::SharedPtr<SmartHomeInterfaces::IEventTaker> m_eventTaker;

};


}

#endif //SENSOR_DEVICE_H