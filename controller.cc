#include "controller.h"
using namespace std;

Controller::Controller(Board* theBoard, unique_ptr<Player> playerOne, unique_ptr<Player> playerTwo)
	: theBoard{theBoard}, currPlayer{playerX}, playerOne{move(playerOne)}, playerTwo{move(playerTwo)} {}

void Controller::playGame() {
	theBoard->updateViews();
	while(!theBoard->gameIsOver()) {
		int moveCol; // this is just the column number to be dropped at
		if(currPlayer == playerX) {
			moveCol = playerOne->getMove(theBoard);
		} else {
			moveCol = playerTwo->getMove(theBoard);
		}
		theBoard->dropPiece(currPlayer, moveCol);
		theBoard->updateViews();
		currPlayer = getOpposingTeam(currPlayer);
	}
	theBoard->displayWinner();
}

