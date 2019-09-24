#include "TempSensor.h"

namespace Demo{

using namespace advcpp;

class TempRunnable: public advcpp::Runnable
{
public:    
    TempRunnable(TempSensor& a_sensor)
    :m_sensor(a_sensor)
    {
    }

    virtual void run()
    {
        while(true)
        {
            if(m_sensor.temp()>=25)
            {
                m_sensor.createEventAndsend();
            }
            sleep(1);
        }
    }
private:
    TempSensor& m_sensor;
};



TempSensor::TempSensor(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config, advcpp::AtomicVal<int>& a_temp)
: SmartHomeDevice::SensorDevice(a_config)
, m_temp(a_temp)
{
    
}

int TempSensor::temp()
{
    return m_temp.value();
}

TempSensor::~TempSensor() {
    
}


void TempSensor::createEventAndsend()
{
    SharedPtr<Event> e  = SharedPtr<Event>(new TempEvent(location(), m_temp.value()));
    sendEvent(e);
}


void TempSensor::monitor()
{
    m_runnable = SharedPtr<Runnable>(new TempRunnable(*this));
    m_thread = SharedPtr<Thread>(new Thread(*m_runnable));
    m_thread->detach();
}

} //Demo