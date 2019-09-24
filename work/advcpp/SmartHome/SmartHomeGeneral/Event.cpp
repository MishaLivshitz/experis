#include "Event.h"

namespace advcpp
{
    using SmartHomeGeneral::Location;


std::string Event::m_type = "Event";

Event::Event(EventDetails::Terminator_tag a_tag)
{

}

Event::Event(Location const& a_location)
:m_location(a_location)
{

}

Event::~Event()
{
    
}

Location const& Event::location() const
{
    return m_location;
}

char const* Event::time() const
{
    return std::asctime(std::localtime(&m_time));
}

void Event::time()
{
    m_time = std::time(0);
}

std::string const& Event::type() const
{
    return m_type;
}

}//advcpp