#include "ACController.h"
#include <ctime>
#include <iostream>


namespace Demo{


ACController::ACController(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config,
                           advcpp::AtomicVal<size_t>& a_counter,
                           advcpp::AtomicVal<int>& a_temp)

:SmartHomeDevice::ControllerDevice(a_config)
, m_counter(a_counter)
, m_temp(a_temp)
{
    
}

void ACController::subscribeToEvents()
{
    subscribe(std::make_pair("TempEvent", SmartHomeGeneral::Location("Room6",3)), this);
}

void ACController::action(advcpp::Event const* a_event)
{
    const Demo::TempEvent* e = static_cast<const Demo::TempEvent*>(a_event);
    std::cout << "Sensor Floor: " << e->location().floor() << '\n';
    std::cout << "Sensor Room: " << e->location().room() << '\n';
    std::cout << "Time: " << e->time();
    std::cout << "Temperature is:" << e->temp() << '\n';
    std::cout << "Cooling Down..." << '\n';
    {
        while(m_temp>20)
        {
            m_temp -= e->temp()/2;
        }
    }
    sleep(1);
    ++m_counter;
    
}


}//Demo