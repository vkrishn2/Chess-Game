#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* Checks if the Move is Invalid */
int CheckIfInvalid(PIECE piece, int destination){ 
     int t;
     int newx = destination /10;
     int newy = destination % 10;
     int x = piece.PosX;
     int y = piece.PosY;
     /* Prevents out of bound moves */
     if(0>destination || 77 < destination){
                t = 0;/*invalid*/
        }
     /* Typing a spot that the piece is already standing at is an invalid input */
     else if(newx == x && newy == y){
                t = 0;
        }
     else{
          t = 1;
     }
     return t;
}

int Castling(PIECE king, BOARD board, int destination){
     /* Prevents out of bound moves */
     //int t, check;
     int x = king.PosX;
     int y = king.PosY;
    int originalPos = 10*x + y;
    int DestinationX = destination/10;
    

     int RookX = (DestinationX - x > 0)? 7 : 0;  //need to know the rook in question
        //If DestinationX > 0, then the rook must be on the right side of the board.
    int RookY = y;  //Rook should be at the same y position
     if(king.Moved != 0){
        return 0;   //If kingmoved, the move is illegal.
    }
    if(board.squares[RookX][RookY].Value != 6 || board.squares[RookX][RookY].Alive != 1 || board.squares[RookX][RookY].Moved != 0 || board.squares[RookX][RookY].color != king.color) {
        return 0;  //Check if there is actually a rook that hasnt moved yet.
    }

int Direction = DestinationX - x;
Direction = (Direction > 0)? 10 : -10;  //Direction can only be in the x direction
destination = originalPos + Direction;  //We will check every square in the direction
    
for(int x = 0; x < 8; x++) {
    for(int y = 0; y < 8; y++) {
        for(int i = 0; i < 30; i++){
            if(board.squares[x][y].PotentialMoves[i] == destination || board.squares[x][y].Alive == 1)
            {
                return 0;
            }
        }
    }
}
destination += Direction;  //Move on to next sqaure;

for(int x = 0; x < 8; x++) {
    for(int y = 0; y < 8; y++) {
        for(int i = 0; i < 30; i++){
            if(board.squares[x][y].PotentialMoves[i] == destination || board.squares[x][y].Alive == 1)
            {
                return 0;
            }
        }
    }
}
//Lastly, check if king is actually in check
destination = originalPos;
for(int x = 0; x < 8; x++) {
    for(int y = 0; y < 8; y++) {
        for(int i = 0; i < 30; i++){
            if(board.squares[x][y].PotentialMoves[i] == destination || board.squares[x][y].Alive == 1)
            {
                return 0;
            }
        }
    }
}

return 1;  //only returned if move was detected to not be legal. 
}

int PawnMove(PIECE pawn, BOARD board, int destination){
     int t, check;
     int x = pawn.PosX;
     int y = pawn.PosY;
     int newx = destination / 10;
     int newy = destination % 10;
     int counter;
     counter = newy - y;
     int dy = abs(counter);
     if(y == 1 && newx == x && pawn.color == 0 && dy == 2){/*special case where pawn moves two spaces forward*/
          if(newy == 3){/*if two spaces, good*/
               t = 1; /*valid*/
          }/*fi*/
     }/*fi*/
     else if(y == 6 && newx == x && pawn.color == 1 && dy == 2){/* same but for the bottom pawn*/
          if(newy == 4){
               t = 1; /*valid*/
          }/*fi*/
     }/*esle fi*/
        /*if(newy == 7){
                printf("Type in the promotion you'd like your pawn to have? (Rook, Bishop, Knight, or Queen");
                scanf("%s", &NewType);
                pawn.Type = NewType;
        }
        if(newy == 0){
                printf("Type in the promotion you'd like your pawn to have? (Rook, Bishop, Knight, or Queen");
                scanf("%s", &NewType);
                pawn.Type = NewType;
        }*/
     
     else if(newx != x && pawn.color == 0){ /*top pawn special cases*/
          if((abs(newx - x)) != 1){/* if pawn moved more than 1 space to the right or left it's no good */
               t = 0; /*invalid*/
          }/*fi*/
          else if(counter == 1 && board.squares[newx][newy].Alive == 1 && board.squares[newx][newy].color != pawn.color){ /*top pawn eating an enemy is okay*/
               t = 1; /*valid*/      
          }/*esle fi*/
          else if(counter == 1 && board.squares[newx][newy].Alive == 0 && board.squares[newx][y].color != pawn.color && board.squares[newx][y].Alive == 1){/*top pawn doing EnPassant*/
                        t = 1; /*valid*/
                }/*esle fi*/
	  else{/* anything else is not fine*/
		t = 0;
	  }/*esle*/

     }/*esle fi*/
     else if(newx != x && pawn.color == 1){/*bottom pawn special cases*/
          if(abs(newx - x) != 1){/* if pawn moved more than 1 space to the right or left it's no good */
		t = 0; /*invalid*/
                }/*fi*/

          else if(counter == -1 && board.squares[newx][newy].Alive == 1 && board.squares[newx][newy].color != pawn.color){ /*bottom pawn eating enemy*/
               t = 1; /*valid*/
          }/*esle fi*/
          else if(counter == -1 && board.squares[newx][newy].Alive == 0 && board.squares[newx][y].color != pawn.color && board.squares[newx][y].Alive == 1){/*bottom pawn doing EnPassant*/
               t = 1; /*valid*/
          }/*esle fi*/
	  else{
		t = 0;
	  }/*esle*/
     }/*esle fi*/
     else if(newx == x && counter == 1 && pawn.color == 0){ /*make sure pawn moves one space forward for the top pawn*/
          t = 1; /*valid*/
     }/*esle fi*/
     else if(newx == x && counter == -1 && pawn.color == 1){/*make sure pawn moves one space forward for the bottom pawn*/
          t = 1; /*valid*/
     }/*esle fi*/
     else{ /*case where if the pawn moved left or right it's invalid because it did not either capture an enemy or do enpassant*/
          t = 0; /*invalid*/
     }/*esle*/
     if((dy) == 2 && board.squares[newx][newy].Alive == 0){/*if pawn moved two spaces*/
		if(counter == 2 && board.squares[x][y+1].Alive == 1){/*check that no one in between is alice*/
			t = 0;
		}/*fi*/
		else if(counter == -2 && board.squares[x][y-1].Alive == 1){/*same check but for the other pawn*/
			t = 0;
		}/*esle fi*/
	}/*fi*/
     else if(board.squares[newx][newy].Alive == 1 && newx == x){/*ifpawn tries to move forward and ANYONE is in front, invalid*/
		t = 0;
     }/*esle fi*/
     check = CheckIfInvalid(pawn, destination);
     if(check == 0){
          return check;
     }/*fi*/

     return t;
}/*end of pawnmove*/


int RookMove(PIECE rook, BOARD board, int destination){
     	int check, t;
        int x = rook.PosX;
        int y = rook.PosY;

     int newx = destination / 10;
     int newy = destination % 10;
     int counter;
     t = -1;
     if(newx != x){   /* if rook changes in x direction */
          counter = newx - x;

          if(newy == y){   /*makes sure rook did not change in y direction*/
               for(int i=1;counter > 1;counter--){   /*loop to check that no pieces are inbetween old spot and new spot*/
                    
                    if(board.squares[x+i][y].Alive == 1){ /*sees if the square has someone alive*/
                         
                         t = 0; /*invlaid*/
                    }/*fi*/
                    i++; 
               }/*rof*/
               for(int i=1;counter < -1;counter++){ /*secondary loop in the case that counter is negative bc the newx is to the left rather than the right*/

                                if(board.squares[x-i][y].Alive == 1){ /*loop to check it's alive*/
                                        t = 0; /*invlaid*/
                                }/*fi*/
                                i++;
                        }/*rof*/
	       if(t == 0){ /* if t is not equal to 0, then it passed the for loop above without running into invlaid*/
		    t = 0;/* invalid*/
	       }/*fi*/
               else if(board.squares[newx][y].Alive == 1 && board.squares[newx][y].color == rook.color){ /*The loops don't check the last square because of this special case where if the piece is the opposing color, you can eat them*/
                    t = 0; /*invalid move*/
               }/*esle fi*/
	       else if(board.squares[newx][y].Alive == 1 && board.squares[newx][y].color != rook.color){
		    t = 1;
	       }/*esle fi*/
	       else{
               t = 1; /*valid move*/
	       }/*esle*/
          }/*fi*/
          else{/*if y changed, invalid*/
               t = 0; /*invalid move*/
          }/*esle*/
     }/*fi*/

     if(newy != y){  /* same loop as the x, except now it checks if the rook moved in the y direction */
          counter = newy -y;
          if(newx == x){
               for(int i=1;counter>1;counter--){/*loop to check that no pieces are inbetween old spot and new spot*/

                        if(board.squares[x][y+i].Alive == 1){/*sees if the square has someone alive regardless of color*/
                                t = 0; /*invlaid*/
                        }/*fi*/
                        i++;
               }/*rof*/
               for(int i=1;counter<-1;counter++){/*second loop incase the counter is negative*/

                        if(board.squares[x][y-i].Alive == 1){/*if alive ofr not */
                                t = 0; /*invlaid*/
                        }/*fi*/
                        i++;
               }/*rof*/
	       if(t == 0){/*if t is set to invalid, skip these cases*/
		    t = 0;
	       }/*fi*/
               else if(board.squares[x][newy].Alive == 1 && board.squares[x][newy].color == rook.color){/*chekcks the last square if it's a friendly*/
                    t = 0; /*invalid move*/
               }/*esle fi*/
	       else if(board.squares[x][newy].Alive == 1 && board.squares[x][newy].color != rook.color){/*checks the last square if it's an enemy*/
		    t = 1;
	       }/*esle fi*/
               else{
                    t = 1; /*valid move*/
	       }/*esle*/
          }/*fi*/
          else{/*if x did change in direction, invalid*/
               t = 0;/*invalid move*/
          }/*esle*/
     }/*fi*/
     check  = CheckIfInvalid(rook, destination);
     if (check == 0){
          t = check;
     }
	return t;
}/*rookmove*/

int KnightMove(PIECE knight, BOARD board, int destination){
        int check, t;
        int x = knight.PosX;
        int y = knight.PosY;

     int newx = destination / 10;
        int newy = destination % 10;         
     /*Checks if the move is valid. Knight moves a change of 2 squares horixontally and 1 vertically or 2 vertically and 1 horizonaally*/
     int dx = abs(newx - x);
     int dy = abs(newy - y); 
     if( dx > 2 || dx < 1 || dy < 1 || dy > 2){
          t = 0; /* invalid */
     }
     else if( dx == dy){
          t = 0; /* invalid */
     }
     else if(board.squares[newx][newy].Alive == 1 && knight.color == board.squares[newx][newy].color){
          t = 0; /* invalid */ 
     }
     else if(board.squares[newx][newy].Alive == 1 && board.squares[newx][newy].color != knight.color){
          t = 1; /*valid*/
     }         
     else{
          t = 1; /*valid*/ 
     }
     check  = CheckIfInvalid(knight, destination);
        if (check == 0){
                t = check;
        }

     return t;
}

int BishopMove(PIECE bishop, BOARD board, int destination){
	int t, check; /* t is used to check whether a move is valid or not by returning a value of 0 or 1 */
	check  = CheckIfInvalid(bishop, destination); /* checks basic rules that applies to all pieces */ 
	if (check == 0){
		return check; /* invalid */
	}

	int x = bishop.PosX;
	int y = bishop.PosY;
	int newx = destination / 10;
	int newy = destination % 10;
        
	if((abs(newx - x)) == (abs(newy - y))){

		/* checks all the spaces inbetween as it moves to its new destination */

		if((newx > x) && (newy > y)){ /* moves upper right */
			for(int i = x + 1; i < newx; i++){ /* moves piece right */
				for(int j = y + 1; j < newy; j++){ /* moves piece up */
					if(board.squares[i][j].Alive == 1){ /* cannot pass through if the space is occupied by another piece */
						t = 0; /*invalid*/
					}
				}
			}

			/* when it gets to the destination, then it has to check to see if it can eat the piece or if the square is empty */
			if((newx == x) && (newy == y)){
				if(bishop.color == board.squares[x][y].color){ /* if piece is the same color */
					t = 0; /* invalid */
                            	}
                              	if((bishop.color != board.squares[x][y].color && board.squares[x][y].Alive == 1) || board.squares[x][y].Alive == 0){ /* different color and square is occupied OR empty */
                                   	t = 1; /* valid */ 
                              	}
			}
          	}

		/* checks all the spaces inbetween as it moves to its new destination */

		else if((newx < x) && (newy > y)){ /* moves upper left */
			for(int i = x - 1; i > newx; i--){ /* moves piece left */
				for(int j = y + 1; j < newy; j++){ /* moves piece up */
					if(board.squares[i][j].Alive == 1){ /* cannot pass through if the space is occupied by another piece */
						t = 0; /*invalid*/
					}
				}
			}

			/* when it gets to the destination, then it has to check to see if it can eat the piece or if the square is empty */
			if((newx == x) && (newy == y)){
				if(bishop.color == board.squares[x][y].color){ /* if piece is the same color */
					t = 0; /* invalid */
				}
				if((bishop.color != board.squares[x][y].color && board.squares[x][y].Alive == 1) || board.squares[x][y].Alive == 0){ /* different color and square is occupied or empty */
					t = 1; /* valid */	
				}               
			}                                
		}
    
		/* checks all the spaces inbetween as it moves to its new destination */

		else if((newx > x) && (newy < y)){ /* moves bottom right */
			for(int i = x + 1; i < newx; i++){ /* moves piece right */
				for(int j = y - 1; j > newy; j--){ /* moves piece down */
					if(board.squares[i][j].Alive == 1){ /* cannot pass through if the space is occupied by another piece */ 
						t = 0; /*invalid*/
                                   	}
				}
			}

			/* when it gets to the destination, then it has to check to see if it can eat the piece or if the square is empty */ 
			if((newx == x) && (newy == y)){
				if(bishop.color == board.squares[x][y].color){ /* if piece is the same color */
					t = 0; /* invalid */
				}
				if((bishop.color != board.squares[x][y].color && board.squares[x][y].Alive == 1) || board.squares[x][y].Alive == 0){ /* different color and square is occupied or empty */
					t = 1; /* valid */
				}     
			}
		}

		/* checks all the spaces inbetween as it moves to its new destination */

		else if((newx < x) && (newy < y)){ /* moves bottom left */
			for(int i = x - 1; i > newx; i--){ /* moves piece left */
				for(int j = y - 1; j < newy; j--){ /* moves piece down */
					if(board.squares[i][j].Alive == 1){ /* cannot pass through if the space is occupied by another piece */
						t = 0; /*invalid*/
					}
				}
			}

			/* when it gets to the destination, then it has to check to see if it can eat the piece or if the square is empty */
			if((newx == x) && (newy == y)){
				if(bishop.color == board.squares[x][y].color){ /* if piece is the same color */
					t = 0; /* invalid */
				}
				if((bishop.color != board.squares[x][y].color && board.squares[x][y].Alive == 1) || board.squares[x][y].Alive == 0){ /* different color and square is occupied or empty */
					t = 1; /* valid */
				}
			}    
		}         
	}

	else{
		t = 0; /* invalid */
	}

	return t;
}    
     
int QueenMove(PIECE queen, BOARD board, int destination){
     int x;
     x = RookMove(queen, board, destination);
     if(x == 0){/*if rookmove gives invalid, then test bishopmove*/
          x = BishopMove(queen, board, destination);
     }
     return x;        
}


PIECE KingMove(PIECE king, BOARD board) {
        int one_x = -1;
        int one_y = 1;
        int x, y, pos;

        for(int i = 0; i < 8; i++) {
                if(i < 4){
                        if((i%2) == 0) {
                                one_x *= -1;
                                x = king.PosX + one_x;
                                y = king.PosY;
                                pos = 10*x + y;
                                if(x > 7 || x < 0 || y > 7 || y < 0)
				pos = -200;
				else if(king.color == board.squares[x][y].color && board.squares[x][y].Alive == 1){
                                pos *= -1;}
                                king.PotentialMoves[i] = pos;
                        }

                        else {
                                one_y *= -1;
                                x = king.PosX;
                                y = king.PosY + one_y;
                                pos = 10*x + y;
                                if(x > 7 || x < 0 || y > 7 || y < 0)
                                pos = -200;
                                else if(king.color == board.squares[x][y].color && board.squares[x][y].Alive == 1){
				pos *= -1;}
                                king.PotentialMoves[i] = pos;
                        }
                }
                else{
                        if((i%2) == 0) {
                                one_x *= -1;
                        }
                        else {
                                one_y *= -1;
                        }
                        x = king.PosX + one_x;
                        y = king.PosY + one_y;
                        pos = 10*x + y;
			if(x > 7 || x < 0 || y > 7 || y < 0)
                        pos = -200;
                        else if(king.color == board.squares[x][y].color && board.squares[x][y].Alive == 1){
                        pos *= -1;}
                        king.PotentialMoves[i] = pos;
                }
        }

     for(int m = 0 ; m < 8; m++) {
                if(king.PotentialMoves[m] >= 0)
                for(int x = 0; x < 8; x++) {
                        for(int y = 0; y < 8; y++) {
                                if(board.squares[x][y].color != king.color && (board.squares[x][y].Alive == 1)) {
                                        for(int i = 0; i < 30 ; i++) {
                                                if(abs(board.squares[x][y].PotentialMoves[i]) == king.PotentialMoves[m] && board.squares[x][y].Value != 10)
                                                king.PotentialMoves[m] = -100;

                                                if(board.squares[x][y].Value == 10){
                                                        if(-(board.squares[x][y].PotentialMoves[i]) == king.PotentialMoves[m])
                                                        king.PotentialMoves[m] = -100;
                                                }
                                        }
                                }
                       }
                }
        }
return king;
}
 
