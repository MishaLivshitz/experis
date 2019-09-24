#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author
{

public:

    Author();
    Author(std::string _name);

    void name(std::string const& _name); // throws exception??!? when _name = 0?
    std::string const& name() const; 


private:
    std::string m_name;

};

inline void Author::name(std::string const& _name)
{
    m_name = _name;
}

inline std::string const& Author::name() const
{
    return m_name;
} 

#endif