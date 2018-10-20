#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

typedef struct board{
	PIECE squares[8][8];
} BOARD;

BOARD Setup(BOARD board);

BOARD SetupBlack(BOARD board);
BOARD CleanPotential(BOARD board);
#endif
