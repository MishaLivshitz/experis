#ifndef ISEARCHABLE_H
#define ISEARCHABLE_H

#include <vector>
#include "IEventHandler.h"
#include "SharedPtr.h"

namespace SmartHomeInterfaces
{
    
class ISearchable
{
public:
    virtual ~ISearchable();
    virtual std::vector<IEventHandler*> const* search(std::pair<std::string,SmartHomeGeneral::Location> const& a_eventType) const = 0;
};

} //SmartHomeInterfaces











#endif //ISEARCHABLE_H