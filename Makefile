CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -Wall -ansi -std=c99 $(DEBUG)
ALL = Chess

Chess: Main.o Board.o Move.o ChessBot_AI.o GUI.o
	$(CC) $(CFLAGS) ./bin/Board.o ./bin/Move.o ./bin/GUI.o ./bin/Main.o ./bin/ChessBot_AI.o -o ./bin/Chess -lSDL

Main.o: ./src/Main.c ./src/Board.h ./src/Piece.h ./src/ChessBot_AI.h ./src/Move.h
	$(CC) $(CFLAGS) -c ./src/Main.c -o ./bin/Main.o

Board.o : ./src/Board.c ./src/Board.h ./src/Piece.h
	$(CC) $(CFLAGS) -c ./src/Board.c -o ./bin/Board.o

Move.o : ./src/Move.c ./src/Board.h ./src/Piece.h ./src/Move.h ./src/Move.c
	$(CC) $(CFLAGS) -c ./src/Move.c -o ./bin/Move.o

ChessBot_AI.o : ./src/ChessBot_AI.c ./src/ChessBot_AI.h ./src/Board.h ./src/Move.h ./src/Piece.h
	$(CC) $(CFLAGS) -c ./src/ChessBot_AI.c -o ./bin/ChessBot_AI.o

GUI.o : ./src/GUI.c ./src/GUI.h ./src/Board.h
	$(CC) $(CFLAGS) -c ./src/GUI.c -o ./bin/GUI.o -lSDL
clean:
	rm ./bin/Chess
	rm ./bin/*.o
tar:
	tar -zcvf Chess_V1.0.tar.gz ./doc/README ./doc/COPYRIGHT ./bin/Chess ./doc/Chess_UserManual.pdf ./doc/INSTALL ./Makefile ./bin/*.bmp
	tar -zcvf Chess_V1.0_src.tar.gz ./doc/README ./doc/COPYRIGHT ./doc/INSTALL ./bin ./src ./Makefile 

cleanTar:
	rm *.tar.gz

uninstall:
	rm -rf bin
	rm -rf doc
	rm Makefile
