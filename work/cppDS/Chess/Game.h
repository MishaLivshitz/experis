#ifndef GAME_H
#define GAME_H

#include "ChessBoard.h"
#include "PiecesContainer.h"
#include "Player.h"

class Game
{
public:

    Game(ChessBoard* _board ,Player const* _player1,Player const* _player2);
    void startGame(PiecesContainer& _pieces);
    void playMove(int _playerNum);

private:
    void displayPlayersPieces(vector<pair<ChessPiece*, pair<int,int> > > const&) const;
    void initBoard(PiecesContainer& _pieces);

private:
    Player const* m_players[2];  
    ChessBoard* m_board;

};


#endif
