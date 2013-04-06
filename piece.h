#ifndef _PIECE_H
#define _PIECE_H

// enumerated cosntants for pieces, including NOPIECE for noPiece type
enum PieceType 
{ 
    NOPIECE = 0,
    PIECE = 1
};

#include "move.h"
#include "player.h"

/*********************************************************\
   WARNING
    This code makes use of polymorphism and inheritance.
    Do NOT use such concepts in assignments 2 and 3.
   WARNING
\*********************************************************/
   
// these objects manage the base piece class and the derived pieces 

class piece
{
   // you cannot create a piece. Instead, you create derived objects
   // which are pieces.

   protected:
      PlayerColor playerColor;
      
   public:
      piece();
      piece(PlayerColor p);
      virtual ~piece();
      
      // pure virtual functions
      virtual PieceType getPieceType() const = 0;    
      virtual piece* clone() const = 0;
      
      PlayerColor getPieceColor() const { return playerColor; }
      PlayerColor getOpponentColor() const { return playerColor.otherPlayerColor(); }
      
      // questions about the type of piece
      bool isPiece() const { return !isNoPiece(); } 
      bool isNoPiece() const { return getPieceType() == NOPIECE; }
      
      const char* getPieceChar() const;
};

class playerPiece : public piece //------------------------------
{
   public :
      playerPiece(PlayerColor p) : piece (p)
      {
      }
        
      PieceType getPieceType() const
      {
         return PIECE;
      }

      piece* clone() const
      {
         return new playerPiece(playerColor);
      }
};


class noPiece : public piece //------------------------------
{
   // The piece you are having when you are not having a piece. 
   // This is a pattern object that simplifies some of our code
   
   public:
      noPiece() : piece(BLANK)
      {
      }
      
      PieceType getPieceType() const
      {
         return NOPIECE;
      } 

      piece* clone() const
      {
         return new noPiece();
      }
};

#endif

