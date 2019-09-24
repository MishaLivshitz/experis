
#include "TextProvider.h"
#include "Loader.h"

TextProvider::TextProvider(char const* _fileName) throw (MyException)
:m_fileStream(_fileName, std::ifstream::in)
{
    if(m_fileStream.fail())
    {
        throw EXCEPTION(MyException,"Cannot open file");
    }
}

TextProvider::~TextProvider()
{
    m_fileStream.close();
}


std::map<int, std::string>* TextProvider::provide()
{
        if(!m_fileStream.eof())
        {
            std::map<int, std::string>* lineMap = new std::map<int, std::string>();
            std::getline(m_fileStream, (*lineMap)[Loader::ISBN], '|');
            std::getline(m_fileStream, (*lineMap)[Loader::TITLE], '|');
            std::getline(m_fileStream, (*lineMap)[Loader::AUTHOR], '|');
            std::getline(m_fileStream, (*lineMap)[Loader::YEAR], '|');
            std::getline(m_fileStream, (*lineMap)[Loader::PUBLISHER] , '\n');
            (*lineMap)[Loader::LEN-1][(*lineMap)[Loader::PUBLISHER].size()-1] = '\0';

            return lineMap;
        }

    return 0;

}