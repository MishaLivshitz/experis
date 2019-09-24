#ifndef SO_BUILDER_H
#define SO_BUILDER_H

#include "SharedPtr.h"
#include "IBuilder.h"
#include "SharedLibUtil.h"
#include "MyException.h"
#include "SystemInitializer.h"
#include "Device.h"


namespace ServerComponents{

class SoBuilder: public SmartHomeInterfaces::IBuilder
{
   
public:
    virtual void build(advcpp::SharedPtr<ServerComponents::DevicesHolder>& a_devices,
                        std::vector<advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> > const & a_configs);
private:

    void createDevice(  advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config,
                                            advcpp::SharedPtr<ServerComponents::DevicesHolder>& a_devices) const;

private:

};



}//ServerComponents

#endif //SO_BUILDER_H