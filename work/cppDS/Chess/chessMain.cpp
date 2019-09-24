


#include "Game.h"
#include "PiecesContainer.h"
#include "ChessBoard.h"
#include "Player.h"

int main()
{
    ChessBoard b;
    Player p1("Michael", ChessPiece::WHITE);
    Player p2("David", ChessPiece::BLACK);
    Game g(&b, &p1, &p2);
    PiecesContainer p;
    p.createPieces();
    g.startGame(p);

    b.print();

    /* ChessPiece* t = b.getCell(3,1).piece();

    vector<pair<int,int> > moves = t->CalcMoves(3,1,b);

    b.setCell(3, 1, 0 ,false);
    b.setCell(moves[0].first, moves[0].second, t ,true);

    moves = t->CalcMoves(3,2,b);

    b.setCell(3, 2, 0 ,false);
    b.setCell(moves[0].first, moves[0].second, t ,true);

    b.print(); */

    return 0;
}