#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "ChessBot_AI.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GUI.h"

void print_board(BOARD boardi, int Player_Color);

int CheckValid(int origx, int origy, int newx, int newy, int destination, BOARD board,int PKingX,int PKingY,int AIKingX, int AIKingY);

int Check(BOARD board, int PKingX, int PKingY, int AIKingX, int AIKingY, int AIX2,int AIY2,int newx, int newy);

int translate(char c, int Player_Color);

char char_translate(int x, int Player_Color);

int main() {
	GUI gui;
	int color_gui;

	int TWOCHECKSP=0,TWOCHECKSAI=0, origx=-1, origy=-1, newx=-1, newy=-1, input1Y, input2Y, valid, skipFirstMove = -1, Player_Color;
	char input1X, input2X;
	int exit_cond = 0;
	int PKingX = 4, PKingY = 7;
	int AIKingX = 4, AIKingY = 0;
	BOARD board;
	int AIMove, AIX, AIY, AIX2, AIY2;

	FILE *f = fopen("log.txt", "w");
	if (f == NULL) {
		printf("ERROR OPENING FILE!\n");
		exit(1);
	}

	printf("Welcome to Chessbot! Type z9 while playing to quit\n");
	printf("Choose a side 0:White  1:Black  :");
	
	skipFirstMove = Gui_Get_Color();
	color_gui = skipFirstMove;

	if(skipFirstMove == -1){	
	scanf("%d", &skipFirstMove);
	}
	Player_Color = (skipFirstMove-1)*(skipFirstMove-1);
	board = Setup(board);
	if (skipFirstMove == 1) {
		board = SetupBlack(board);
		PKingX = 3;
		AIKingX = 3;

	}

	print_board(board, Player_Color);
	gui = Display(board,1,color_gui);


	while (exit_cond == 0) {
		if (skipFirstMove == 0) {
			gui = Display(board,0,color_gui);

			if(gui.exit ==1)
			break;

			origx = gui.srcx;
			origy = gui.srcy;
			newx = gui.targetx;
			newy = gui.targety;
			printf("newy is %d\n",newy);
			if(origx==-1||origy==-1||newx==-1||newy==-1){
			printf("Player Type in location of the piece you want to move (use lowercase letters) \n");
			scanf(" %c%d", &input1X, &input1Y);
			if(input1X == 'z')
			break;
			printf("Where do you want to move it to? \n");
			scanf(" %c%d", &input2X, &input2Y);
			
			//input z9 to quit

			if (input1X == 'z' || input2X == 'z')
				break;

			origx = translate(input1X, Player_Color);
			origy = (Player_Color == 1)? input1Y-1 : 8 - input1Y;
			newx = translate(input2X, Player_Color);
			newy = (Player_Color == 1)? input2Y-1 : 8 - input2Y;
			}


			int destination = newx * 10 + newy;
			//checks valid move
			
			valid = CheckValid(origx, origy, newx, newy, destination, board, PKingX,PKingY,AIKingX,AIKingY);


			//not complete castle
			if((strcmp(board.squares[origx][origy].Type,"pK") == 0) && (abs(newx - origx) == 2) && (valid == 0)){
				if(newx - origx == -2){
					board = movepiece(0,7,newx + 1, 7, board);
					//board.squares[0][7].PosX = newx + 1;
				}
				if(newx - origx == 2){
					board = movepiece(7,7,newx - 1,7, board);
					//board.squares[7][7].PosX = newx - 1;
				}
			}
			if (valid != 0) {
				printf("Not Valid Move\n");
				continue;
			}
			//assuming format is given like this "1133" meaning pos 11 goes to pos 33
			board = movepiece(origx, origy, newx, newy, board);
			if (origx == PKingX && origy == PKingY) {
				PKingX = newx;
				PKingY = newy;
			}

			print_board(board, Player_Color);
			gui = Display(board,1,color_gui);				

		} //for the skipfirstmove if statement




		  //AI MOVE
		  //generating all moves

		board = move_generate(board, PKingX, PKingY, AIKingX, AIKingY);

		for (int x = 0; x<8; x++) {
			for (int y = 0; y<8; y++) {
				if (board.squares[x][y].color == 0 && board.squares[x][y].Alive == 1)
					board.squares[x][y] = BestMoveOnePieceAdvanced(board.squares[x][y], board,PKingX,PKingY,AIKingX,AIKingY);
			}
		}


		AIMove = BestMoveAllPiece(board, 0);


		AIX = AIMove / 10;
		AIY = AIMove % 10;
		AIX2 = board.squares[AIX][AIY].bestmove / 10;
		AIY2 = board.squares[AIX][AIY].bestmove % 10;


		board = movepiece(AIX, AIY, AIX2, AIY2, board);
		print_board(board, Player_Color);
		gui = Display(board,1,color_gui);
		
		if(AIX == AIKingX && AIY == AIKingY){
			AIKingX = AIX2;
			AIKingY = AIY2;
		}

		if(skipFirstMove == 0){
		if(Check(board,PKingX,PKingY,AIKingX,AIKingY,AIX2,AIY2,newx,newy)==1){
			TWOCHECKSP +=1;
			printf("Player: Check!\n");
			fprintf(f,"Player: Check!\n");
		}else 
		TWOCHECKSP = 0;
		if(Check(board,PKingX,PKingY,AIKingX,AIKingY,AIX2,AIY2,newx,newy)==2){
			TWOCHECKSAI +=1 ;
			printf("AI: Check!\n");
			fprintf(f,"AI: Check!\n");
		}else
		TWOCHECKSAI =0;
		
		if(TWOCHECKSP == 2){
			printf("PLAYER CHECK MATE, AI WON!!!\n");
			fprintf(f,"PLAYER CHECK MATE, AI WON!!!\n");
			break;
		}
		if(TWOCHECKSAI == 2){
			printf("AI CHECK MATE, PLAYER WON!!!\n");
                        fprintf(f,"AI CHECK MATE, PLAYER WON!!!\n");
			break;

		}	
		}
		//	RESET POTENTIAL MOVES
		for (int x = 0; x<8; x++) {
			for (int y = 0; y<8; y++) {
				//printf("bestmove for %d is %d\n",x*10+y,board.squares[x][y].bestmove);
				//printf("bestmove Value %d\n",board.squares[x][y].bestmoveValue);
				for (int i = 0; i<30; i++) {
					board.squares[x][y].PotentialMoves[i] = -100;
				}
			}
		}


		//	LOG SAVING
		/*First translate the AI moves to the board coordinates*/
		char input1X = char_translate(origx,Player_Color);
		int input1Y = (Player_Color ==1? origy+1:8-origy);
		char input2X = char_translate(newx,Player_Color);
		int input2Y = (Player_Color ==1)? newy+1:8-newy;
		char x1 = char_translate(AIX, Player_Color);
		int y1 = (Player_Color == 1)? AIY+1 : 8-AIY;
		char x2 = char_translate(AIX2, Player_Color);
		int y2 = (Player_Color == 1)? AIY2+1 : 8-AIY2;
		if (skipFirstMove == 0)
			printf("Player Moved %c%d to %c%d, AI moved %c%d to %c%d\n", input1X, input1Y, input2X, input2Y, x1, y1, x2, y2);
		if (skipFirstMove == 0)
			fprintf(f, "Player Moved %c%d to %c%d, AI Moved %c%d to %c%d.\n", input1X, input1Y, input2X, input2Y, x1, y1, x2, y2);
		if (skipFirstMove == 1)
			fprintf(f, "Player chose Black, AI moved %c%d to %c%d.\n", x1, y1, x2, y2);

		skipFirstMove = 0;
	}



	fclose(f);
	return 0;
}














void print_board(BOARD board, int Player_Color) {
	if(Player_Color == 1) {
	for (int i = 0; i < 8; i++) {
		printf("         |        |        |        |        |        |        |        \n");
		printf("%d   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   \n", i+1, board.squares[0][i].Type, board.squares[1][i].Type, board.squares[2][i].Type, board.squares[3][i].Type, board.squares[4][i].Type, board.squares[5][i].Type, board.squares[6][i].Type, board.squares[7][i].Type);
		if (i != 7)
			printf("--------------------------------------------------------------------------\n");
	}

	printf("    A    |   B    |   C    |   D    |   E    |   F    |   G    |   H    \n\n\n\n");
	}
	else {
	for (int i = 0; i < 8; i++) {
                printf("         |        |        |        |        |        |        |        \n");
                printf("%d   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   |   %s   \n", 8-i, board.squares[0][i].Type, board.squares[1][i].Type, board.squares[2][i].Type, board.squares[3][i].Type, board.squares[4][i].Type, board.squares[5][i].Type, board.squares[6][i].Type, board.squares[7][i].Type);
                if (i != 7)
                        printf("--------------------------------------------------------------------------\n");
        }

        printf("    H    |   G    |   F    |   E    |   D    |   C    |   B    |   A    \n\n\n\n");
        }

}





int CheckValid(int origx, int origy, int newx, int newy, int destination, BOARD board, int PKingX,int PKingY,int AIKingX,int AIKingY) {
	int valid = 1;
	//checks valid move
	valid = (origx>7 || origy>7 || newx>7 || newy>7) ? 1 : (origx<0 || origy<0 || newx<0 || newy<0) ? 1 : 0;
	//printf("valid %d\n",valid);
	if (valid != 0) {
		printf("NOT VALID MOVE\n");
		return 1;
	}
	if (strcmp(board.squares[origx][origy].Type, "pP") == 0)
	{
		valid = PawnMove(board.squares[origx][origy], board, destination) - 1;
		//printf("pawn valid %d\n",valid);
	}
	else if (strcmp(board.squares[origx][origy].Type, "pR") == 0)
	{
		valid = RookMove(board.squares[origx][origy], board, destination) - 1;
		//printf("rook valid %d\n",valid);
	}
	else if (strcmp(board.squares[origx][origy].Type, "pH") == 0)
	{
		valid = KnightMove(board.squares[origx][origy], board, destination) - 1;
		//printf("knight valid %d\n",valid);
		//
		//Move.c Bishop and Queen does not work
		//
		/*}else if(strcmp(board.squares[origx][origy].Type,"pB")==0)
		{valid = BishopMove(board.squares[origx][origy], board, destination)-1;
		//printf("bishop valid %d\n",valid);
		}else if(strcmp(board.squares[origx][origy].Type,"pQ")==0)
		{valid = QueenMove(board.squares[origx][origy], board, destination)-1;
		//printf("queen valid %d\n",valid);
		}else if(strcmp(board.squares[origx][origy].Type,"pK")==0){
		board.squares[origx][origy]= KingMove(board.squares[origx][origy], board);
		valid = -1;
		for(int i=0;i<30;i++){
		if(destination == board.squares[origx][origy].PotentialMoves[i])
		valid = 0;
		}
		}else
		valid = 1;
		*/

		//SPENCER VALID
		/*if(strcmp(board.squares[origx][origy].Type,"pP")==0){
		board.squares[origx][origy] = Pawn_Potential(board.squares[origx][origy],board);
		valid = -1;
		for(int i=0;i<30;i++){
		if(destination == board.squares[origx][origy].PotentialMoves[i])
		valid = 0;
		}
		}else if(strcmp(board.squares[origx][origy].Type,"pH")==0){
		board.squares[origx][origy] = Knight_Potential(board.squares[origx][origy],board);
		valid = -1;
		for(int i=0;i<30;i++){
		if(destination == board.squares[origx][origy].PotentialMoves[i])
		valid = 0;
		}
		}else if(strcmp(board.squares[origx][origy].Type,"pR")==0){
		board.squares[origx][origy] = Rook_Potential(board.squares[origx][origy],board);
		valid = -1;
		for(int i=0;i<30;i++){
		if(destination == board.squares[origx][origy].PotentialMoves[i])
		valid = 0;
		}
		*/
		// Working Bishop and Queen
	}
	else if (strcmp(board.squares[origx][origy].Type, "pB") == 0) {
		board.squares[origx][origy] = Bishop_Potential(board.squares[origx][origy], board);
		valid = -1;
		for (int i = 0; i<30; i++) {
			if (destination == board.squares[origx][origy].PotentialMoves[i])
				valid = 0;
		}
	}
	else if (strcmp(board.squares[origx][origy].Type, "pQ") == 0) {
		board.squares[origx][origy] = Queen_Potential(board.squares[origx][origy], board);
		valid = -1;
		for (int i = 0; i<30; i++) {
			if (destination == board.squares[origx][origy].PotentialMoves[i])
				valid = 0;
		}
	}
	else if (strcmp(board.squares[origx][origy].Type, "pK") == 0) {
		board = move_generate(board, PKingX,PKingY,AIKingX,AIKingY);
		valid = -1;
		for (int i = 0; i<30; i++) {
			if (destination == board.squares[PKingX][PKingY].PotentialMoves[i])
				valid = 0;
		}
		if( abs(newx - origx) == 2){
			valid = Castling(board.squares[origx][origy], board, destination); 
			/*if(valid == 0){
				if(newx - origx == -2){
					board = movepiece(0,7,newx + 1, 7, board);
					//board.squares[0][7].PosX = newx + 1;
				}
				if(newx - origx == 2){
					board = movepiece(7,7,newx - 1,7, board);
					//board.squares[7][7].PosX = newx - 1;
				}
			} */	
		}
	}
	else {
		valid = 1;
	}

	return valid;
}


int Check(BOARD board, int PKingX, int PKingY, int AIKingX, int AIKingY, int AIX2,int AIY2,int newx, int newy){
int check = 0;
BOARD boardtemp = board;
for (int x = 0; x<8; x++) {
	for (int y = 0; y<8; y++) {
		for (int i = 0; i<30; i++){
			boardtemp.squares[x][y].PotentialMoves[i] = -100;
                }
	}
}
boardtemp = move_generate(boardtemp, PKingX, PKingY, AIKingX, AIKingY);
for(int i = 0;i<30;i++){
	//printf("Potential Moves for %d%d is: %d\n",AIX2,AIY2,boardtemp.squares[AIX2][AIY2].PotentialMoves[i]);
	if((PKingX*10+PKingY) == boardtemp.squares[AIX2][AIY2].PotentialMoves[i]){
		check =  1;
		break;
	}
	if((AIKingX*10+AIKingY) == boardtemp.squares[newx][newy].PotentialMoves[i]){
		check =  2;
		break;
	}
}
return check;
}




int translate( char c, int Player_Color){
	int i;
	switch(c) {
	case 'a': i = 0;
		  break;
	case 'b': i = 1;
                  break;
	case 'c': i = 2;
		  break;
	case 'd': i = 3;
                  break;
	case 'e': i = 4;
                  break;
	case 'f': i = 5;
                  break;
	case 'g': i = 6;
                  break;
	case 'h': i = 7;
                  break;
	}
	if(Player_Color == 1) {
		return i;
	}
	else {
		return 7 - i;
	}
}

char char_translate(int x, int Player_Color) {
	char c;
	if(Player_Color == 1) {
		switch(x) {
		case 0: c = 'A';
			break;
		case 1: c = 'B';
                        break;
		case 2: c = 'C';
                        break;
		case 3: c = 'D';
                        break;
		case 4: c = 'E';
                        break;
		case 5: c = 'F';
                        break;
		case 6: c = 'G';
                        break;
		case 7: c = 'H';
			break;
		}
	}
	else {
		switch(x) {
                case 0: c = 'H';
                        break;
                case 1: c = 'G';
                        break;
                case 2: c = 'F';
                        break;
                case 3: c = 'E';
                        break;
                case 4: c = 'D';
                        break;
                case 5: c = 'C';
                        break;
                case 6: c = 'B';
                        break;
                case 7: c = 'A';
                        break;
                }
	}
	return c;
}
