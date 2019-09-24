#ifndef BUILDER_H
#define BUILDER_H

#include "SharedPtr.h"
#include "DeviceConfig.h"
#include <vector>

namespace ServerComponents{
        class DevicesHolder;
    }

namespace SmartHomeInterfaces{

class IBuilder
{
public:
    virtual ~IBuilder();
    virtual void build( advcpp::SharedPtr<ServerComponents::DevicesHolder>& a_devices,
                        std::vector<advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> > const & a_configs) = 0;
};

}//SmartHomeInterfaces

#endif //BUILDER_H
