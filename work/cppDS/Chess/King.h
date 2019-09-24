#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King: public ChessPiece
{
public:
    King(int _x, int _y, ChessPiece::Color _color);
    virtual vector<pair<int,int> > CalcMoves(int _x, int _y, ChessBoard const& _board) const;

};


#endif