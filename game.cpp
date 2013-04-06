#include <string.h>
#include <iostream>

#include "game.h"
#include "math.h"
#include <vector>

// define the maximum number of keystrokes permitted per move
const int ENTRYMAX = 10;

using namespace std;

game::game() {
	currentPlayer = WHITE;

	numMoves = 0;
	entryString = new char[ENTRYMAX];

	srand(time(NULL));
}

game::game(const game &other) {
	gameBoard = other.gameBoard;
	currentPlayer = other.currentPlayer;
	numMoves = other.numMoves;
	entryString = new char[ENTRYMAX];
	strcpy(entryString, other.entryString);
}

game::~game() {
	delete entryString;
}

game& game::operator =(const game &other) {
	// make this game equal to the other game
	gameBoard = other.gameBoard;
	strcpy(entryString, other.entryString);
	currentPlayer = other.currentPlayer;
	numMoves = other.numMoves;

	return *this;
}

bool game::splitUpMove(const char *entry, move &theMove) {
	// the user has entered a move - eg a1 b3
	// split this up and update the move object

	if (entry == NULL)
		return false;

	if (strlen(entry) != 5)
		return false;
	if (entry[2] != ' ')
		return false;

	theMove.fromX = entry[0] - 'a';
	theMove.fromY = entry[1] - '0';
	theMove.toX = entry[3] - 'a';
	theMove.toY = entry[4] - '0';

	return true;
}

char* game::getMove() {
	// ask the user to enter a move
	cout << "\n" << numMoves << ". Next move, " << currentPlayer.toString()
			<< " to play : ";

	cin.getline(entryString, ENTRYMAX);

	return entryString;
}

void game::printMenu() {
	cout << "\nINSTRUCTIONS\n";
	cout << "m     : print this menu\n";
	cout << "q     : quit\n";
	cout << "a2 b3 : move piece from a2 to b3\n";
	cout << "\n";
}

void game::printBoard() {
	gameBoard.printBoard();
}

void game::printWinner() {
	// print the results of the game
	int scoreWhite = gameBoard.whiteScore();
	int scoreBlack = gameBoard.blackScore();

	if (scoreWhite > scoreBlack) {
		cout << "\nWhite has won with a score of " << scoreWhite << " to "
				<< scoreBlack << "\n";
	} else if (scoreBlack > scoreWhite) {
		cout << "\nBlack has won with a score of " << scoreBlack << " to "
				<< scoreWhite << "\n";
	} else {
		cout << "\nIt's a draw with a score of " << scoreWhite << " each\n";
	}
}

void game::resolveCurrentPlayerBlocked() {
	// deal with the situation of the current player being blocked from moving

	cout << "\n" << numMoves << ". " << currentPlayer.toString()
			<< " is blocked from moving. Press enter to continue.";

	char line[1];
	cin.getline(line, 1, '\n');

	cout << "\nblocked from moving\n";

	// swap the current player and update moves
	currentPlayer = currentPlayer.otherPlayerColor();
	numMoves++;
}

void game::makeMove(const char *entry) {
	move theMove;

	bool validMove = splitUpMove(entry, theMove);

	if (validMove) {
		// a properly formated move instruction has been entered
		// now try and run it
		validMove = gameBoard.legalMove(currentPlayer, theMove);
	}

	if (validMove) {
		gameBoard.movePiece(currentPlayer, theMove);

		dataMove = theMove;
		// a properly formated, legal move was entered
		gameBoard.printBoard();
		gameBoard.printScore();

		// swap the current player and update moves
		currentPlayer = currentPlayer.otherPlayerColor();

		numMoves++;
	} else {
		// invalid or illegal move made
		cout << "Invalid move entered\n";
	}
}

void game::humanMove() {
	char* entry = getMove();

	if (entry[0] == 'q' && entry[1] == '\0') {
		// the player has entered the quit commmand
		exit(0);
	} else if (entry[0] == 'm' && entry[1] == '\0') {
		// the player has entered the print menu command
		printMenu();
	} else {
		// the player has possibly entered a move instruction
		makeMove(entry);
	}
}

void game::computerMove(const char color) {
	move theMove;
	if (gameBoard.whiteScore() == 0 && gameBoard.blackScore() == 0) {
		theMove.setMove(2, 1, 3, 2);
		gameBoard.movePiece(currentPlayer, theMove);
	} else {

		vector<move> validMoves;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					for (int l = 0; l < 4; l++) {
						theMove.setMove(i, j, k, l);
						if (gameBoard.legalMove(currentPlayer, theMove))
							validMoves.push_back(theMove);
//						else
//							validMoves.clear();
					}
				}
			}
		}
		//resolveCurrentPlayerBlocked();
		if (validMoves.size() == 0)
		{
			resolveCurrentPlayerBlocked();
		}
		else
		{
			while (1)
			{
				int random = rand() % (int) validMoves.size() + 0;
				theMove = validMoves[random];

				gameBoard.movePiece(currentPlayer, theMove);

				if (color == 'w')
				{
					if (gameBoard.whiteScore() < gameBoard.blackScore())
					{
						if (gameBoard.noLegalMoves(currentPlayer))
							break;
						else if(!gameBoard.ended())
							break;
						gameBoard.movePiece(currentPlayer, theMove);
					}
					else {
						break;
					}
				}
				else
				{
					if (gameBoard.whiteScore() > gameBoard.blackScore())
					{
						if (gameBoard.noLegalMoves(currentPlayer))
							break;
						else if(!gameBoard.ended())
							break;
						gameBoard.movePiece(currentPlayer, theMove);
					}
					else {
						break;
					}
				}
			}
		}
	}

	if (gameBoard.noLegalMoves(currentPlayer)) {
		resolveCurrentPlayerBlocked();
	} else {

	cout << '\n' << numMoves << ". " << currentPlayer.toString() << " moves : ";
	char temp[6];
	strcpy(temp, "");
	cout << theMove.getString(temp) << '\n';
	cout << '\n';
	}
	// a properly formated, legal move was entered
	gameBoard.printBoard();
	gameBoard.printScore();

	// swap the current player and update moves
	currentPlayer = currentPlayer.otherPlayerColor();

	numMoves++;
}

void game::nextMove(const int doIPlayFirst) {
	// ask the user to enter a move, validate the move and, if valid, run it

//	if (gameBoard.noLegalMoves(currentPlayer)) {
//		// the current player is blocked from moving.
//		resolveCurrentPlayerBlocked();
//	} else {
		// current player can move, so get their move and run it
		if (doIPlayFirst == 1) {
			while (1) {
				humanMove();
				if (dataMove.xMove() != 0 || dataMove.yMove() != 0) {
					dataMove.setMove(0, 0, 0, 0);
					break;
				}
			}
			computerMove('b');
		} else if (doIPlayFirst == 0) {
			computerMove('w');
			while (1) {
				humanMove();
				if (dataMove.xMove() != 0 || dataMove.yMove() != 0) {
					dataMove.setMove(0, 0, 0, 0);
					break;
				}
			}
		} else {
			humanMove();
		}
	//}
}

bool game::ended() {
	if (numMoves > 30)
		return true;
	return gameBoard.ended();
}
