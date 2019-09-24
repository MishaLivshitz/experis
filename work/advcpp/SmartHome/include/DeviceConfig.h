#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#include <string>
#include "Location.h"

namespace SmartHomeDevice{


class DeviceConfig
{
public:
    DeviceConfig();
    DeviceConfig(   std::string const& a_id,
                    std::string const& a_room,
                    int floor, std::string const& a_type,
                    std::string const& a_config);

    std::string const& id();
    SmartHomeGeneral::Location const& location();
    std::string const& type();
    std::string const& config();

private:
    std::string m_id;
    SmartHomeGeneral::Location m_location;
    std::string m_type;
    std::string m_config;
};



}//advcpp








#endif //DEVICE_CONFIG_H