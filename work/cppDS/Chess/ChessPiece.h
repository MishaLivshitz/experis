#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <iostream>
#include <vector>
#include <string>

class ChessBoard;

using std::vector;
using std::pair;
using std::string;

class ChessPiece
{

public:
    enum Color {BLACK, WHITE};

    ChessPiece(int _x, int _y, char _sign, Color _color);
    virtual ~ChessPiece() {};
    virtual vector<pair<int,int> > CalcMoves(int _x, int _y, ChessBoard const& _board) const = 0;

    char const sign() const;
    Color color() const;

    pair<int,int> getStartingPosition() const;
    
protected:
    char const m_sign;
    Color m_color;
    pair<int,int> const m_startingPosition;
  
};

inline ChessPiece::ChessPiece(int _x, int _y, char _sign, Color _color)
: m_sign(_sign)
, m_color(_color)
, m_startingPosition(pair<int,int>(_x,_y))
{
    
}

inline char const ChessPiece::sign() const
{
    return m_sign;
}

inline ChessPiece::Color ChessPiece::color() const
{
    return m_color;
}

inline pair<int,int> ChessPiece::getStartingPosition() const
{
    return m_startingPosition;
}


#endif