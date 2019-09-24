#include "DeviceConfig.h"


namespace SmartHomeDevice{

using SmartHomeGeneral::Location;

DeviceConfig::DeviceConfig()
{

}

DeviceConfig::DeviceConfig(     std::string const& a_id,
                                std::string const& a_room,
                                int a_floor,
                                std::string const& a_type,
                                std::string const& a_config)
: m_id(a_id)
, m_location(a_room, a_floor)
, m_type(a_type)
, m_config(a_config)
{

}

std::string const& DeviceConfig::id()
{
    return m_id;
}

Location const& DeviceConfig::location()
{
    return m_location;
}

std::string const& DeviceConfig::type()
{
    return m_type;
}

std::string const& DeviceConfig::config()
{
    return m_config;
}


}//advcpp

