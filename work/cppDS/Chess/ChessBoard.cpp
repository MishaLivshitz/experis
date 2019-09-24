#include "ChessBoard.h"


const char* ChessBoard::s_BLACK_COLOR = "\033[31m";
const char* ChessBoard::s_RESET_COLOR = "\033[0m";


void ChessBoard::print() const
{
    std::cout << "   ";
    for(int k=0; k<8; ++k)
    {
        std::cout << k;
        std::cout << "  ";
    }

    std::cout << std::endl;

    for(int i = 0 ;i<8 ;++i)
    {
        std::cout << "  ";
        for(int k=0; k<8; ++k)
        {
            std::cout << " _ ";
        }

        std::cout << std::endl;
        std::cout << i<< ' ';

        for(int j = 0 ; j<8 ;++j)
        {
            if(0 == m_board[i][j].state())
            {
                std::cout << "|_|";
            }
            else
            {
                if(m_board[i][j].piece()->color() == ChessPiece::BLACK)
                {
                    std::cout << "|" << s_BLACK_COLOR << m_board[i][j].piece()->sign() << s_RESET_COLOR << "|";
                }
                else
                {
                    std::cout << "|" << m_board[i][j].piece()->sign() << "|";
                }
            }
        }

        std::cout << std::endl;
    }
}