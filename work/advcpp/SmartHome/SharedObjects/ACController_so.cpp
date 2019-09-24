#include "ACController_so.h"
#include "TempEvent_so.h"
#include <ctime>
#include <iostream>


namespace Demo{


ACController_So::ACController_So(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config)

:SmartHomeDevice::ControllerDevice(a_config)
{
    
}

void ACController_So::registraition(advcpp::SharedPtr<SmartHomeInterfaces::ISubscriptor> a_subscriptor)
{
    ControllerDevice::registraition(a_subscriptor);
    subscribeToEvents();
}

void ACController_So::subscribeToEvents()
{
    subscribe(std::make_pair("TempEvent", SmartHomeGeneral::Location("room_1_a",1)), this);
}

void ACController_So::action(advcpp::Event const* a_event)
{
    const Demo::TempEvent_So* e = static_cast<const Demo::TempEvent_So*>(a_event);
    std::cout << "Sensor Floor: " << e->location().floor() << '\n';
    std::cout << "Sensor Room: " << e->location().room() << '\n';
    std::cout << "Time: " << e->time();
    std::cout << "Temperature is:" << e->temp() << '\n';
    std::cout << "Cooling Down..." << '\n';
 
    sleep(1);
  
}

extern "C"
SmartHomeDevice::Device* makeDevice(
    advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config)
{
    return new ACController_So(a_config);
}

}//Demo