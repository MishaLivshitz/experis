
#include "Title.h"

Title::Title(std::string& _title)
{
    char temp[256] = {0};
    std::stringstream temp_title(_title);
    while(!temp_title.eof())
    {
        temp_title.getline(temp, 256, ' ');
        m_title.push_back(temp);
    }
}

void Title::print(std::ostream& _os) const
{
    size_t const size = m_title.size();
    _os << "Title: ";
    for(size_t i = 0 ;i< size - 1 ;++i)
    {
        _os << m_title[i] << ' ';
    }

    _os << m_title[size-1] << std::endl;

}

Title::Title_t const& Title::title() const
{
    return m_title;
}