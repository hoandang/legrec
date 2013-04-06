#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>

enum Color
{
    BLANK = 0,
    WHITE = 1,
    BLACK = 2
};

class PlayerColor
{
     private:
        Color playerColor;
       
    public:
        // constructors
        PlayerColor() : playerColor(BLANK)
        {
        }
       
        PlayerColor(Color pc) : playerColor(pc)
        {
        }
        
        PlayerColor(const PlayerColor &other) : playerColor(other.playerColor)
        {
        }
        
        Color getPlayerColor() const { return playerColor; }
        
        const char* toString() const
        {
            if (playerColor == WHITE) return "White";
            else if (playerColor == BLACK) return "Black";
            else return "Empty";
        }
        
        
        // static methods
        static Color otherPlayerColor(Color aColor)
        {
            // return who opponent is to a particular player
            if (aColor == WHITE) return BLACK;
            else if (aColor == BLACK) return WHITE;
            else return BLANK;
        }
        
        static Color otherPlayerColor(const PlayerColor &aPlayer)
        {
            return otherPlayerColor(aPlayer.playerColor);
        }  
        
        Color otherPlayerColor() const
		{
		    return otherPlayerColor(playerColor);
		}
        
        // overloaded operators = operator
        const PlayerColor& operator = (const PlayerColor &otherColor)
        {
            playerColor = otherColor.playerColor;
            return *this;
        }
        
        const PlayerColor& operator = (Color otherColor)
        {
            playerColor = otherColor;
            return *this;
        }
        
        // overloaded == operators
        bool operator == (const PlayerColor &other) const
        {
            return (playerColor == other.playerColor);
        }
        
        bool operator == (Color otherColor) const
        {
            return (playerColor == otherColor);
        }
        
        // overloaded != operators
        bool operator != (const PlayerColor &other) const
        {
            return (playerColor != other.playerColor);
        }
        
        bool operator != (Color otherColor) const
        {
            return (playerColor != otherColor);
        }
};


#endif

