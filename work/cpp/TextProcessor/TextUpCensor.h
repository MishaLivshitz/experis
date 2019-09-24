#include "TextProcessor.h"
#include "TextCensor.h"
#include "TextUpCaser.h"


class TextUpCensor: public TextProcessor
{
public:
    
    TextUpCensor(std::string _censorList);
    virtual ~TextUpCensor();
    virtual void process(std::string const&);


private:
    TextCensor  m_textCensor;
    TextUpCaser m_textUpper;
};