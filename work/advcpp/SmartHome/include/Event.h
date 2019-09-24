#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "Location.h"
#include <ctime>
#include <iostream>

namespace advcpp{

namespace EventDetails{
    class Terminator_tag{};
}

class Event
{

public:

    Event();
    Event(EventDetails::Terminator_tag);
    Event(SmartHomeGeneral::Location const& a_location);
    virtual ~Event();

    SmartHomeGeneral::Location const& location() const;
    char const* time() const;
    std::string const& type() const;
    void time();

protected:
    

protected:
    SmartHomeGeneral::Location m_location;
    std::time_t                m_time;         
    static std::string         m_type;
};



}//advcpp
#endif