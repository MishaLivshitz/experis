#include "TempEvent.h"


namespace Demo{

TempEvent::TempEvent(SmartHomeGeneral::Location const& a_location, double a_temp) 
: advcpp::Event(a_location)
,m_temp(a_temp)
{
    m_type = "TempEvent";
}

void TempEvent::temp(double a_temp)
{
    m_temp = a_temp;
}

double TempEvent::temp() const
{
    return m_temp;
}






}//DemoDevices