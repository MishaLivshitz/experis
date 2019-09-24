#include "Game.h"


Game::Game(ChessBoard* _board ,Player const* _player1, Player const* _player2)
: m_players()
, m_board(_board)
{
   m_players[0] = _player1;
   m_players[1] = _player2;
}

void Game::displayPlayersPieces(vector<pair<ChessPiece*, pair<int,int> > > const& _pieces) const
{
    size_t const size = _pieces.size();
    pair<int,int> position;
    ChessPiece* p;
    
    for(size_t i = 0; i< size; ++i)
    {
        position = _pieces[i].second;
        p = _pieces[i].first;
        std::cout << i+1 << ":" << p->sign() <<" in " << position.second << ' ' << position.first << std::endl;
    }
}

void Game::startGame(PiecesContainer& _pieces)
{
    initBoard(_pieces);
    int playerNum = 0;
    int pieceToPlay;
    int x;
    int y;

    vector<pair<ChessPiece*, pair<int,int> > > piecesPositions;

    while(true)
    {
        m_board->PlayersPieces(m_players[playerNum], piecesPositions);
        displayPlayersPieces(piecesPositions);
        std::cout << std::endl << "Choose piece to play with" << std::endl;
        std::cin >> pieceToPlay;
        std::cin.clear();

        --pieceToPlay;
        x = piecesPositions[pieceToPlay].second.first; 
        y = piecesPositions[pieceToPlay].second.second; 

        piecesPositions[pieceToPlay].first->CalcMoves(x,y, *m_board);

        playerNum ^= 1;
        piecesPositions.clear();
    }
    
}

void Game::initBoard(PiecesContainer& _pieces)
{
    ChessPiece* bPiece = _pieces.getBlackPiece();
    ChessPiece* wPiece = _pieces.getWhitePiece();
    while(bPiece !=0 || wPiece !=0)
    {   
        int y = bPiece->getStartingPosition().first;
        int x = bPiece->getStartingPosition().second;
        m_board->setCell(x,y,bPiece,true);

        y = wPiece->getStartingPosition().first;
        x = wPiece->getStartingPosition().second;

        m_board->setCell(x,y,wPiece,true);
        
        bPiece = _pieces.getBlackPiece();
        wPiece = _pieces.getWhitePiece();
    }
}