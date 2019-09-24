#ifndef TEXT_UP_CASE_H
#define TEXT_UP_CASE_H

#include "TextProcessor.h"


class TextUpCaser: public TextProcessor
{
public:
    virtual ~TextUpCaser();
    virtual void process(std::string const&);

    void toUpCase(std::string& _str) const;

};



#endif