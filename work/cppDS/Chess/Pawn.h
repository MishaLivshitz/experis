#ifndef PAWN_H
#define PAWN_H


#include "ChessPiece.h"

class Pawn: public ChessPiece
{

public:

    Pawn(int _x, int _y, ChessPiece::Color _color);
    virtual vector<pair<int,int> > CalcMoves(int _x, int _y, ChessBoard const& _board) const;

private:
    bool isValidMove(int _x, int _y, int _state , ChessBoard const& _board) const;
    void moveByColor(int _x, int _y, ChessPiece::Color _color, ChessBoard const& _board, vector<pair<int,int> >&) const;
};

#endif