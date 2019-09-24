#ifndef TOKEN_H
#define TOKEN_H

#include <sstream>

class Token
{
public:

    Token(std::string const& _token, bool _isOp);

    bool isOp() const;
    std::string const& token() const;

private:

    std::string m_token;
    bool m_isOp;

};


inline bool Token::isOp() const
{
    return m_isOp;
}


inline std::string const& Token::token() const
{
    return m_token;
}


#endif