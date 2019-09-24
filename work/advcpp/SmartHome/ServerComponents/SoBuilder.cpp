#include "SoBuilder.h"
#include "SensorDevice.h"
#include "ControllerDevice.h"

namespace ServerComponents{

    using SmartHomeDevice::Device;
    using SmartHomeDevice::DeviceConfig;
    using SmartHomeDevice::ControllerDevice;
    using SmartHomeDevice::SensorDevice;
    using ServerComponents::DevicesHolder;
    using advcpp::SharedPtr;
    using advcpp::SharedLibUtil;

void SoBuilder::createDevice(SharedPtr<DeviceConfig> a_config, SharedPtr<DevicesHolder>& a_devices) const
{
    typedef Device* (*MakeDevice)(SharedPtr<DeviceConfig> a_config);

    try
    {
        std::string libName = "./SharedObjects/lib" + a_config->type() + ".so";
        SharedLibUtil sUtil(libName.c_str());
        MakeDevice make = reinterpret_cast<MakeDevice>(sUtil.getPtr("makeDevice"));
        Device* d = make(a_config);
        
        a_devices->addDevice(SharedPtr<Device>(d));

    }
    
    catch(MyException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void SoBuilder::build(SharedPtr<DevicesHolder>& a_devices, std::vector<SharedPtr<DeviceConfig> > const& a_configs)
{
    std::vector<SharedPtr<DeviceConfig> >::const_iterator itrB = a_configs.begin(); 
    std::vector<SharedPtr<DeviceConfig> >::const_iterator itrE = a_configs.end(); 

    while(itrB!=itrE)
    {
        createDevice(*itrB, a_devices);
        ++itrB;
    }
}

}//ServerComponents