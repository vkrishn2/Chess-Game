#include "Board.h"
#include "Piece.h"
#include <math.h>

#ifndef MOVE_H
#define MOVE_H

int CheckIfInvalid(PIECE piece, int destination);
int Castling(PIECE king, BOARD board, int destination);
int EnPassant(PIECE pawn, BOARD board, int destination);
int Promotion(PIECE pawn, BOARD board, int destination);
int PawnMove(PIECE pawn, BOARD board, int destination);
int RookMove(PIECE rook, BOARD board, int destination);
int KnightMove(PIECE knight, BOARD board, int destination);
int BishopMove(PIECE bishop, BOARD board, int destination);
int QueenMove(PIECE queen, BOARD board, int destination);
PIECE KingMove(PIECE king, BOARD board);
#endif
