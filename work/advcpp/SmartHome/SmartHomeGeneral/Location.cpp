#include "Location.h"

namespace SmartHomeGeneral
{

Location::Location(std::string const& a_room, int a_floor)
:m_room(a_room)
,m_floor(a_floor)
{

}

std::string const& Location::room() const
{
    return m_room;
}

int Location::floor() const
{
    return m_floor;
}

bool Location::operator<(Location const& a_rhs) const
{
    if( m_floor < a_rhs.m_floor){
        return true;
    } else if(m_floor  == a_rhs.m_floor){
        return  m_room < a_rhs.m_room;
    }
    return false;        
}

bool Location::operator ==(Location const& a_rhs) const
{
    return (m_floor == a_rhs.m_floor && m_room == a_rhs.m_room);
}

}
