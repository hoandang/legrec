#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "board.h"

using namespace std;

// print functions ========================================

void board::printRow(int y) const
{
    // print a row in board showing pieces at each square
    // also print row numbers
    char row = '0' + y;
    
    cout << row << " |";
    for (int x=0; x<MAXWIDTH; x++)
    {
       cout << squares[y][x]->getPieceChar() << "|";
    }
    cout << "\n";
}

void board::printMiddleLine() const
{
    // print a ---+--- etc line
    cout << "  |-";
    for (int x=0; x<MAXWIDTH-1; x++)
    {
       cout << "--+-";
    }
    cout << "--|\n";
}

void board::printOuterLine() const
{
    // print the top and bottom line of board
    cout << "   -";
    for (int x=0; x<MAXWIDTH-1; x++)
    {
       cout << "----";
    }
    cout << "--\n";
}

void board::printBottomLine() const
{
    // bottom part of board with column letters
    cout << "    ";
    for (int x=0; x<MAXWIDTH; x++)
    {
       char digit = 'a' + x;
       cout << digit << "   ";
    }
    cout << "\n";
}
    
void board::printBoard() const
{
    // print entire board
    printOuterLine();
    for (int y=0; y<MAXHEIGHT; y++)
    {
        printRow(y);
        if (y < MAXHEIGHT-1) printMiddleLine();
    }
    printOuterLine();
    printBottomLine();
}

void board::printScore() const
{
    // print the scores of white and black players
    cout << "White score = " << whiteScore() << " : Black score = " << blackScore() << "\n";
}

   
// board constructors and destructor =============================================   

board::board()
{
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            squares[y][x] = NULL;
        }
    }
    setupBoard();
}

board::board(const board &other)
{
    // copy constructor
   
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            squares[y][x] = other.squares[y][x]->clone();
        }
    }
}

board::~board()
{
    // set the entire board to NULL
    clear();
}

board& board::operator = (const board &other)
{
   for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            if (squares[y][x] != NULL) delete(squares[y][x]);
            squares[y][x] = other.squares[y][x]->clone();
        }
    }
    
    return *this;
}

void board::setupBoard()
{
    // clean up previous board set up
    clear();
    
    // setup white starting positions
    for (int x = 0; x<MAXWIDTH; x++) squares[0][x] = new playerPiece(WHITE); 
    squares[1][0] = new noPiece();
    squares[1][1] = new playerPiece(WHITE);
    squares[1][2] = new playerPiece(WHITE);
    squares[1][3] = new playerPiece(WHITE);
    
    
    // setup black starting positions
    squares[2][0] = new playerPiece(BLACK);
    squares[2][1] = new playerPiece(BLACK);
    squares[2][2] = new playerPiece(BLACK);
    squares[2][3] = new noPiece();
    for (int x = 0; x<MAXWIDTH; x++) squares[3][x] = new playerPiece(BLACK); 
}

void board::clear()
{
    // delete all former pieces and set board to NULL
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            if (squares[y][x] != NULL) delete(squares[y][x]);
            squares[y][x] = NULL;
        }
    }
}

// get functions ====================================================

PlayerColor board::getPieceColor(int x, int y) const
{
    // return color of piece at square x, y
    return squares[y][x]->getPieceColor();
}

bool board::squareEmpty(int x, int y) const
{
    return (getPieceType(x, y) == NOPIECE);
}

PieceType board::getPieceType(int x, int y) const
{
    // return type of piece at square x, y
    return squares[y][x]->getPieceType();
}

const piece* board::getPiece(int x, int y) const
{
    return squares[y][x];
}

void board::swapPieces(move theMove)
{
    piece *tempPiece = squares[theMove.fromY][theMove.fromX];
    squares[theMove.fromY][theMove.fromX] = squares[theMove.toY][theMove.toX];
    squares[theMove.toY][theMove.toX] = tempPiece;
}


// move functions ===================================================

bool board::insideBoardBoundaries(int x, int y)
{
    // determine if (x,y) is properly inside the board area
    if (x < 0 || x >= MAXWIDTH) return false;
    if (y < 0 || y >= MAXHEIGHT) return false;
    return true;
}

bool board::insideBoardBoundaries(move theMove)
{
    // determine if the move is properly inside the board area
    return insideBoardBoundaries(theMove.toX, theMove.toY) &&
           insideBoardBoundaries(theMove.fromX, theMove.fromY);
}

bool board::noLegalMoves(PlayerColor playerColor) const
{
    // examine every possible move on the board and see if any are legal
    
    int fromx, fromy, tox, toy;
    move theMove;
    
    for (fromy=0; fromy<MAXHEIGHT; fromy++)
    {
        for (fromx=0; fromx<MAXWIDTH; fromx++)
        {
            for (toy=0; toy<MAXHEIGHT; toy++)
            {
                for (tox=0; tox<MAXWIDTH; tox++)
                {
                    theMove.setMove(fromx, fromy, tox, toy);
                    if (legalMove(playerColor, theMove)) return false;
                }
            }
        }
    }
    return true;
}
   
bool board::legalMove(PlayerColor playerColor, move theMove) const
{
    // ckeck that the move is within the board boundaries
    if (!insideBoardBoundaries(theMove)) return false;
    
    // confirm player has a piece at from location
    if (getPieceColor(theMove.fromX, theMove.fromY) != playerColor) return false;
    
    // confirm the move to square is empty
    if (!squareEmpty(theMove.toX, theMove.toY)) return false;
    
    // make sure move isn't backwards
	if (theMove.isBackward(playerColor)) return false;
    
    int moveDist = theMove.distance();
    
    // if move distance is one return true
    if (moveDist == 1) return true;
    
    // if move distance != 2 return false;
    if (moveDist != 2) return false;
    
    // check if diagonal or orthoganol move
    if (!theMove.onDiagonal() && !theMove.onOrthogonal()) return false;
    
    // return if jumped piece is opponent color
    int x, y;
    theMove.middleMove(x, y);
    return getPieceColor(x, y) == playerColor.otherPlayerColor();
}

void board::movePiece(PlayerColor playerColor, move theMove)
{
    // return true if piece is successfully placed
    
    // check for the legality of the move
    //if (!legalMove(playerColor, theMove)) return false;
    
    // swap the from and to locations
    swapPieces(theMove);
    
    //return true;
}

// scoring functions ===========================================

int board::whiteScore() const
{
    // add up the values and connections of all white peices
   return playerScore(WHITE);
}

int board::blackScore() const
{ 
    // add up the values and connections of all player2 pieces
   return playerScore(BLACK);
}

int board::playerScore(PlayerColor playerColor) const
{
    return playerScore(playerColor.getPlayerColor());
}

int board::playerScore(Color playerColor) const
{
    // determine if the player has moved all their pieces to the other side of the board
    
    int score = 0;
    
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            if (squares[y][x]->getPieceColor() == playerColor)
            {
                if (playerColor == WHITE && y >= MAXHEIGHT/2) score++;
                else if (playerColor == BLACK && y < MAXHEIGHT/2) score++;
            }
        }
    }
    return score;
}

int board::currentScore(PlayerColor playerColor) const
{
    // subtract the opponents score from the players score
	// a +'ve score for the player means they are ahead, other wise they are behind
   return playerScore(playerColor) - playerScore(playerColor.otherPlayerColor()); 
}

bool board::allPiecesMoved(PlayerColor playerColor) const
{
    // determine if the player has moved all their pieces to the other side of the board
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            if (squares[y][x]->getPieceColor() == playerColor)
            {
                if (playerColor == WHITE && y < MAXHEIGHT/2) return false;
                if (playerColor == BLACK && y >= MAXHEIGHT/2) return false;
            }
        }
    }
    return true;
}

bool board::ended() const
{
    // if there are no legal moves available to either player then the game ends
    if (noLegalMoves(WHITE) && noLegalMoves(BLACK)) return true;
    
    return allPiecesMoved(WHITE) || allPiecesMoved(BLACK);   
}



