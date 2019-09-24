
#include "Pawn.h"
#include "ChessBoard.h"

Pawn::Pawn(int _x, int _y, ChessPiece::Color _color)
:ChessPiece(_x, _y, 'p', _color)
{
    
}

bool Pawn::isValidMove(int _x, int _y, int _state, ChessBoard const& _board) const
{
    if(_state)
    {
        ChessPiece* p =  _board.getCell(_y, _x).piece();
        if(p->color() != m_color)
        {
            return true;
        }
    }
    
    return false;
}

void Pawn::moveByColor(int _x, int _y, ChessPiece::Color _color, ChessBoard const& _board, vector<pair<int,int> >& _moves) const
{

    int tempX = _x;
    int const nextY = _color == BLACK ? _y + 1: _y - 1;

    bool state = _board.getCell(tempX, nextY).state();

    if(!state)
    {
        //TODO:in first move can move 2 steps
        _moves.push_back(pair<int,int>(tempX, nextY));
    }

    for(int i=0, tempX = _x+1 ;i<2; ++i, tempX = _x-1)
    {
        state = _board.getCell(tempX,nextY).state();

        if (isValidMove(tempX, nextY, state, _board))
        {
            _moves.push_back(pair<int,int>(tempX, nextY));
        }
    }

}

vector<pair<int,int> > Pawn::CalcMoves(int _x, int _y, ChessBoard const& _board) const
{
    vector<pair<int,int> > moves;

    switch (m_color)
    {
        case WHITE:
            moveByColor(_x, _y, WHITE, _board, moves);
            break;

        case BLACK:
            moveByColor(_x, _y, BLACK, _board, moves);
            break;
    }

    return moves;
}