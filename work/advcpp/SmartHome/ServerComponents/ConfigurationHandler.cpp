#include "ConfigurationHandler.h"
#include <iostream>
#include <string>
#include <sstream>

namespace ServerComponents{

using advcpp::SharedPtr;
using SmartHomeDevice::DeviceConfig;


ConfigurationHandler::ConfigurationHandler(char const* fileName) throw (MyException)
: m_file(fileName)
{
    if(!m_file.is_open())
    {
        std::string s = "cannot open file: ";
        throw EXCEPTION(MyException,s + fileName + '\n');
    }

    createConfigs();
}

ConfigurationHandler::Configs const& ConfigurationHandler::configs() const
{
    return m_configs;
}

void ConfigurationHandler::createConfigs()
{
    std::stringstream str;
    std::string id;
    std::string room;
    std::string floorStr;
    std::string type;
    std::string config;
    
    while(!m_file.eof())
    {
        while(id.empty())
        {
            getline(m_file, id);
        }

        getline(m_file, type);
        getline(m_file, room);
        getline(m_file, floorStr);
        getline(m_file, config);
        
        type.replace(0,type.find("= ",0,1) + 2,"");
        room.replace(0,room.find("= ",0,1) + 2,"");
        floorStr.replace(0,floorStr.find("= ",0,1) + 2,"");
        config.replace(0,config.find("= ",0,1) + 2,"");
        m_configs.push_back(SharedPtr<DeviceConfig>(new DeviceConfig(id, room, atoi(floorStr.c_str()), type, config)));
        
        id.clear();
        config.clear();
    }
}



}// ServerComponents