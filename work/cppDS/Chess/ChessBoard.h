#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "ChessPiece.h"
#include "Cell.h"
#include "Player.h"
#include <vector>

using std::vector;
using std::pair;

class ChessBoard
{

public:

    Cell const & getCell(int _x, int _y) const;
    void setCell(int _x, int _y, ChessPiece* _piece, bool _state);
    void PlayersPieces(Player const*, vector<pair<ChessPiece*, pair<int,int> > >&) const;
    void print() const;

private:
    static const char* s_BLACK_COLOR;
    static const char* s_RESET_COLOR;
    Cell m_board[8][8];    

};

inline Cell const& ChessBoard::getCell(int _x, int _y) const
{
    //check range!!! maybe exception 
    return m_board[_y][_x];
}

inline void ChessBoard::setCell(int _x, int _y, ChessPiece* _piece, bool _state)
{
    //check range!!! maybe exception
    m_board[_y][_x].state(_state);
    m_board[_y][_x].piece(_piece);
}

inline void ChessBoard::PlayersPieces(Player const* _player,vector<pair<ChessPiece*, pair<int,int> > >& _piecesPositions) const
{
    for(int i=0; i < 8;++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            if(m_board[i][j].state())
            {
                ChessPiece* p = m_board[i][j].piece();
                if(p->color() == _player->color())
                {
                    _piecesPositions.push_back(pair<ChessPiece*, pair<int,int> >(p ,pair<int,int>(j,i)));
                }
            }
        }
    }
}

#endif