#ifndef _BOARD_H
#define _BOARD_H

#include "piece.h"
#include "move.h"
#include "player.h"

// maximum size of board side
const int MAXWIDTH = 4;
const int MAXHEIGHT = 4;
        
class board
{
    // the board object manages the board. 
    // Particularly, which pieces are on each square

    private:
        
        // the array that hold the board square and which pieces are on it
        piece* squares[MAXHEIGHT][MAXWIDTH];
        
        void setupBoard();
        void clear();
        
		// private methods for printing sections of the board
        void printRow(int y) const;        
        void printMiddleLine() const;      
        void printOuterLine() const;      
        void printBottomLine() const;
        
        const piece* getPiece(int x, int y) const;
        void swapPieces(move theMove);
        
    public:

        board();
        board(const board &other);
        ~board();
		
        void printBoard() const;
        void printScore() const;
		
        void movePiece(PlayerColor playerColor, move theMove);
        static bool insideBoardBoundaries(int x, int y);
        static bool insideBoardBoundaries(move theMove);
        bool legalMove(PlayerColor playerColor, move theMove) const;
        bool noLegalMoves(PlayerColor playerColor) const;
        bool allPiecesMoved(PlayerColor playerColor) const;
        
        PlayerColor getPieceColor(int x, int y) const;
        bool squareEmpty(int x, int y) const;
        PieceType getPieceType(int x, int y) const;

        int whiteScore() const;
        int blackScore() const;
        int playerScore(PlayerColor playerColor) const;
        int playerScore(Color playerColor) const;
        int currentScore(PlayerColor playerColor) const;
        
        bool ended() const;
        
        board& operator = (const board &other);
};

#endif

