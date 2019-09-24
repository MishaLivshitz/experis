#include "TextProcessor.h"
#include <iostream>


TextProcessor::TextProcessor()
{
}

TextProcessor::~TextProcessor()
{
    std::cout << "TextProcessor distructor"<< std::endl;
}

void TextProcessor::process(std::string const& a_str)
{
    std::string str = a_str;
    m_vec.push_back(str);
}

size_t TextProcessor::numLinesProcessed() const
{
    return m_vec.size();
}

void TextProcessor::display(std::ostream& a_os) const
{
    Vector::const_iterator itB = m_vec.begin();
    Vector::const_iterator itE = m_vec.end();

    while(itB!=itE)
    {
        a_os << *itB << std::endl;
        ++itB;
    }
}


