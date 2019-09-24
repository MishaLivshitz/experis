#ifndef AC_CONTROLLER_SO_H
#define AC_CONTROLLER_SO_H

#include "ControllerDevice.h"
#include <iostream>
#include "unistd.h"

namespace Demo{


class ACController_So: public SmartHomeDevice::ControllerDevice
                    , public SmartHomeInterfaces::IEventHandler
{
public:

    ACController_So(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config);
    void registraition(advcpp::SharedPtr<SmartHomeInterfaces::ISubscriptor> a_subscriptor);
    virtual void action(advcpp::Event const* a_event);
    
    void subscribeToEvents();
};



}//DemoDevices

#endif //AC_CONTROLLER_SO_H