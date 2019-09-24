#ifndef DEVICE_H
#define DEVICE_H

#include "DeviceConfig.h"
#include "SharedPtr.h"

namespace SmartHomeDevice{


class Device
{
public:

    Device(advcpp::SharedPtr<DeviceConfig> a_device);
    virtual ~Device() = 0;

    std::string const&  config() const;
    SmartHomeGeneral::Location  const&  location() const;
    std::string const&  type() const;
    std::string const&  id() const;

private:
    advcpp::SharedPtr<DeviceConfig> m_config;

};



}



#endif // DEVICE_H