#include "PiecesContainer.h"
#include "Pawn.h"
#include "King.h"

PiecesContainer::PiecesContainer()
: m_blackPieces(16)
, m_whitePieces(16)
{

}


void PiecesContainer::createPieces()
{
    for(int i = 0; i<8; ++i)
    {
        m_blackPieces.push_back(new Pawn(1,i,ChessPiece::BLACK));
        m_whitePieces.push_back(new Pawn(6,i,ChessPiece::WHITE));
    }

    m_blackPieces.push_back(new King(0,3,ChessPiece::BLACK)); 
    m_whitePieces.push_back(new King(7,3,ChessPiece::WHITE)); 
}
