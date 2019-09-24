
#include "TextUpCensor.h"

TextUpCensor::TextUpCensor(std::string _censorList="")
{
    m_textCensor.setCensorList(_censorList);  
}

TextUpCensor::~TextUpCensor()
{
    std::cout << "TextUpCensor destructor" << std::endl;
}

void TextUpCensor::process(std::string const& _str)
{
    std::string str = _str;

    m_textCensor.censor(str);
    m_textUpper.toUpCase(str);
    m_vec.push_back(str);
}
