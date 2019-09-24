#include "Tokenizer.h"
#include <istream>
#include <sstream>

void Tokenizer::getTokens(std::string const& _str, std::vector<Token>& _tokens)
{
    int const size = 256;
    char buff[size];
    std::stringstream streamStr(_str);
    std::stringstream buffStream;
    
    while(!streamStr.eof())
    {
        streamStr.getline(buff, size, ' ');
       _tokens.push_back(Token(buff, !std::isdigit(buff[0])));
    }
}