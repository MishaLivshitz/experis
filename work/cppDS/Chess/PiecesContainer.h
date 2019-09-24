#ifndef PIECES_CONTAINER
#define PIECES_CONTAINER

#include "ChessPiece.h"
#include "vector"

using std::vector;

class PiecesContainer
{

public:
    PiecesContainer();
    ChessPiece* getWhitePiece();
    ChessPiece* getBlackPiece();
    void createPieces();

private:
    enum Types {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
    vector<ChessPiece*> m_blackPieces;
    vector<ChessPiece*> m_whitePieces;

};

inline ChessPiece* PiecesContainer::getWhitePiece() 
{
    size_t const size = m_whitePieces.size(); 
    if(size > 0)
    {
        ChessPiece* piece = m_whitePieces[size-1];
        m_whitePieces.pop_back();
        return piece;
    }

    return 0;
}

inline ChessPiece* PiecesContainer::getBlackPiece() 
{
    size_t const size = m_blackPieces.size(); 
    if(size > 0)
    {
        ChessPiece* piece = m_blackPieces[size-1];
        m_blackPieces.pop_back();
        return piece;
    }

    return 0;
}


#endif