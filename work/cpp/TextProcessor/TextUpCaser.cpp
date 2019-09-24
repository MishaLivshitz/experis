#include "TextUpCaser.h"
#include <algorithm>


TextUpCaser::~TextUpCaser()
{
    std::cout << "TextUpCaser distructor" << std::endl;
}

void TextUpCaser::toUpCase(std::string& _str) const
{
    std::transform(_str.begin(), _str.end(), _str.begin(), ::toupper);  
}

void TextUpCaser::process(std::string const& a_str)
{
    std::string str = a_str;
    toUpCase(str);
    m_vec.push_back(str);
}