#ifndef LOCATION_H
#define LOCATION_H

#include <string>

namespace SmartHomeGeneral
{


class Location
{
public:
    
    Location(std::string const& a_room = "", int a_floor = -1);

    std::string const& room() const;
    int floor() const;

    bool operator <(Location const& a_rhs) const;
    bool operator ==(Location const& a_rhs) const;

private:
    std::string m_room;
    int         m_floor;
};


}//SmartHomeGeneral

#endif //LOCATION_H

