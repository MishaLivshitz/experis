#ifndef PLAYER_H
#define PLAYER_H

#include "ChessPiece.h"
#include <string>

using std::string;
using std::vector;
using std::pair;

class Player
{
public:
    Player(string const& _name, ChessPiece::Color _color);
    
    ChessPiece::Color color() const;

private:
   
    string m_name;
    ChessPiece::Color m_color;

};

inline ChessPiece::Color Player::color() const
{
    return m_color;
}

#endif