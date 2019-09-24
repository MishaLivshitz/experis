#ifndef TEMP_SENSOR_SO_H
#define TEMP_SENSOR_SO_H

#include "SensorDevice.h"
#include "Thread.h"
#include <unistd.h>


namespace Demo{



class TempSensor_So: public SmartHomeDevice::SensorDevice
{
public:
    TempSensor_So(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config);
    virtual ~TempSensor_So();
    virtual void connect(advcpp::SharedPtr<SmartHomeInterfaces::IEventTaker> const& a_eventTaker);
    void createEventAndsend(int a_temp);
    void monitor();
    bool isRunning() const;
    
private:

private:
    
    advcpp::SharedPtr<advcpp::Runnable> m_runnable;
    advcpp::SharedPtr<advcpp::Thread> m_thread;
    bool m_isRunning;

};


} //Demo


#endif //TEMP_SENSOR_SO_H