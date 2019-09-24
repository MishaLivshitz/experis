#ifndef TEXT_PROVIDER
#define TEXT_PROVIDER

#include "Provider.h"
#include <sstream>

class TextProvider: public Provider
{

public:
    TextProvider(char const* _fileName) throw (MyException);
    
    virtual ~TextProvider();
    virtual std::map<int, std::string>* provide();



private:
    std::ifstream m_fileStream;

};



#endif