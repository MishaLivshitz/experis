#ifndef CONFIGURATION_HANDLER
#define CONFIGURATION_HANDLER

#include <fstream>
#include <vector>
#include "DeviceConfig.h"
#include "SharedPtr.h"
#include "MyException.h"

namespace ServerComponents{

class ConfigurationHandler
{
typedef std::vector<advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> > Configs;
public:
    ConfigurationHandler(char const* fileName) throw (MyException);
    Configs const& configs() const;
    
private:
    void createConfigs();

private:
    std::ifstream m_file;
    Configs m_configs;

};

} //ServerComponents





#endif //CONFIGURATION_HANDLER