#include "Board.h"

BOARD Setup(BOARD board) {
        for(int x = 0; x < 8; x++) {
                for(int y = 0; y < 8; y++) {

                        if(y == 1){
                                board.squares[x][y].Type  = "aP";
				board.squares[x][y].color = 0;
				board.squares[x][y].Value = 10;
				board.squares[x][y].Moved = 0;
				board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
				board.squares[x][y].PotentialMoves[i]=-100;
				}
			}

                        else if(y == 6){
                                board.squares[x][y].Type  = "pP";
				board.squares[x][y].color = 1;
				board.squares[x][y].Value = 10;
				board.squares[x][y].Moved = 0;
				board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=-100;
                                }

			}

                        else if((y == 0) && (x == 0 || x == 7)) {
                                board.squares[x][y].Type = "aR";
				board.squares[x][y].color = 0;
				board.squares[x][y].Value = 40;
				board.squares[x][y].Alive = 1;
				for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
                        }

                        else if((y == 7) && (x == 0 || x == 7)) {
                                board.squares[x][y].Type = "pR";
				board.squares[x][y].color = 1;
				board.squares[x][y].Value = 40;
				board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}                        

                        else if((y == 0) && (x == 2 || x == 5)) {
                                board.squares[x][y].Type = "aB";
				board.squares[x][y].color = 0;
				board.squares[x][y].Value = 30;
				board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else if((y == 7) && (x == 2 || x == 5)) {
                                board.squares[x][y].Type = "pB";
				board.squares[x][y].color = 1;
                                board.squares[x][y].Value = 30;
				board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else if((y == 0) && (x == 1 || x == 6)) {
                                board.squares[x][y].Type = "aH";
				board.squares[x][y].color = 0;
                                board.squares[x][y].Value = 20;
				board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else if((y == 7) && (x == 1 || x == 6)) {
                                board.squares[x][y].Type = "pH";
				board.squares[x][y].color = 1;
                                board.squares[x][y].Value = 20;
				board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else if((y == 0) && x == 3) {
                                board.squares[x][y].Type = "aQ";
				board.squares[x][y].color = 0;
                                board.squares[x][y].Value = 50;
                                board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else if((y == 7) && x == 3) {
                                board.squares[x][y].Type = "pQ";
				board.squares[x][y].color = 1;
                                board.squares[x][y].Value = 50;
                                board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else if((y == 0) && x == 4) {
                                board.squares[x][y].Type = "aK";
				board.squares[x][y].color = 0;
                                board.squares[x][y].Value = 600;
                                board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else if((y == 7) && x == 4) {
                                board.squares[x][y].Type = "pK";
				board.squares[x][y].color = 1;
                                board.squares[x][y].Value = 600;
                                board.squares[x][y].Alive = 1;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=(-100);
                                }
			}

                        else {
                                board.squares[x][y].Type = "  ";
				board.squares[x][y].color = 1;
                                board.squares[x][y].Value = 0;
                                board.squares[x][y].Alive = 0;
                        	for(int i=0;i<30;i++){
                                board.squares[x][y].PotentialMoves[i]=-100;
                                }
			}
			board.squares[x][y].PosX = x;
			board.squares[x][y].PosY = y;
			board.squares[x][y].Moved = 0;
			board.squares[x][y].bestmove = -1;
			board.squares[x][y].bestmoveValue = -1;
                }
        }
board.squares[4][3].Value = 3;
board.squares[4][4].Value = 2;
board.squares[3][2].Value = 2;
board.squares[2][2].Value = 1;
board.squares[5][2].Value = 1;
board.squares[3][3].Value = 1;
return board;
}
BOARD SetupBlack(BOARD board) {
	board.squares[3][0].Type = "aK";
	board.squares[4][0].Type = "aQ";
	board.squares[3][7].Type = "pK";
	board.squares[4][7].Type = "pQ";
return board;
}
BOARD CleanPotential(BOARD board){
for(int x = 0;x<8;x++){
	for(int y=0;y<8;y++){
//		if(board.squares[x][y].Alive == 1){
			for(int i=0;i<30;i++)
				board.squares[x][y].PotentialMoves[i]=-100;

//		}
	}
}

return board;

}
