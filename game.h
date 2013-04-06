#ifndef _GAME_H
#define _GAME_H

// forward declarations
class board;
class piece;

#include <time.h>

#include "move.h"
#include "piece.h"
#include "player.h"
#include "board.h"

class game
{
    // the game object manages the game of connections.
    // the moves, who wins/loses, etc

    private:
        board gameBoard;

        PlayerColor currentPlayer;

        move dataMove;

        int numMoves;
        char* entryString;
        
        bool splitUpMove(const char *entry, move &theMove);

        char* getMove();

        void makeMove(const char *entry);

        void humanMove();

        void computerMove(const char color);
        
        void resolveCurrentPlayerBlocked();

    public:
        game();
        game(const game &other);
        ~game();

        void erase();

        void collectValidMoves();

        void printBoard();
        
        void printWinner();
        
        void printMenu();
        
        void nextMove(const int doIPlayFirst);

        bool ended();

        game& operator = (const game &other);
};

#endif
