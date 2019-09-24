#ifndef TEMP_EVENT_SO_H
#define TEMP_EVENT_SO_H

#include "Event.h"

namespace Demo{


class TempEvent_So: public advcpp::Event
{
public:
    TempEvent_So(SmartHomeGeneral::Location const& a_location, double a_temp);

    void temp(double a_temp);
    double temp() const;

private:
    double m_temp;
};


}// DemoDevices


#endif //TEMP_EVENT_SO_H