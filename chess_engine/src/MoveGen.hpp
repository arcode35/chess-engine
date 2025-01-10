#pragma once

#include "Board.hpp"
#include <vector>
#include <map>
// This class contains the functions that are required to generate legal moves for each piece.
class MoveGen
{
public:
    static std::vector<Move> generatePawnMoves(const Board &board, int i, int j, bool isWhite);
    static std::vector<Move> generateKnightMoves(const Board &board, int i, int j, bool isWhite);
    static std::vector<Move> generateBishopMoves(const Board &board, int i, int j, bool isWhite);
    static std::vector<Move> generateRookMoves(const Board &board, int i, int j, bool isWhite);
    static std::vector<Move> generateQueenMoves(const Board &board, int i, int j, bool isWhite);
    static std::vector<Move> generateKingMoves(const Board& board, int i, int j, bool isWhite);
    static std::vector<Move> generateAllMoves(const Board& board);
    static void printAllMoves(const std::vector<Move>& allMoves);


};