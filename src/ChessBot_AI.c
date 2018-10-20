#include <stdio.h>
#include <stdlib.h>
#include "ChessBot_AI.h"
#include "Move.h"
PIECE BestMoveOnePiece(PIECE piece, BOARD board) {
	int i = 0, value = -1;
	int MoveX = 0, MoveY = 0, point;
/*	for(int i = 0; i < 30; i++)
	printf("%d ", piece.PotentialMoves[i]);
	printf("\n");
*/	for (i = 0; i < 30; i++) {
		if (piece.PotentialMoves[i] >= 0) {
		MoveX = piece.PotentialMoves[i] / 10;
		MoveY = piece.PotentialMoves[i] % 10;
		point = board.squares[MoveX][MoveY].Value;

		if (point > value) {
			value = point;
			piece.bestmove = 10*MoveX + MoveY;
		}
		}
	}	
	piece.bestmoveValue = value;
	return piece;
}

PIECE BestMoveOnePieceAdvanced(PIECE piece, BOARD board, int PKingX,int PKingY,int AIKingX,int AIKingY){
	printf("Potential Move for this is %d  ",piece.PotentialMoves[0]);
	BOARD boardtemp = board;
	int move;
	int value = -100;
	int MoveX = 0, MoveY = 0, point;
	for (int i = 0; i < 30; i++) {
        	boardtemp = board;
	        for (int x = 0; x<8; x++) {
               		 for (int y = 0; y<8; y++) {
                       		 for (int i = 0; i<30; i++){
                         	       boardtemp.squares[x][y].PotentialMoves[i] = -100;
                       		 }
                	}
       		 }

		if (piece.PotentialMoves[i] >= 0) {
                	MoveX = piece.PotentialMoves[i] / 10;
                	MoveY = piece.PotentialMoves[i] % 10;
                	point = board.squares[MoveX][MoveY].Value;
			if(board.squares[MoveX][MoveY].Alive ==1)
			point +=5;
			boardtemp = movepiece(piece.PosX,piece.PosY,MoveX,MoveY,boardtemp);
			boardtemp = move_generate(boardtemp,PKingX,PKingY,AIKingX,AIKingY);
        		for (int x = 0; x<8; x++) {
                		for (int y = 0; y<8; y++) {
                        		boardtemp.squares[x][y] = BestMoveOnePiece(boardtemp.squares[x][y], boardtemp);
                		}
        		}
       			move = BestMoveAllPiece(boardtemp,(piece.color-1)*(piece.color-1));


			point = point + 1 - boardtemp.squares[move/10][move%10].bestmoveValue;	
		
        	        if (point > value) {
                	        value = point;
                        	piece.bestmove = 10*MoveX + MoveY;
                	}
                }
        }
        piece.bestmoveValue = value;
	printf("value;%d for %s\n",value,piece.Type);
return piece;
}

BOARD movepiece(int x1, int y1, int x2, int y2, BOARD board) {
	char* ttype;
	int tcolor, tvalue, talive;

	ttype = board.squares[x1][y1].Type;
	tcolor = board.squares[x1][y1].color;
	tvalue = board.squares[x1][y1].Value;
	talive = board.squares[x1][y1].Alive;

	board.squares[x2][y2].Type = ttype;
	board.squares[x2][y2].color = tcolor;
	board.squares[x2][y2].Value = tvalue;
	board.squares[x2][y2].Alive = talive;
	board.squares[x2][y2].Moved = 1;

	board.squares[x1][y1].Type = "  ";
	board.squares[x1][y1].color = -1;
	board.squares[x1][y1].Value = 0;
	board.squares[x1][y1].Alive = 0;
	board.squares[x1][y1].Moved = 0;

	for (int i = 0; i < 30; i++)
		board.squares[x1][y1].PotentialMoves[i] = -100;

	return board;
}

int BestMoveAllPiece(BOARD board, int color) {
	int point = -100, x = 0, y = 0, best = -100, index_x = 0, index_y =-1;
	/*linearly search through all squares*/
	for(x=0;x<8; x++) {
		for(y = 0; y<8; y++) {
			/*Search for the best move of a current piece*/
			point = board.squares[x][y].bestmoveValue;
			/*If a piece with a better move is found, remember its index.*/
			if(point > best && color == board.squares[x][y].color && board.squares[x][y].Alive == 1) {
				best = point;
				index_x = x;
				index_y = y;
			}
		}
	}
	/*return index of best piece*/
	return (10* index_x + index_y);
}

BOARD move_generate(BOARD board, int PKingX, int PKingY, int AIKingX, int AIKingY){
		  //AI MOVE
		  //generating all moves
//		board = Potential_Tom(board);



		//	SPENCER MOVE GENERATING
		for (int x = 0; x<8; x++) {
			for (int y = 0; y<8; y++) {
				if(strcmp(board.squares[x][y].Type,"aP")==0)
					board.squares[x][y]=Pawn_Potential(board.squares[x][y],board);
				else if(strcmp(board.squares[x][y].Type,"aH")==0)
					board.squares[x][y]=Knight_Potential(board.squares[x][y], board);
				else if(strcmp(board.squares[x][y].Type,"aR")==0)
					board.squares[x][y]=Rook_Potential(board.squares[x][y], board);
				else if (strcmp(board.squares[x][y].Type, "aB") == 0)
					board.squares[x][y] = Bishop_Potential(board.squares[x][y], board);
				else if (strcmp(board.squares[x][y].Type, "aQ") == 0)
					board.squares[x][y] = Queen_Potential(board.squares[x][y], board);
				else if(strcmp(board.squares[x][y].Type,"pP")==0)
                                        board.squares[x][y]=Pawn_Potential(board.squares[x][y],board);
                                else if(strcmp(board.squares[x][y].Type,"pH")==0)
                                        board.squares[x][y]=Knight_Potential(board.squares[x][y], board);
                                else if(strcmp(board.squares[x][y].Type,"pR")==0)
                                        board.squares[x][y]=Rook_Potential(board.squares[x][y], board);
                                else if (strcmp(board.squares[x][y].Type, "pB") == 0)
                                        board.squares[x][y] = Bishop_Potential(board.squares[x][y], board);
                                else if (strcmp(board.squares[x][y].Type, "pQ") == 0)
                                        board.squares[x][y] = Queen_Potential(board.squares[x][y], board);
			}
		}

		board.squares[PKingX][PKingY] = KingMove(board.squares[PKingX][PKingY], board);
		board.squares[AIKingX][AIKingY] = KingMove(board.squares[AIKingX][AIKingY], board);


return board;
}


PIECE Pawn_Potential(PIECE pawn, BOARD board) {
	int one = 1, x, y, pos, index = 0;
	if(pawn.color == 1)
	one = -1;

	/*Check if a two square start is legal*/
	if(pawn.Moved == 0) {
		x = pawn.PosX;
		y = pawn.PosY + one*2;
		pos = 10*x + y;
		if(y > 7 || y < 0)
		pos = -200;
		else if(board.squares[x][y].Alive == 1)
		pos *= -1;
		pawn.PotentialMoves[index] = pos;
		index++;
	}

	/*next check a normal movement*/
	x = pawn.PosX;
	y = pawn.PosY + one;
	pos = 10*x + y;
	/*if a pawn cannot move forward, the move is illegal and assigned a position of -1*/
	if(y > 7 || y < 0)
	pos = -200;
	else if (board.squares[x][y].Alive == 1)
	pos *= -1;
	pawn.PotentialMoves[index] = pos;
	index++;
	
	/*Check an attack to the right*/
	x = pawn.PosX + 1;
	pos = 10*x +y;
	/*If a pawn cannot attack a piece there, the move is illegal an assigned a position of -1*/
	if(x > 7 || x < 0 || y > 7 || y < 0)
	pos = -200;
	else if((board.squares[x][y].color == pawn.color && board.squares[x][y].Alive == 1) || (board.squares[x][y].Alive == 0))
	pos *= -1;
	pawn.PotentialMoves[index] = pos;
        index++;

	/*Check an attack to the left*/
	x = pawn.PosX - 1;
        pos = 10*x +y;
	/*If a pawn cannot attack a piece there, the move is illegal an assigned a position of -1*/
        if(x > 7 || x < 0 || y > 7 || y < 0)
        pos = -200;
        else if((board.squares[x][y].color == pawn.color && board.squares[x][y].Alive == 1) || (board.squares[x][y].Alive == 0))
        pos *= -1;
	pawn.PotentialMoves[index] = pos;
        index++;

	return pawn;
}

PIECE Knight_Potential(PIECE knight, BOARD board) {
	int two = -2, one = 1, x, y, pos;
	/*This loop is to calculate the potential L-moves with the long end vertical*/
	for(int i = 0; i < 4; i++) {
		if((i%2) == 1)
		two *= -1;
		else
		one *= -1;
		
		x = knight.PosX + two;
		y = knight.PosY + one;
		pos = x * 10 + y;
		if(x > 7 || x < 0 || y > 7 || y < 0 )
		pos = -200;
		else if((board.squares[x][y].color == knight.color) && (board.squares[x][y].Alive == 1))
        	pos *= -1;
		
		knight.PotentialMoves[i] = pos;
	}
	/*This loop is to calculate the potential L-moves with the long end horizontal*/
	for(int i = 4; i < 8; i++) {
                if((i%2) == 1)
                two *= -1;
                else
                one *= -1;

                x = knight.PosX + one;
                y = knight.PosY + two;
                pos = x * 10 + y;
		if(x > 7 || x < 0 || y > 7 || y < 0 )
                pos = -200;
                else if((board.squares[x][y].color == knight.color) && (board.squares[x][y].Alive == 1))
                pos *= -1;
                knight.PotentialMoves[i] = pos;
        }
return knight;
}

PIECE Bishop_Potential(PIECE bishop, BOARD board) {
	int x = bishop.PosX, y = bishop.PosY, legal = 1, count = 0;
	/*This loop determines the potential moves upper diagonal right*/
	while(legal) {
		x++;
		y++;
		int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0){
			break;
		}

		if(board.squares[x][y].Alive == 1) {
			if(board.squares[x][y].color == bishop.color) {
                	pos *= -1;}
			legal = 0;
		}

		bishop.PotentialMoves[count] = pos;
		count++;
	}
	/*Reset the x and y values for the potential moves in the other directions*/
	x = bishop.PosX;
	y = bishop.PosY;
	legal = 1;
	/*This loop determines the potential moves upper diagonal left.*/
	while(legal) {
                x--;
                y++;
                int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0){
                        break;
                }

                if(board.squares[x][y].Alive == 1) {
                        if(board.squares[x][y].color == bishop.color) {
                        pos *= -1;}
                        legal = 0;
                }

                bishop.PotentialMoves[count] = pos;
                count++;
        }
	/*reset variables again*/
	x = bishop.PosX;
        y = bishop.PosY;
        legal = 1;
	/*This loop determines the potential moves lower right diagonal.*/
	while(legal) {
                x++;
                y--;
                int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0){
                        break;
                }

                if(board.squares[x][y].Alive == 1) {
                        if(board.squares[x][y].color == bishop.color) {
                        pos *= -1;}
                        legal = 0;
                }

                bishop.PotentialMoves[count] = pos;
                count++;
        }
	/*Reset vaiables again*/
	x = bishop.PosX;
        y = bishop.PosY;
        legal = 1;
	/*This loop determines the potential moves lower left diagonal*/
        while(legal) {
                x--;
                y--;
                int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0){
                        break;
                }

                if(board.squares[x][y].Alive == 1) {
                        if(board.squares[x][y].color == bishop.color) {
                        pos *= -1;}
                        legal = 0;
                }

                bishop.PotentialMoves[count] = pos;
                count++;
        }
	return bishop;
}


PIECE Rook_Potential(PIECE rook, BOARD board) {
        int x = rook.PosX, y = rook.PosY, legal = 1, count=0;
	for(int i = 0; i < 30; i++) {
		if(rook.PotentialMoves[i] == -100)
		break;

		count++;
	}
	/*Basically same stuff as bishop_potential, but this time for horizontal and vertical directions*/
        while(legal) {
                x++;
                int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0) {
			break;
		}
			
		if (board.squares[x][y].Alive == 1) {
                        if(board.squares[x][y].color == rook.color) {
                        pos *= -1;}
                        legal = 0;
                }

                rook.PotentialMoves[count] = pos;
                count++;
        }

        x = rook.PosX;
        y = rook.PosY;
        legal = 1;

	while(legal) {
                x--;
                int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0) {
                        break;
                }

                if (board.squares[x][y].Alive == 1) {
                        if(board.squares[x][y].color == rook.color) {
                        pos *= -1;}
                        legal = 0;
                }

                rook.PotentialMoves[count] = pos;
                count++;
        }

	x = rook.PosX;
        y = rook.PosY;
        legal = 1;

	while(legal) {
                y--;
                int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0) {
                        break;
                }

                if (board.squares[x][y].Alive == 1) {
                        if(board.squares[x][y].color == rook.color) {
                        pos *= -1;}
                        legal = 0;
                }

                rook.PotentialMoves[count] = pos;
                count++;
        }

        x = rook.PosX;
        y = rook.PosY;
        legal = 1;

	while(legal) {
                y++;
                int pos = x * 10 + y;
                if(x > 7 || x < 0 || y > 7 || y < 0) {
                        break;
                }

                if (board.squares[x][y].Alive == 1) {
                        if(board.squares[x][y].color == rook.color) {
                        pos *= -1;}
                        legal = 0;
                }

                rook.PotentialMoves[count] = pos;
                count++;
        }
	return rook;
}

PIECE Queen_Potential(PIECE queen, BOARD board) {
	/*A queen is basically a rook and bishop combined*/
	queen = Bishop_Potential(queen, board);
	queen = Rook_Potential(queen, board);
	
	return queen;
}


BOARD Potential_Tom(BOARD board){
	int valid,counter=0;
	for(int x=0;x<8;x++){
		for(int y=0; y<8;y++){
			if(strcmp(board.squares[x][y].Type,"aP")==0){
				counter=0;
				for(int i=0;i<8;i++){
					for(int j=0;j<8;j++){
						valid = PawnMove(board.squares[x][y],board,i*10+j)-1;
						if(valid == 0){
							board.squares[x][y].PotentialMoves[counter]=i*10+j;
							counter++;
						}
					}
				}
			}
			else if(strcmp(board.squares[x][y].Type,"aR")==0){
				counter = 0;
				for(int i=0;i<8;i++){
                                        for(int j=0;j<8;j++){
                                                valid = RookMove(board.squares[x][y],board,i*10+j)-1;
                                                if(valid == 0){
                                                        board.squares[x][y].PotentialMoves[counter]=i*10+j;
                                                        counter++;
						}
					}
				}
			}
			else if(strcmp(board.squares[x][y].Type,"aH")==0){
                                counter = 0;
                                for(int i=0;i<8;i++){
                                        for(int j=0;j<8;j++){
                                                valid = KnightMove(board.squares[x][y],board,i*10+j)-1;
                                                if(valid == 0){
                                                        board.squares[x][y].PotentialMoves[counter]=i*10+j;
                                                        counter++;			
						}
					}
				}
			}
/* Move.c Bishop and Quessn does not work
 			 else if(strcmp(board.squares[x][y].Type,"aB")==0){
                                counter = 0;
                                for(int i=0;i<8;i++){
                                        for(int j=0;j<8;j++){
                                                valid = BishopMove(board.squares[x][y],board,i*10+j)-1;
                                                if(valid == 0){
                                                        board.squares[x][y].PotentialMoves[counter]=i*10+j;
                                                        counter++;
                                                }
                                        }
                                }
                        }
			else if(strcmp(board.squares[x][y].Type,"aQ")==0){
                                counter = 0;
                                for(int i=0;i<8;i++){
                                        for(int j=0;j<8;j++){
                                                valid = QueenMove(board.squares[x][y],board,i*10+j)-1;
                                                if(valid == 0){
                                                        board.squares[x][y].PotentialMoves[counter]=i*10+j;
                                                        counter++;
                                                }
                                        }
                                }
                        }
*/
		}
	}

return board;


}
