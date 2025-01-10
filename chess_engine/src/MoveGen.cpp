#include "MoveGen.hpp"
#include "Board.hpp"
#include <vector>
#include <map>

Square convertXYToSquare(int row, int column)
{
    std::map<int, char> mapping;
    mapping[0] = 'A';
    mapping[1] = 'B';
    mapping[2] = 'C';
    mapping[3] = 'D';
    mapping[4] = 'E';
    mapping[5] = 'F';
    mapping[6] = 'G';
    mapping[7] = 'H';

    return Square(mapping[column], 8 - row);
};

bool isWhitePiece(const Piece &piece)
{
    return (piece == PAWN || piece == KNIGHT || piece == BISHOP ||
            piece == ROOK || piece == QUEEN || piece == KING);
}

std::vector<Move> MoveGen::generatePawnMoves(const Board &board, int i, int j, bool isWhite)
{
    std::vector<Move> pawnMoves;
    Square currentSquare = convertXYToSquare(i, j);

    int startingRow = (isWhite) ? 6 : 1;
    int promotionRow = (isWhite) ? 0 : 7;
    int forwardStep = (isWhite) ? -1 : 1;

    if (i == startingRow && board.board[i + forwardStep * 2][j] == EMPTY && board.board[i + forwardStep][j] == EMPTY)
    {
        Square nextSquare = convertXYToSquare(i + forwardStep * 2, j);
        pawnMoves.push_back(Move(isWhite ? PAWN : PAWN_BLACK, currentSquare, nextSquare, false));
    }

    if (i + forwardStep >= 0 && i + forwardStep < 8 && board.board[i + forwardStep][j] == EMPTY)
    {
        Square nextSquare = convertXYToSquare(i + forwardStep, j);
        // Check for promotion
        if (i + forwardStep == promotionRow)
        {
            pawnMoves.push_back(Move(isWhite ? PAWN : PAWN_BLACK, currentSquare, nextSquare, false, true)); // Indicate promotion
        }
        else
        {
            pawnMoves.push_back(Move(isWhite ? PAWN : PAWN_BLACK, currentSquare, nextSquare, false));
        }
    }

    for (int offset : {-1, 1})
    {
        int newColumn = j + offset;

        if (newColumn >= 0 && newColumn < 8 && i + forwardStep >= 0 && i + forwardStep < 8)
        {
            Piece target = static_cast<Piece>(board.board[i + forwardStep][newColumn]);
            if (target != EMPTY && isWhitePiece(target) != isWhite)
            {
                Square nextSquare = convertXYToSquare(i + forwardStep, newColumn);

                // Check for promotion
                if (i + forwardStep == promotionRow)
                {
                    pawnMoves.push_back(Move(isWhite ? PAWN : PAWN_BLACK, currentSquare, nextSquare, true, true)); // Indicate capture and promotion
                }
                else
                {
                    pawnMoves.push_back(Move(isWhite ? PAWN : PAWN_BLACK, currentSquare, nextSquare, true));
                }
            }
        }
    }

    return pawnMoves;
}

std::vector<Move> MoveGen::generateKnightMoves(const Board &board, int i, int j, bool isWhite)
{
    std::vector<Move> knightMoves;

    static const int knightOffsets[8][2] = {
        {-2, -1}, {-2, 1}, // Two up, one left/right
        {-1, -2},
        {-1, 2}, // One up, two left/right
        {1, -2},
        {1, 2}, // One down, two left/right
        {2, -1},
        {2, 1} // Two down, one left/right
    };

    Square currentSquare = convertXYToSquare(i, j);
    for (const auto &offset : knightOffsets)
    {
        int newRow = i + offset[0];
        int newColumn = j + offset[1];
        if (newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8)
        {
            Square newSquare = convertXYToSquare(newRow, newColumn);
            if (board.board[newRow][newColumn] == EMPTY)
            {
                knightMoves.push_back(Move(isWhite ? KNIGHT : KNIGHT_BLACK, currentSquare, newSquare, false));
            }
            else if (isWhite != isWhitePiece(static_cast<Piece>(board.board[newRow][newColumn])))
            {
                knightMoves.push_back(Move(isWhite ? KNIGHT : KNIGHT_BLACK, currentSquare, newSquare, true));
            }
        }
    }

    return knightMoves;
}
std::vector<Move> MoveGen::generateBishopMoves(const Board &board, int i, int j, bool isWhite)
{
    std::vector<Move> bishopMoves;

    static int bishopOffsets[4][2] = {
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}};

    Square currentSquare = convertXYToSquare(i, j);
    for (const auto &offset : bishopOffsets)
    {
        int newRow = i + offset[0];
        int newColumn = j + offset[1];

        while (newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8)
        {
            Square nextSquare = convertXYToSquare(newRow, newColumn);
            if (board.board[newRow][newColumn] == EMPTY)
            {
                bishopMoves.push_back(Move(isWhite ? BISHOP : BISHOP_BLACK, currentSquare, nextSquare, false));
            }
            else if (isWhite != isWhitePiece(static_cast<Piece>(board.board[newRow][newColumn])))
            {
                bishopMoves.push_back(Move(isWhite ? BISHOP : BISHOP_BLACK, currentSquare, nextSquare, true));
                break;
            }
            else
            {
                break;
            }

            newRow += offset[0];
            newColumn += offset[1];
        }
    }
    return bishopMoves;
}

std::vector<Move> MoveGen::generateRookMoves(const Board &board, int i, int j, bool isWhite)
{
    std::vector<Move> whiteRookMoves;

    static int rookOffsets[4][2] =
        {
            {-1, 0}, // UP
            {1, 0},  // DOWN
            {0, -1}, // LEFT
            {0, 1},  // RIGHT

        };
    Square currentSquare = convertXYToSquare(i, j);

    for (const auto &offset : rookOffsets)
    {
        int newRow = i + offset[0];
        int newColumn = j + offset[1];
        while (newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8)
        {
            Square nextSquare = convertXYToSquare(newRow, newColumn);
            if (board.board[newRow][newColumn] == EMPTY)
            {
                whiteRookMoves.push_back(Move(isWhite ? ROOK : ROOK_BLACK, currentSquare, nextSquare, false));
            }
            else if (isWhite != isWhitePiece(static_cast<Piece>(board.board[newRow][newColumn])))
            {
                whiteRookMoves.push_back(Move(isWhite ? ROOK : ROOK_BLACK, currentSquare, nextSquare, true));
                break;
            }
            else
            {
                break;
            }
            newRow += offset[0];
            newColumn += offset[1];
        }
    }

    return whiteRookMoves;
}
std::vector<Move> MoveGen::generateQueenMoves(const Board &board, int i, int j, bool isWhite)
{
    std::vector<Move> queenMoves;

    static int queenOffsets[8][2] =
        {
            {-1, 0},  // UP
            {1, 0},   // DOWN
            {0, -1},  // LEFT
            {0, 1},   // RIGHT
            {-1, -1}, // LEFT TOP
            {-1, 1},  // RIGHT TOP
            {1, -1},  // LEFT DOWN
            {1, 1}};  // RIGHT DOWN

    Square currentSquare = convertXYToSquare(i, j);

    for (const auto &offset : queenOffsets)
    {
        int newRow = i + offset[0];
        int newColumn = j + offset[1];
        while (newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8)
        {
            Square nextSquare = convertXYToSquare(newRow, newColumn);
            if (board.board[newRow][newColumn] == EMPTY)
            {
                queenMoves.push_back(Move(isWhite ? QUEEN : QUEEN_BLACK, currentSquare, nextSquare, false));
            }
            else if (isWhite != isWhitePiece(static_cast<Piece>(board.board[newRow][newColumn])))
            {
                queenMoves.push_back(Move(isWhite ? QUEEN : QUEEN_BLACK, currentSquare, nextSquare, true));
                break;
            }
            else
            {
                break; // If we encounter another white piece.
            }
            newRow += offset[0];
            newColumn += offset[1];
        }
    }
    return queenMoves;
}
std::vector<Move> MoveGen::generateKingMoves(const Board& board, int i, int j, bool isWhite)
{
    std::vector<Move> kingMoves;

    // Define all possible king moves
    static const int kingOffsets[8][2] = {
        {-1,  0}, // UP
        { 1,  0}, // DOWN
        { 0, -1}, // LEFT
        { 0,  1}, // RIGHT
        {-1, -1}, // TOP LEFT
        {-1,  1}, // TOP RIGHT
        { 1, -1}, // BOTTOM LEFT
        { 1,  1}  // BOTTOM RIGHT
    };

    Square currentSquare = convertXYToSquare(i, j);

    for (const auto& offset : kingOffsets)
    {
        int newRow = i + offset[0];
        int newColumn = j + offset[1];

        if (newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8)
        {
            Square nextSquare = convertXYToSquare(newRow, newColumn);

            if (board.board[newRow][newColumn] == EMPTY)
            {
                kingMoves.push_back(Move(isWhite ? KING : KING_BLACK, currentSquare, nextSquare, false));
            }
            else if (isWhite != isWhitePiece(static_cast<Piece>(board.board[newRow][newColumn])))
            {
                kingMoves.push_back(Move(isWhite ? KING : KING_BLACK, currentSquare, nextSquare, true));
            }
        }
    }

    return kingMoves;
}


std::vector<Move> MoveGen::generateAllMoves(const Board& board)
{
    std::vector<Move> allMoves;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Piece piece = static_cast<Piece>(board.board[i][j]); 

            switch (piece)
            {
            case PAWN:
            {
                std::vector<Move> whitePawnMoves = generatePawnMoves(board, i, j, true);
                allMoves.insert(allMoves.end(), whitePawnMoves.begin(), whitePawnMoves.end());
                break;
            }
            case PAWN_BLACK:
            {
                std::vector<Move> blackPawnMoves = generatePawnMoves(board, i, j, false);
                allMoves.insert(allMoves.end(), blackPawnMoves.begin(), blackPawnMoves.end());
                break;
            }
            case KNIGHT:
            {
                std::vector<Move> whiteKnightMoves = generateKnightMoves(board, i, j, true);
                allMoves.insert(allMoves.end(), whiteKnightMoves.begin(), whiteKnightMoves.end());
                break;
            }
            case KNIGHT_BLACK:
            {
                std::vector<Move> blackKnightMoves = generateKnightMoves(board, i, j, false);
                allMoves.insert(allMoves.end(), blackKnightMoves.begin(), blackKnightMoves.end());
                break;
            }
            case BISHOP:
            {
                std::vector<Move> whiteBishopMoves = generateBishopMoves(board, i, j, true);
                allMoves.insert(allMoves.end(), whiteBishopMoves.begin(), whiteBishopMoves.end());
                break;
            }
            case BISHOP_BLACK:
            {
                std::vector<Move> blackBishopMoves = generateBishopMoves(board, i, j, false);
                allMoves.insert(allMoves.end(), blackBishopMoves.begin(), blackBishopMoves.end());
                break;
            }
            case ROOK:
            {
                std::vector<Move> whiteRookMoves = generateRookMoves(board, i, j, true);
                allMoves.insert(allMoves.end(), whiteRookMoves.begin(), whiteRookMoves.end());
                break;
            }
            case ROOK_BLACK:
            {
                std::vector<Move> blackRookMoves = generateRookMoves(board, i, j, false);
                allMoves.insert(allMoves.end(), blackRookMoves.begin(), blackRookMoves.end());
                break;
            }
            case QUEEN:
            {
                std::vector<Move> whiteQueenMoves = generateQueenMoves(board, i, j, true);
                allMoves.insert(allMoves.end(), whiteQueenMoves.begin(), whiteQueenMoves.end());
                break;
            }
            case QUEEN_BLACK:
            {
                std::vector<Move> blackQueenMoves = generateQueenMoves(board, i, j, false);
                allMoves.insert(allMoves.end(), blackQueenMoves.begin(), blackQueenMoves.end());
                break;
            }
            case KING:
            {
                std::vector<Move> kingMoves = generateKingMoves(board, i, j, true);
                allMoves.insert(allMoves.end(), kingMoves.begin(), kingMoves.end());
                break;
            }
            case KING_BLACK:
            {
                std::vector<Move> blackKingMoves = generateKingMoves(board, i, j, false);
                allMoves.insert(allMoves.end(), blackKingMoves.begin(), blackKingMoves.end());
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }

    return allMoves;
}
void MoveGen::printAllMoves(const std::vector<Move>& allMoves)
{
    for (const auto& move : allMoves)
    {
        std::cout << move.toString() << '\n';
    }
}
