#include <iostream>
#include <string.h>

#include "piece.h"
       
// piece constructors and destructors
       
piece::piece() : playerColor(BLANK)
{
}
        
piece::piece(PlayerColor p) : playerColor(p)
{
}

piece::~piece()
{
}

const char* piece::getPieceChar() const
{
    if (playerColor == BLANK) return "   ";
    else if (playerColor == WHITE) return " O "; 
    else return " # ";
}   




