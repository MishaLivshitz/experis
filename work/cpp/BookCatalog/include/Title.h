#ifndef TITLE_H
#define TITLE_H

#include <vector>
#include <string>
#include <sstream>

class Title
{
private:
    typedef std::vector<std::string> Title_t; 


public:
    Title(std::string&);
    Title_t const& title() const;

    void print(std::ostream& _os) const;

private: 
    Title_t m_title;

};


#endif