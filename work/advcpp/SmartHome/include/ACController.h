#ifndef AC_CONTROLLER_H
#define AC_CONTROLLER_H

#include "ControllerDevice.h"
#include "TempEvent.h"
#include <iostream>
#include "unistd.h"

namespace Demo{


class ACController: public SmartHomeDevice::ControllerDevice
                    , public SmartHomeInterfaces::IEventHandler
{
public:

    ACController(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config);

    ACController(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config,
                 advcpp::AtomicVal<size_t>& m_counter,
                 advcpp::AtomicVal<int>& m_temp);

    virtual void action(advcpp::Event const* a_event);
    
    void subscribeToEvents();

private:
    advcpp::AtomicVal<size_t>& m_counter;
    advcpp::AtomicVal<int>& m_temp;

};



}//DemoDevices

#endif //AC_CONTROLLER_H