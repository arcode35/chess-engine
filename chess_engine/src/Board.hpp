#pragma once

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
struct Square
{
    char letter;  // File (column) represented as a letter (e.g., 'a', 'b', etc.)
    int number;   // Rank (row) represented as an integer (e.g., 1, 2, etc.)

    // Default constructor
    Square() : letter('Z'), number(10) {}

    // Parameterized constructor
    Square(char letter, int number) : letter(letter), number(number) {}

    // toString method
    std::string toString() const
    {
        return std::string(1, letter) + std::to_string(number);
    }
};


enum Piece
{
    EMPTY = '.',
    PAWN = 'P',
    KNIGHT = 'N',
    BISHOP = 'B',
    ROOK = 'R',
    QUEEN = 'Q',
    KING = 'K',
    PAWN_BLACK = 'p',
    KNIGHT_BLACK = 'n',
    BISHOP_BLACK = 'b',
    ROOK_BLACK = 'r',
    QUEEN_BLACK = 'q',
    KING_BLACK = 'k'
};
struct Move
{
    Piece piece;
    Square currentSquare;
    Square nextSquare;
    bool isCapture;
    bool isPromotion;

    Move(Piece piece, Square currentSquare, Square nextSquare, bool isCapture, bool isPromotion = false)
        : piece(piece), currentSquare(currentSquare), nextSquare(nextSquare), isCapture(isCapture), isPromotion(isPromotion) {}

    // toString method
    std::string toString() const
    {
        std::string result;

        // Add the piece type
        switch (piece)
        {
        case PAWN:
        case PAWN_BLACK:
            result += "Pawn";
            break;
        case KNIGHT:
        case KNIGHT_BLACK:
            result += "Knight";
            break;
        case BISHOP:
        case BISHOP_BLACK:
            result += "Bishop";
            break;
        case ROOK:
        case ROOK_BLACK:
            result += "Rook";
            break;
        case QUEEN:
        case QUEEN_BLACK:
            result += "Queen";
            break;
        case KING:
        case KING_BLACK:
            result += "King";
            break;
        default:
            result += "Unknown";
            break;
        }

        // Add the move details
        result += " " + currentSquare.toString() + " -> " + nextSquare.toString();

        // Add flags for capture and promotion
        if (isCapture)
        {
            result += " (Capture)";
        }
        if (isPromotion)
        {
            result += " (Promotion)";
        }

        return result;
    }
};

class Board
{
public:
    char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // Black pieces
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // Black pawns
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // Empty spaces
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // White pawns
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // White pieces
    };

    std::vector<Move> moves;
    void generateMoves(int x, int y);
    void printBoard();
    void printMoves();
};

#endif