#include <iostream>
#include <string>

#include "game.h"

// code =====================================================

void setFirstPlayer(int &doIPlayFirst, const std::string color)
{
	if (color.compare("-b") == 0)
		doIPlayFirst = 1;
	else if (color.compare("-w") == 0)
		doIPlayFirst = 0;
	else
	  doIPlayFirst = -1;
}

int main(int argc, char *argv[]) {

    int doIPlayFirst;
	 if (argc == 1)
	 	setFirstPlayer(doIPlayFirst, "");
	 else
	 	setFirstPlayer(doIPlayFirst, argv[1]);

	game theGame;

    theGame.printMenu();
    theGame.printBoard();

	while (!theGame.ended())
	{
		theGame.nextMove(doIPlayFirst);
	}

    theGame.printWinner();
    return 0;
}
