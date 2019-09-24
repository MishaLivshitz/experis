
#include "TextCensor.h"

TextCensor::TextCensor(std::string _censorList)
:TextProcessor()
,m_censorList(_censorList)
{

}

TextCensor::~TextCensor()
{
    std::cout << "TextCensor distructor" << std::endl;
}

void TextCensor::censor(std::string& _str) const
{
    std::string::iterator itB = _str.begin();
    std::string::iterator itE = _str.end();

    while(itB!=itE)
    {
        if(std::string::npos!=m_censorList.find(*itB))
        {
            *itB = '*';
        }

        ++itB;
    }
}

void TextCensor::setCensorList(std::string const& _c)
{
    m_censorList = _c;
}

void TextCensor::process(std::string const& a_str)
{
    std::string str = a_str;
    censor(str);
    m_vec.push_back(str);
}