#include <iostream>
#include "Board.hpp"
#include "MoveGen.hpp"
int main()
{
    Board board;
    std::vector<Move> allMoves = MoveGen::generateAllMoves(board);
    MoveGen::printAllMoves(allMoves);
    return 0;
}