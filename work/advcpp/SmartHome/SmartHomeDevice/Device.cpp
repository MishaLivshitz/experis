#include "Device.h"
#include <iostream>

namespace SmartHomeDevice
{
    using advcpp::SharedPtr;
    using SmartHomeGeneral::Location;

Device::Device(SharedPtr<DeviceConfig> a_config)
:m_config(a_config)
{
    
}

Device::~Device()
{
    
}

std::string const& Device::config() const
{
    return m_config->config();
}

Location const&  Device::location() const
{
    return m_config->location();
}

std::string const&  Device::type() const
{
    return m_config->type();
}

std::string const&  Device::id() const
{
    return m_config->id();
}

} //SmartHomeDevice


