

CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -Wall -ansi -std=c99 $(DEBUG)

Chess: Main.o Board.o Move.o ChessBot_AI.o GUI.o
	$(CC) $(CFLAGS) GUI.o Board.o Move.o Main.o ChessBot_AI.o -o Chess -lSDL

Test: Test.o Board.o Move.o ChessBot_AI.o
	$(CC) $(CFLAGS) Board.o Move.o Test.o ChessBot_AI.o -o Test

Test.o: Test.c Board.h Piece.h Move.h ChessBot_AI.h
	$(CC) $(CFLAGS) -c Test.c -o Test.o

Main.o: Main.c Board.h Piece.h Move.h ChessBot_AI.h GUI.h
	$(CC) $(CFLAGS) -c Main.c -o Main.o

Board.o : Board.c Board.h Piece.h
	$(CC) $(CFLAGS) -c Board.c -o Board.o

Move.o : Move.c Move.h Piece.h Board.h
	$(CC) $(CFLAGS) -c Move.c -o Move.o

ChessBot_AI.o : ChessBot_AI.c ChessBot_AI.h Move.h Piece.h Board.h 
	$(CC) $(CFLAGS) -c ChessBot_AI.c -o ChessBot_AI.o

GUI.o: GUI.h Board.h
	$(CC) -c GUI.c -o GUI.o -Wall -ansi -std=c99 -lSDL

clean: 
	rm Chess
	rm *.o
