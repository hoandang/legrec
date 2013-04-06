#ifndef _MOVE_H
#define _MOVE_H

#include <stdlib.h>

#include "player.h"

struct move
{
    
    // struct to store coordinates for moving a piece from a square to a square
    
    int fromX;
    int fromY;
    int toX;
    int toY;
    
    move() : fromX(-1), fromY(-1), toX(-1), toY(-1)
    {
    }
    
    move(int fx, int fy, int tox, int toy) 
        : fromX(fx), fromY(fy), toX(tox), toY(toy)
    {
        
    }
    
    void setMove(int fx, int fy, int tox, int toy)
    {
        fromX = fx;
        fromY = fy;
        toX = tox;
        toY = toy;
    }
    
    int xMove() const
    {
        // return number of x spaces we have moved
        return abs(toX - fromX);
    }

    int yMove() const
    {
        // return number of y spaces we have moved
        return abs(toY - fromY);
    }
    
    bool atToLocation(int x, int y) const
    {
		// return if we are moving to x, y location
        return (x == toX && y == toY);
    }
    
    bool onOrthogonal() const
    {
        // return if move is either along vertical or horzontal line
        return (toX == fromX  || toY == fromY);
    }
    
    int distance() const
    {
        int diag = (xMove() < yMove()) ? xMove() : yMove();
        return diag + abs(xMove() - yMove());
    }
    
    void middleMove(int &x, int &y) const
    {
        x = (toX + fromX) / 2;
        y = (toY + fromY) / 2;
    }
    
    bool onDiagonal() const
    {
        // return if move is along a 45 degree diagonal line
        return (xMove() == yMove());
    }

    char* getString(char *theMove) const
    {
        // given the char array theMove, add the typed move to it and then return it
        theMove[0] = 'a' + fromX;
        theMove[1] = '0' + fromY;
        theMove[2] = ' ';
        theMove[3] = 'a' + toX;
        theMove[4] = '0' + toY;
        theMove[5] = '\0';
        
        return theMove;
    }
    
    bool isSideways() const
    {
        return (fromY == toY);
    }
    
    bool isForward(PlayerColor playerColor) const
    {
        if (playerColor == WHITE) return (toY > fromY);
        else return (toY < fromY);
    }
    
    bool isBackward(PlayerColor playerColor) const
    {
        if (playerColor == WHITE) return (toY < fromY);
        else return (toY > fromY);
    }
};

#endif
