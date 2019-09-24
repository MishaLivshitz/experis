#include "TempSensor_so.h"
#include "TempEvent_so.h"

namespace Demo{

using namespace advcpp;

class TempRunnable_So: public advcpp::Runnable
{
public:    
    TempRunnable_So(TempSensor_So& a_sensor)
    :m_sensor(a_sensor)
    {
    }

    virtual void run()
    {
        std::srand(time(0));
        while(m_sensor.isRunning())
        {
            int temp = std::rand() % 100 - 30;
            if(temp>50 || temp < -5)
            {
                m_sensor.createEventAndsend(temp);
            }
            sleep(3);
        }
    }
private:
    TempSensor_So& m_sensor;
};

bool TempSensor_So::isRunning() const
{
    return m_isRunning;
}

void TempSensor_So::connect(advcpp::SharedPtr<SmartHomeInterfaces::IEventTaker> const& a_eventTaker)
{
    SensorDevice::connect(a_eventTaker);
    monitor();
}

TempSensor_So::TempSensor_So(advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config)
: SmartHomeDevice::SensorDevice(a_config)
,m_isRunning(false)
{

}

TempSensor_So::~TempSensor_So() 
{
    m_isRunning = false;
    m_thread->join();
}


void TempSensor_So::createEventAndsend(int a_temp)
{
    SharedPtr<Event> e  = SharedPtr<Event>(new TempEvent_So(location(), a_temp));
    sendEvent(e);
}


void TempSensor_So::monitor()
{
    m_isRunning = true;
    m_runnable = SharedPtr<Runnable>(new TempRunnable_So(*this));
    m_thread = SharedPtr<Thread>(new Thread(*m_runnable));
    //m_thread->detach();
}


extern "C"
SmartHomeDevice::Device* makeDevice(
    advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> a_config)
{
    return new TempSensor_So(a_config);
}

} //Demo