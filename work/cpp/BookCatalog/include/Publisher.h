#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>

class Publisher
{

public:

    Publisher();
    Publisher(std::string _name);

    void name(std::string const& _name); // throws exception??!? when _name = 0?
    std::string const& name() const; 


private:
    std::string m_name;

};

inline void Publisher::name(std::string const& _name)
{
    m_name = _name;
}

inline std::string const& Publisher::name() const
{
    return m_name;
} 


#endif