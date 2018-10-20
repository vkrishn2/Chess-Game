#ifndef CHESSAI_H
#define CHESSAI_H
#include "Piece.h"
#include "Board.h"
#include "Move.h"
#include <string.h>
PIECE BestMoveOnePiece(PIECE piece, BOARD board);

PIECE BestMoveOnePieceAdvanced(PIECE piece, BOARD board, int PKingX, int PKingY, int AIKingX, int AIKingY);

BOARD move_generate(BOARD board, int PKingX, int PKingY, int AIKingX, int AIKingY);

int BestMoveAllPiece(BOARD board, int color);

BOARD movepiece(int x1, int y1, int x2, int y2, BOARD board);

PIECE Pawn_Potential(PIECE pawn, BOARD board);

PIECE Knight_Potential(PIECE knight, BOARD board);

PIECE Bishop_Potential(PIECE bishop, BOARD board);

PIECE Rook_Potential(PIECE rook, BOARD board);

PIECE Queen_Potential(PIECE queen, BOARD board);

BOARD Potential_Tom(BOARD board);
#endif
