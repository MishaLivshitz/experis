#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include "Token.h"

class Tokenizer
{
public:

    static void getTokens(std::string const& _str, std::vector<Token>& _tokens);

private:
    Tokenizer();
};

#endif