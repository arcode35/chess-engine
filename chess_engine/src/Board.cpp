#include "Board.hpp"
#include <iostream>
#include <vector>

#define LENGTH 8
#define WIDTH 8

void Board::printBoard()
{
    for (unsigned int i = 0; i < WIDTH; ++i)
    {
        for (unsigned int j = 0; j < LENGTH; ++j)
        {
            std::cout << board[i][j] << ' ';
            if (board[i][j] >= 0)
            {
                std::cout << "  ";
            }
        }
        std::cout << '\n';
    }
}
