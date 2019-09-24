#ifndef CELL_H
#define CELL_H

#include "ChessPiece.h"

class ChessBoard;


class Cell
{
    
friend class ChessBoard;

public:
    bool state() const;
    ChessPiece* piece() const;

private:
    Cell(bool _stata = false, ChessPiece* _piece = 0 );
    void state(bool _state);

    void piece(ChessPiece*);
    bool m_state;
    ChessPiece* m_piece;
};

inline void Cell::state(bool _state)
{
    m_state = _state;
}

inline bool Cell::state() const
{
    return m_state;
}

inline ChessPiece* Cell::piece() const
{
    return m_piece;
}

inline void Cell::piece(ChessPiece* _piece)
{
    m_piece = _piece;
}


#endif
