#include "King.h"

King::King(int _x, int _y,ChessPiece::Color _color )
:ChessPiece(_x, _y, 'K', _color)
{
    
}

vector<pair<int,int> > King::CalcMoves(int _x, int _y, ChessBoard const& _board) const
{
    vector<pair<int,int> > moves;

    return moves;
}