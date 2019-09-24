#ifndef CONTROLLER_DEVICE_H
#define CONTROLLER_DEVICE_H

#include "Device.h"
#include "IController.h"
#include "ISubscriptor.h"
#include "IEventHandler.h"

namespace SmartHomeDevice{

class ControllerDevice: public virtual Device 
                        ,public SmartHomeInterfaces::IController                        
{
public:
    ControllerDevice(advcpp::SharedPtr<DeviceConfig> a_config);
    virtual void registraition(advcpp::SharedPtr<SmartHomeInterfaces::ISubscriptor> a_subscriptor);
     
protected:
    void subscribe(std::pair<std::string,SmartHomeGeneral::Location> const& a_typeEvent , SmartHomeInterfaces::IEventHandler* a_handler);

private:
    advcpp::SharedPtr<SmartHomeInterfaces::ISubscriptor> m_subscriptor;
};

}




#endif //CONTROLLER_DEVICE_H