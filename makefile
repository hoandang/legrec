CC = g++
prog: legrec.o game.o board.o piece.o 
	$(CC) legrec.o game.o board.o piece.o -Wall -Werror -pedantic -o legrec
legrec.o: legrec.cpp game.h
	$(CC) -Wall -Werror -pedantic -c legrec.cpp
game.o: game.cpp game.h board.h piece.h move.h player.h
	$(CC) -Wall -Werror -pedantic -c game.cpp
board.o: board.cpp board.h piece.h move.h player.h
	$(CC) -Wall -Werror -pedantic -c board.cpp
piece.o: piece.cpp piece.h board.h move.h player.h
	$(CC) -Wall -Werror -pedantic -c piece.cpp
