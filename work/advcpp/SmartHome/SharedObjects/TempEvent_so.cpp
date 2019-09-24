#include "TempEvent_so.h"


namespace Demo{

TempEvent_So::TempEvent_So(SmartHomeGeneral::Location const& a_location, double a_temp) 
: advcpp::Event(a_location)
,m_temp(a_temp)
{
    m_type = "TempEvent";
}

void TempEvent_So::temp(double a_temp)
{
    m_temp = a_temp;
}

double TempEvent_So::temp() const
{
    return m_temp;
}


}//DemoDevices