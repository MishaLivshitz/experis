#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include "SensorDevice.h"
#include "TempEvent.h"
#include "Thread.h"
#include <unistd.h>


namespace Demo{



class TempSensor: public SmartHomeDevice::SensorDevice
{
public:
    TempSensor(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config, advcpp::AtomicVal<int>& a_temp);
    virtual ~TempSensor();
    void createEventAndsend();
    void monitor();
    int temp();

private:
    
    advcpp::SharedPtr<advcpp::Runnable> m_runnable;
    advcpp::SharedPtr<advcpp::Thread> m_thread;
    advcpp::AtomicVal<int>& m_temp;
};


} //Demo


#endif //TEMP_SENSOR_H