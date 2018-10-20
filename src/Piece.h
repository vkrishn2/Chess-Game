#ifndef PIECE_H
#define PIECE_H

/*Ai always has a color of 0. Player always has color of 1*/
typedef struct piece {
        int color;
        char* Type;
	int Value;
	int PosX;
	int PosY;
	int Alive;
	int Moved;
	int PotentialMoves[30];
	//this 2 variables is for AI, ignore
	int bestmove;
	int bestmoveValue;
} PIECE;

#endif

