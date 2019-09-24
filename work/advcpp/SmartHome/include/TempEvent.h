#ifndef TEMP_EVENT_H
#define TEMP_EVENT_H

#include "Event.h"

namespace Demo{


class TempEvent: public advcpp::Event
{
public:
    TempEvent(SmartHomeGeneral::Location const& a_location, double a_temp);

    void temp(double a_temp);
    double temp() const;

private:
    double m_temp;
};


}// DemoDevices


#endif //TEMP_EVENT_H