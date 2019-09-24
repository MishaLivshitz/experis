#ifndef TEXT_CENSOR_H
#define TEXT_CENSOR_H

#include "TextProcessor.h"


class TextCensor: public TextProcessor
{
public:
    TextCensor(std::string _censorList = "");
    virtual ~TextCensor();
    virtual void process(std::string const&);

    void setCensorList(std::string const&);
    void censor(std::string& _str) const;

private:
    std::string m_censorList;

};



#endif